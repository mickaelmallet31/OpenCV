/**************************************
 ** OPENCV - EXERCICE 1.3 :          **
 ** Op�rations �l�mentaires sur      **
 ** les images                       **
 **************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
const int taille_x = 800;
const int taille_y = 1100;

int main(void)
{
  std::cout << "Exercice 1-3..." << std::endl;

  Mat m1, m2, m3, m4;

  // Charge l'image
  m1 = imread("data/joubarbe.jpg");
  CV_Assert(m1.data != nullptr);
  const char * name_win = "Scène";
  //cv::namedWindow(name_win); cv::moveWindow(name_win, 0, 0); cv::imshow(name_win, m1);


  // (1) A FAIRE : Extraire une zone d'int�ret :
  // rectangle de taille 360 x 360 � la position (220,330)
  m2 = Mat(m1, Rect(220, 330, 360, 360));
  name_win = "Zone d'intérêt";
  //cv::namedWindow(name_win); cv::moveWindow(name_win, taille_x, 0); cv::imshow(name_win, m2);

  // (2) A FAIRE : Aggrandir la zone d'int�r�t (zoom + 50 %)
  //m3 = Mat(540, 540, CV_8U, Scalar(0));
  resize(m2, m3, Size(0,0), 1.5, 1.5);
  cv::imshow("Zoom", m3);

  // (3) A FAIRE : Masquer avec un disque au centre de l'image
  Mat masque = Mat(m3.size().height, m3.size().width, CV_8U, Scalar(0));
  circle(masque, Point(m3.size().width/2, m3.size().height/2), 180, Scalar(255), -1, CV_AA);
  name_win = "Masque";
  cv::imshow(name_win, masque);

  m3.copyTo(m4, masque);
  name_win = "Masquee";
  cv::imshow(name_win, m4);

  std::cout << "Appuyer sur une touche pour terminer..." << std::endl;
  cv::waitKey(0);
  cv::waitKey(0);
  cv::waitKey(0);
  cv::waitKey(0);
  std::cout << "Fin.\n";

  return 0;
}
