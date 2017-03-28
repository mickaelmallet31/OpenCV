/**************************************
 ** OPENCV - Exercice 1.1 :          **
 ** Manipulation des matrices        **
 **************************************/


#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

static void print_mat(const cv::Mat &m)
{
  if(m.data)
    std::cout << "m:\n" << m << std::endl;
  else
    std::cout << "m: matrice non initialisée" << std::endl;
}

int main(void)
{
  std::cout << "Exercice 1-1..." << std::endl;

  cv::Mat m;

  // (1) A FAIRE : Définir m comme une matrice 5 x 4 (5 lignes, 4 colonnes),
  //  de type flottant monocal, initialisée à zéro
  m = cv::Mat::zeros(5,4,CV_32F);

  // (2) A FAIRE : Affecter l'élément en ligne 0 et colonne 3 à la valeur 2
  m.at<float>(0,3,0)=2;

  // (3) A FAIRE : Mettre les 4 éléments sur le coin supérieur gauche à 1
  //  (utiliser une zone d'intérêt)
  // ...
  cv::Mat roi = cv::Mat(m, cv::Rect(0,0,2,2));
  roi.setTo(cv::Scalar(1));
  print_mat(m);

  // (4) A FAIRE : Récuperer un pointeur vers la troisième ligne,
  // pour mettre tous ces éléments à 3.0
  float *ptr = m.ptr<float>(2);
  for(int i = 0; i < 4; i++) {
	  *ptr++ = 3.0;
  }

  print_mat(m);

  // (5) A FAIRE : Multiplier tous les éléments de la matrice par deux
  m *= 2;

  print_mat(m);

  std::cout << "Fin.\n";
  return 0;
}
