/**************************************
 ** OPENCV - EXERCICE 3 :            **
 ** Mise en correspondance de points **
 ** d'int�r�t                        **
 **************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace cv;

// Seuil pour le crit�re de ratio
#define SEUIL_RATIO 0.63f

int main(void)
{
  std::cout << "Exercice 3..." << std::endl;

  Mat img[2];
  Mat empty;
  img[0] = imread("data/box.png", CV_LOAD_IMAGE_GRAYSCALE);
  img[1] = imread("data/box-in-scene.png", CV_LOAD_IMAGE_GRAYSCALE);

  if(!img[0].data || !img[1].data)
  {
    std::cout << "Erreur lors de la lecture des images\n";
    return -1;
  }

  // Vecteurs de points d'int�r�ts (un par image)
  std::vector<KeyPoint> keypoints[2];
  // Matrice des traits (pour chaque image, et pour chaque point d'int�r�t)
  Mat traits[2];

  // A FAIRE : instancier un d�tecteur ORB (ORiented BRIEF),
  // r�gl� pour d�tecter au maximum 500 points d'int�r�ts
  // et l'appliquer aux deux images pour calculer :
  //   - les points d'int�r�ts ("keypoints" en anglais)
  //   - les traits ("descriptors" en anglais)
  auto orb = ORB::create(500);
  orb->detectAndCompute(img[0], empty, keypoints[0], traits[0]);
  orb->detectAndCompute(img[1], empty, keypoints[1], traits[1]);

  // Paires de points d'int�r�t
  std::vector<std::vector<DMatch> > matches;

  // A FAIRE : Mettre en correspondance les points d'int�r�ts
  // (calcul des paires). Utiliser la m�thode "brute force",
  // avec la norme de Hamming.
  auto descriptor = DescriptorMatcher::create("BruteForce-Hamming");
  descriptor->knnMatch(traits[0], traits[1], matches, 2);

  // Ici, on a un ensemble de correspondance brutes
  // Il s'agit maintenant de filtrer pour ne retenir
  // que les paires de points d'int�r�ts les plus fiables
  std::vector<DMatch> good_matches;

  // Filtre crit�re ratio
  for(auto &match: matches)
  {
    // A FAIRE : V�rifier qu'il y a au moins 2 voisins
    // et v�rifier le crit�re de distance :
    // d0 < SEUIL_RATIO * d1, avec d0: distance du plus proche,
    // d1: distance du deuxi�me plus proche.
    // Si le crit�re est v�rifi�, ajouter le plus
    // des bonnes paires ("good_matches").
    // (commenter la ligne suivante)
    if (match.size() >= 2)
    {
      if (match[0].distance < match[1].distance * SEUIL_RATIO)
      {
        good_matches.push_back(match[0]);
      }
    }
  }

  // Dessin des paires de points pour v�rification
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
