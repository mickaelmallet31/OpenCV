/**************************************
 ** OPENCV - EXERCICE 1.2 :          **
 ** Espaces de couleur               **
 **************************************/
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main(void)
{
  std::cout << "Exercice 1-2..." << std::endl;

  // Les quatres images � g�n�rer
  cv::Mat m1, m2, m3, m4;
  int taille_x = 500;
  int taille_y = 450;

  //////////////////////////////////////////
  // Chargement image
  //////////////////////////////////////////

  // (1) A FAIRE : Charger l'image "data/jouets.png" dans la matrice m
  m1 = imread("data/jouets.png");
  const char * name_win = "1 - Image d'entree";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 0, 0); cv::imshow(name_win, m1);

  //////////////////////////////////////////
  // Conversion en niveaux de gris
  //////////////////////////////////////////

  // (2) A FAIRE : Convertir l'image en niveaux de gris
  // (supprimer la ligne de code suivante)
  cvtColor(m1, m2, CV_BGR2GRAY);
  name_win = "2 - Conversion niveaux de gris";
  cv::namedWindow(name_win); cv::moveWindow(name_win, taille_x, 0); cv::imshow(name_win, m2);

  //////////////////////////////////////////
  // Diminution de la saturation des couleurs
  //////////////////////////////////////////
  // Conversion BGR -> HSV (Hue, Saturation, Value)
  cv::cvtColor(m1, m3, CV_BGR2HSV);

  // S�paration des 3 composantes H,S,V
  cv::Mat compos[3];

  // (3) A FAIRE : s�parer les 3 canaux de l'image HSV (m3)
  // ...
  split(m3, compos);

  // (4) A FAIRE : diviser la saturation (2eme composante) par 2
  // ...
  compos[1] /= 2;

  // Regroupement des trois composantes et conversion en BGR
  cv::merge(compos, 3, m3);
  cv::cvtColor(m3,m3,CV_HSV2BGR);
  name_win = "3 - desaturation";
  cv::namedWindow(name_win); cv::moveWindow(name_win, taille_x * 2, 0); cv::imshow(name_win, m3);

  //////////////////////////////////////////
  // D�tection d'objet d'apr�s sa couleur
  //////////////////////////////////////////

  cv::Mat masque, hsv;
  // Conversion en HSV
  cv::cvtColor(m1,hsv,CV_BGR2HSV);

  // Calcul d'un masque
  // en s�lectionnant tous les pixels ~ verts :
  // teinte entre 41 et 71 (approximativement).
  cv::inRange(hsv,
              // Borne inf�rieure
              cv::Scalar(41,50,50),
              // Borne sup�rieure
              cv::Scalar(71,255,255),
              masque);
  name_win = "Masque";
  cv::namedWindow(name_win); cv::moveWindow(name_win, 0, taille_y); cv::imshow(name_win, masque);

  // m4 = matrice d'entr�e (couleur)
  m4 = m1;

  // (4) A FAIRE : mettre en rouge tous les �l�ments masqu�s (dans la matrice m4)
  // ....
  m4.setTo(Scalar(0, 0, 255), masque);
  name_win = "Masquee";
  cv::namedWindow(name_win); cv::moveWindow(name_win, taille_x, taille_y); cv::imshow(name_win, m4);

  // Attente appui sur une touche du clavier
  std::cout << "Fin : appuyer sur une touche pour terminer." << std::endl;
  cv::waitKey(0);
  cv::waitKey(0);
  cv::waitKey(0);
  return 0;
}
