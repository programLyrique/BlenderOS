/** \brief Pilote d'affichage bas niveau
 * \todo utiliser static volatile uchar *video pour situer la position du
 * charact�re suivant.
 */
#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "../../utils/types.h"
#include "colors.h"

/**Origine de la m�moire vid�o*/
#define VIDEO_MEM 0xB8000
#define COLUMNS 80
#define LINES 25
#define VIDEO_SIZE (COLUMNS * LINES *2)
#define VIDEOLIM (VIDEO_MEM + VIDEO_SIZE)
#define DEFAULT_KATTR 7

#define TAB_SIZE 8

/**Efface l'�cran*/
void cls ();
/**Abaisse l'affichage de nbLines*/
void scrollup(unsigned int nbLines);
/**Affiche le caract�re c � l'�cran � la position courante, puis incr�mente cette position*/
void putchar (unsigned char c);
/**Modifier les attributs d'un charact�re :
 * \param foreground couleur de premier plan
 * \param background couleur d'arri�re plan
 * \param overIntensity surIntensit�
 * \param blink clignotement
 *
 * Il convient d'utiliser, pour une meilleure clart�, les couleurs et attributs d�finis
 * dans colors.h
 */
void setAttribute(char foreground, char background, char overIntensity, char blink);

#endif // SCREEN_H_INCLUDED
