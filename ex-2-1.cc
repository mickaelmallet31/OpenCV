/**************************************
 ** OPENCV - EXERCICE 2.1 :          **
 **  Filtrage et d�rivation (sur un  **
 **  flux vid�o)                     **
 **************************************/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

using namespace cv;

int main(void)
{
  std::cout << "Exercice 2-1...\n";
  std::cout << "Video / filtrage / d�rivation\n\n";
  std::cout << "Appuyer sur une touche pour terminer..." << std::endl;

  Mat m1, m2, m3, m4;
  Mat gx, gy, agx, agy;

  // A FAIRE : initialiser le flux vid�o (webcam 0)
  cv::VideoCapture cap(0);

  do
  {
    // A FAIRE : lire une trame (dans la matrice m1),
    cap >> m1;
    const char * name_win = "origin";
    cv::namedWindow(name_win); cv::moveWindow(name_win, 50, 50); cv::imshow(name_win, m1);

    // la convertir en niveaux de gris,
    cvtColor(m1, m1, CV_BGR2GRAY);

    // puis diviser la r�solution par deux
    resize(m1, m1, Size(0, 0), 0.5, 0.5);

    // A FAIRE : filtrage passe-bas
    GaussianBlur(m1, m2, Size(5, 5), 5, 1);
    name_win = "passe-bas";
    cv::namedWindow(name_win); cv::moveWindow(name_win, 800, 50); cv::imshow(name_win, m2);

    Mat laplacien;
    // A FAIRE : calculer le laplacien de m1 (format flottant 32 bits)
    Laplacian(m1, m4, CV_32F, 3, 1, 0, BORDER_DEFAULT);

    // A FAIRE : calculer m3 = m1 - 0.3 * laplacien
    // Attention pi�ge : m1 est de type CV_8U (unsigned char)
    // --> � pr�-convertir en flottant.
    // Puis apr�s calcul, reconvertir le r�sultat en CV_8U
    m1.convertTo(m1, CV_32F);
    m3 = m1 - 0.3 * m4;
    m3.convertTo(m3, CV_8U);
    name_win = "plus-net";
    cv::namedWindow(name_win); cv::moveWindow(name_win, 1200, 50); cv::imshow(name_win, m3);

    // Tant que l'utilisateur n'appuie pas sur une touche
    // + attente de 20 ms � chaque image
  } while (waitKey(20) == -1);

  std::cout << "Fin.\n";
  return 0;
}
