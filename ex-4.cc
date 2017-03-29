/**************************************
 ** OPENCV - EXERCICE 4 :            **
 ** Calcul de flux optique           **
 **************************************/
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <iostream>

using namespace cv;


int main(void)
{
  std::cout << "Exercice 4 (flux optique)...\n"
            << "Appuyer sur une touche pour terminer." << std::endl;

  // A FAIRE : changer pour ouvrir la premi�re webcam
  VideoCapture cam(0);

  // I = trame courante, Iprev = trame pr�c�dente
  // flux = flux optique
  Mat I, Iprev, flux;
  unsigned int trame_num = 0;

  do
  {
    // A FAIRE : charger une image � partir de la webcam
    cam >> I;

    if(I.data == nullptr)
      break;

    // A FAIRE : diviser la r�solution par 2 et passer en niveaux de gris
    // [...]
    //pyrDown(I, I);
    imshow("Entree", I);
    cvtColor(I, I, CV_BGR2GRAY);

    // Attends d'avoir lu au moins 2 trames
    if(trame_num > 0)
    {
      // Calcul du flux optique d'apr�s l'algorithme de Farneback
      // (stockage du r�sultat dans la matrice bicanale et flottante "flux")
      // Note : vous pourrez ajuster les param�tres
      // afin d'am�liorer la pr�cision.
      calcOpticalFlowFarneback(Iprev, I, flux,
                               0.5, /* Facteur d'�chelle entre chaque �tage */
                               4,   /* Nombre de niveaux */
                               15,  /* winsize */
                               3,   /* iterations */
                               5,   /* Taille du voisinage pour estim. polynome */
                               1.1, /* Ecart-type filtre gaussien */
                               0    /* Drapeaux */);

      // Affichage du flux optique

      Mat hsv,     // Image au format HSV (� g�n�rer)
          _hsv[3]; // Les 3 composantes H, S, V (s�par�es)


      // Conversion coordonn�e cart�sienne vers polaire
      // (calcul magnitude et direction du flux)
      Mat mag, angle, xy[2];
      split(flux, xy); // S�paration des 2 composantes du flux optiques
      cartToPolar(xy[0], xy[1], mag, angle);

      // A FAIRE : normaliser la magnitude entre 0 et 1.0
      // ...
      normalize(mag, mag, 0, 1.0, NORM_MINMAX);

      // A FAIRE : Calcul d'une couleur pour chaque pixel :
      // - Teinte ([0 - 360�[) = en fonction de la direction du flux
      //  (attention : angle en radians � convertir en degr�s)
      // _hsv[0] = ...
      _hsv[0] = (angle * 180 / CV_PI);

      // - Saturation = 1.0 (compl�tement satur�)
      // _hsv[1] = ...
      _hsv[1] = Mat::ones(Size(I.size()), CV_32F);

      // - Valeur = en fonction de la magnitude du flux
      _hsv[2] = mag; // Luminance

      // A FAIRE : fusionner  les 3 composantes "_hsv"
      // dans une seule matrice "hsv"
      // ...
      merge(_hsv, 3, hsv);

      // A FAIRE : Conversion HSV vers BGR pour l'affichage
      Mat bgr;
      cvtColor(hsv, bgr, CV_HSV2BGR); // Supprimer cette ligne
      // ...

      imshow("flux optique", bgr);
    }

    Iprev = I;
    trame_num++;
  } while (waitKey(30) == -1); // Sortie d�s que appui sur une touche

  std::cout << "Fin : appuyer sur une touche pour terminer." << std::endl;
  waitKey(0);
  return 0;
}
