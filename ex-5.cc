/**************************************
 ** OPENCV - EXERCICE 5 :            **
 ** Calcul d'homographie             **
 **************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>
#include <stdint.h>

using namespace cv;
using namespace std;

void detection_paires(Mat img[2],
                      std::vector<Point2f> &pts_0,
                      std::vector<Point2f> &pts_1)
{
  std::vector<DMatch> good_matches;
  auto orb = cv::ORB::create(500); // 500 points max
  std::vector<KeyPoint> keypoints[2];
  Mat traits[2];

  orb->detectAndCompute(img[0], Mat(), keypoints[0], traits[0]);
  orb->detectAndCompute(img[1], Mat(), keypoints[1], traits[1]);


  // Mise en correspondance dess points d'int�r�ts
  BFMatcher matcher(NORM_HAMMING);
  std::vector<DMatch> matches;
  matcher.match(traits[0], traits[1], matches);

  double max_dist = 0; double min_dist = 100;

  // Calcul des distances min et max entre les points
  for( int i = 0; i < traits[0].rows; i++ )
  {
    double dist = matches[i].distance;
    if(dist < min_dist)
      min_dist = dist;
    if(dist > max_dist)
      max_dist = dist;
  }

  printf("Max dist : %f\n", max_dist);
  printf("Min dist : %f\n", min_dist);

  // Draw only "good" matches (i.e. whose distance is less than 2.5 * min_dist )
  for(int i = 0; i < traits[0].rows; i++ )
  {
    if(matches[i].distance < 2.5 * min_dist)
      good_matches.push_back(matches[i]);
  }

  Mat img_matches;
  drawMatches(img[0], keypoints[0], img[1], keypoints[1],
              good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
              std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

  const char * name_win = "Paires";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 50, 50); cv::imshow(name_win, img_matches);

  for(auto i = 0u; i < good_matches.size(); i++ )
  {
     // Get the keypoints from the good matches
     pts_0.push_back(keypoints[0][good_matches[i].queryIdx].pt);
     pts_1.push_back(keypoints[1][good_matches[i].trainIdx].pt);
  }
}



int main(void)
{
  std::cout << "Exercice 5..." << std::endl;

  Mat img[2];
  img[0] = imread("data/box.png", CV_LOAD_IMAGE_GRAYSCALE);
  img[1] = imread("data/box-in-scene.png", CV_LOAD_IMAGE_GRAYSCALE);

  if(!img[0].data || !img[1].data)
  {
    std::cout << "Erreur lors de la lecture des images\n";
    return -1;
  }



  ////////////////////////////////////////////////////////////////
  // Etape 1: d�tection des paires de points d'int�r�ts (ORB)
  // (c.f. exercice 3)
  ////////////////////////////////////////////////////////////////
  std::vector<Point2f> pts[2];
  detection_paires(img, pts[0], pts[1]);


  ////////////////////////////////////////////////////////////////
  /// ETAPE 2 : localisation de l'objet (calcul d'homographie)  //
  ////////////////////////////////////////////////////////////////

  // A FAIRE : estimation d'homographie
  // (commenter la ligne suivante, et estimer l'homographie H � partir
  // des paires de point d'int�r�ts pr�c�demment trouv�es).
  Mat H = findHomography(pts[0], pts[1], CV_RANSAC);

  // Dimension de l'objet
  uint16_t sx = img[0].cols, sy = img[0].rows;

  // Position des 4 coins de l'objet (dans la premi�re image)
  std::vector<Point2f> coins_obj(4);
  coins_obj[0] = Point2f(0,0);
  coins_obj[1] = Point2f(sx, 0);
  coins_obj[2] = Point2f(sx, sy);
  coins_obj[3] = Point2f(0, sy);

  // Position des 4 coins de l'objet (dans la deuxi�me image)
  std::vector<Point2f> coins_scene(4);

  // A FAIRE : Calculer les positions des coins de l'objet dans la deuxi�me image
  // (Utiliser l'homographie H)
  perspectiveTransform(coins_obj, coins_scene, H);

  // Construit une image couleur � partir de la 2eme image
  Mat img_det;
  cvtColor(img[1], img_det, CV_GRAY2BGR);

  // Dessine les contour de l'objet sur la 2eme image (en vert)
  for(auto i = 0u; i < 4; i++)
    line(img_det, coins_scene[i], coins_scene[(i+1) & 3],
        Scalar(0, 255, 0) /* vert */, 4);

  // Affiche la localisation de l'objet sur la deuxi�me image
  const char * name_win = "Detection";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 900, 50); cv::imshow(name_win, img_det);

  // Applique une transform�e de perspective pour remettre
  // � plat l'objet d�tect�
  Mat img_cor;

  // A FAIRE : corriger la perspective de l'objet d�tect� sur l'image 2
  // (commenter la ligne suivante)
  warpPerspective(img[1], img_cor, H.inv(), img[0].size());
  name_win = "Perspective corrigee";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 50, 500); cv::imshow(name_win, img_cor);

  waitKey(0);
  std::cout << "Fin.\n";
  return 0;
}
