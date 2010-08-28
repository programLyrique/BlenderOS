/** \file string.h
 * \brief Les fonctions de gestion de chaines
 * \todo optimiser avec instructions spécifiques du processeur.
 */

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include "types.h"
/**Copie n octets de src vers dest
 *
 * L'implémentation est tirée de la newlib.
 * \todo a optimiser en copiant plusieurs octets à la suite
 */
void * memcpy(void *dest, const void *src, size_t n);

/**Initialise une zone
 *
 * L'implémentation est tirée de la newlib
 * \param s zone à initialiser
 * \param c initialisateur
 * \param taille de la zone
 */
void * memset(void *s, int c, size_t n);

/**Convertit un entier en chaine de charactères
 * \param buf le buffer de destination
 * \param base la base :
 *          - 'd' équivaut à décimal
 *          - 'x' équivaut à hexadécimal
 * \param n entier à convertir
 */
void itoa(char *buf, unsigned long int n, int base);

/**Retourne la longueur d'une chaine C*/
size_t strlen(const char *s);
#endif
