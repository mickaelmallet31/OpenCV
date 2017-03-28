/**************************************
 ** OPENCV - EXERCICE 3 :            **
 ** Mise en correspondance de points **
 ** d'intérêt                        **
 **************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace cv;

// Seuil pour le critère de ratio
#define SEUIL_RATIO 0.65f

int main(void)
{
  std::cout << "Exercice 3..." << std::endl;

  Mat img[2];
  img[0] = imread("data/box.png", CV_LOAD_IMAGE_GRAYSCALE);
  img[1] = imread("data/box-in-scene.png", CV_LOAD_IMAGE_GRAYSCALE);

  if(!img[0].data || !img[1].data)
  {
    std::cout << "Erreur lors de la lecture des images\n";
    return -1;
  }

  // Vecteurs de points d'intérêts (un par image)
  std::vector<KeyPoint> keypoints[2];
  // Matrice des traits (pour chaque image, et pour chaque point d'intérêt)
  Mat traits[2];

  // A FAIRE : instancier un détecteur ORB (ORiented BRIEF),
  // réglé pour détecter au maximum 500 points d'intérêts
  // et l'appliquer aux deux images pour calculer :
  //   - les points d'intérêts ("keypoints" en anglais)
  //   - les traits ("descriptors" en anglais)


  // Paires de points d'intérêt
  std::vector<std::vector<DMatch> > matches;

  // A FAIRE : Mettre en correspondance les points d'intérêts
  // (calcul des paires). Utiliser la méthode "brute force",
  // avec la norme de Hamming.


  // Ici, on a un ensemble de correspondance brutes
  // Il s'agit maintenant de filtrer pour ne retenir
  // que les paires de points d'intérêts les plus fiables
  std::vector<DMatch> good_matches;

  // Filtre critère ratio
  for(auto &match: matches)
  {
    // A FAIRE : Vérifier qu'il y a au moins 2 voisins
    // et vérifier le critère de distance :
    // d0 < SEUIL_RATIO * d1, avec d0: distance du plus proche,
    // d1: distance du deuxième plus proche.
    // Si le critère est vérifié, ajouter le plus
    // des bonnes paires ("good_matches").
    // (commenter la ligne suivante)
    good_matches.push_back(match[0]);
  }

  // Dessin des paires de points pour vérification
  Mat img_matches;
  drawMatches(img[0], keypoints[0], img[1], keypoints[1],
              good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
              std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

  imshow("Paires", img_matches);
  std::cout << "Appuyer sur une touche pour continuer..." << std::endl;
  cv::waitKey(0);

  std::cout << "Fin.\n";
  return 0;
}




