/**************************************
 ** OPENCV - EXERCICE 2.3 :          **
 **  Transform�e de Hough            **
 **************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace cv;

int main(void)
{
  std::cout << "Exercice 2-3...\n";
  std::cout << "Transform�e de Hough\n\n";
  std::cout << "Appuyer sur une touche pour terminer..." << std::endl;

  Mat m1, m2;

  m1 = imread("./data/carte.jpg");
  imshow("Carte", m1);


  std::cout << "Canny..." << std::endl;
  // (1) A FAIRE : Utiliser l'algorithme de Canny (attention au r�glage des seuils...)
  m2 = m1; // (supprimer cette ligne)

  cv::imshow("Canny", m2);

  ////////////////////////////////////////////////////
  std::cout << "Hough..." << std::endl;
  std::vector<Vec2f> lignes;

  // (2) A FAIRE : Faire la transform�e de Hough (fonction OpenCV HoughLines)


  std::cout << "D�tect� " << lignes.size() << " lignes." << std::endl;

  // Dessin des lignes (superposition sur l'image initiale)
  for(size_t i = 0; i < lignes.size(); i++ )
  {
    // R�cup�re les coordonn�es polaires de chaque ligne
    float rho   = lignes[i][0],
          theta = lignes[i][1];

    // Calcul 2 points sur la ligne (� l'ext�rieur de l'image)
    cv::Point pt1, pt2;
    float a = cos(theta), b = sin(theta);
    float x0 = a * rho, y0 = b * rho;
    pt1.x = x0 - 1000 * b;
    pt1.y = y0 + 1000 * a;
    pt2.x = x0 + 1000 * b;
    pt2.y = y0 - 1000 * a;

    // (3) A FAIRE : tracer une ligne entre les 2 points pt1 et pt2

  }
  cv::imshow("Detection", m1);

  waitKey(0);
  std::cout << "Fin.\n";
  return 0;
}



