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

  // A FAIRE : changer pour ouvrir la première webcam
  VideoCapture cam("./data/sequence.mpg");

  // I = trame courante, Iprev = trame précédente
  // flux = flux optique
  Mat I, Iprev, flux;
  unsigned int trame_num = 0;

  do
  {
    // A FAIRE : charger une image à partir de la webcam
    cam >> I;

    if(I.data == nullptr)
      break;

    // A FAIRE : diviser la résolution par 2 et passer en niveaux de gris
    // [...]

    imshow("Entrée", I);

    // Attends d'avoir lu au moins 2 trames
    if(trame_num > 0)
    {
      // Calcul du flux optique d'après l'algorithme de Farneback
      // (stockage du résultat dans la matrice bicanale et flottante "flux")
      // Note : vous pourrez ajuster les paramètres
      // afin d'améliorer la précision.
      calcOpticalFlowFarneback(Iprev, I, flux,
                               0.5, /* Facteur d'échelle entre chaque étage */
                               4,   /* Nombre de niveaux */
                               15,  /* winsize */
                               3,   /* iterations */
                               5,   /* Taille du voisinage pour estim. polynome */
                               1.1, /* Ecart-type filtre gaussien */
                               0    /* Drapeaux */);

      // Affichage du flux optique

      Mat hsv,     // Image au format HSV (à générer)
          _hsv[3]; // Les 3 composantes H, S, V (séparées)


      // Conversion coordonnée cartésienne vers polaire
      // (calcul magnitude et direction du flux)
      Mat mag, angle, xy[2];
      split(flux, xy); // Séparation des 2 composantes du flux optiques
      cartToPolar(xy[0], xy[1], mag, angle);

      // A FAIRE : normaliser la magnitude entre 0 et 1.0
      // ...

      // A FAIRE : Calcul d'une couleur pour chaque pixel :
      // - Teinte ([0 - 360°[) = en fonction de la direction du flux
      //  (attention : angle en radians à convertir en degrés)
      // _hsv[0] = ...

      // - Saturation = 1.0 (complétement saturé)
      // _hsv[1] = ...

      // - Valeur = en fonction de la magnitude du flux
      _hsv[2] = mag; // Luminance

      // A FAIRE : fusionner  les 3 composantes "_hsv"
      // dans une seule matrice "hsv"
      // ...



      // A FAIRE : Conversion HSV vers BGR pour l'affichage
      Mat bgr = I; // Supprimer cette ligne
      // ...

      imshow("flux optique", bgr);
    }

    Iprev = I;
    trame_num++;
  } while (waitKey(30) == -1); // Sortie dès que appui sur une touche

  std::cout << "Fin : appuyer sur une touche pour terminer." << std::endl;
  waitKey(0);
  return 0;
}




