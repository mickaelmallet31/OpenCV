/**************************************
 ** OPENCV - EXERCICE 2.2 :          **
 ** D�limitation d'objets avec Canny **
 ** et recherche de contours         **
 **************************************/

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <iostream>

using namespace cv;

int main(void)
{
  std::cout << "Exercice 2-2..." << std::endl;

  Mat m1, m2, m3, m4, m5, m6, m7;

  // Charge l'image
  m1 = imread("data/jouets2.png");
  CV_Assert(m1.data != nullptr);
  const char * name_win = "Sc�ne";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 50, 50); cv::imshow(name_win, m1);


  // A FAIRE : filtrer l'image pour diminuer le bruit
  medianBlur(m1, m2, 5);
  name_win = "Filtrage";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 500, 50); cv::imshow(name_win, m2);

  // A FAIRE : op�rateur de Canny
  Canny(m2, m3, 50, 150);
  name_win = "Canny";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 950, 50); cv::imshow(name_win, m3);

  // A FAIRE : fermeture (utiliser un op�rateur morphologique)
  Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
  morphologyEx(m3, m4, MORPH_CLOSE, kernel);
  name_win = "Fermeture";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 1450, 50); cv::imshow(name_win, m4);

  // A FAIRE : recherche de contours
  std::vector<std::vector<Point> > contours;

  // Affichage des contours
  m7 = imread("data/jouets2.png");
  cv::findContours(m4, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
  cv::drawContours(m7, contours, -1, Scalar(0,255,0), 2);
  name_win = "Contours";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 50, 500); cv::imshow(name_win, m7);

  // D�tection des billes
  m6 = m1 / 2; // En fond : l'image originale, moins lumineuse
  for(const auto &contour: contours)
  {
    // A FAIRE : parmi les contours, d�tecter les billes
    // (largeur et hauteur comprise entre 20 et 30 pixels)
    // Pour chaque bille, dessiner sa localisation (rectangle)
    // sur l'image m6.
    Rect rect = boundingRect(contour);
	
    if (rect.height >= 20 and rect.height <= 30 and rect.width >= 20 and rect.width <= 30) 
    {
      rectangle(m6, rect, Scalar(0, 255, 0), 2);
    }
  }
  name_win = "Billes";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 500, 500); cv::imshow(name_win, m6);

  std::cout << "Appuyer sur une touche pour terminer..." << std::endl;
  cv::waitKey(0);
  std::cout << "Fin.\n";

  return 0;
}
