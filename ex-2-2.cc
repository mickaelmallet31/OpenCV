/**************************************
 ** OPENCV - EXERCICE 2.2 :          **
 ** Délimitation d'objets avec Canny **
 ** et recherche de contours         **
 **************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace cv;

int main(void)
{
  std::cout << "Exercice 2-2..." << std::endl;
  
  Mat m1, m2, m3, m4, m5, m6;

  // Charge l'image
  m1 = imread("data/jouets2.png");
  CV_Assert(m1.data != nullptr);
  imshow("Scène", m1);


  // A FAIRE : filtrer l'image pour diminuer le bruit
  m2 = m1; // A supprimer

  imshow("Filtage", m2);


  // A FAIRE : opérateur de Canny
  m3 = Mat::zeros(m1.size(), CV_8U); // A supprimer
  imshow("Canny", m3);

  // A FAIRE : fermeture (utiliser un opérateur morphologique)
  m4 = m3; // A supprimer
  imshow("Fermeture", m4);

  // A FAIRE : recherche de contours
  std::vector<std::vector<Point> > contours;

  // Affichage des contours
  m5 = m1 / 2; // En fond : l'image originale, moins lumineuse
  cv::drawContours(m5, contours, -1, Scalar(0,255,0), 2);
  imshow("Contours", m5);


  // Détection des billes
  m6 = m1 / 2; // En fond : l'image originale, moins lumineuse
  for(const auto &contour: contours)
  {
    // A FAIRE : parmi les contours, détecter les billes
    // (largeur et hauteur comprise entre 20 et 30 pixels)
    // Pour chaque bille, dessiner sa localisation (rectangle)
    // sur l'image m6.

  }
  imshow("Billes", m6);

  std::cout << "Appuyer sur une touche pour terminer..." << std::endl;
  cv::waitKey(0);
  std::cout << "Fin.\n";

  return 0;
}



