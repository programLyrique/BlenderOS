/** \file string.h
 * \brief Les fonctions de gestion de chaines
 * \todo optimiser avec instructions sp�cifiques du processeur.
 */

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include "types.h"
/**Copie n octets de src vers dest
 *
 * L'impl�mentation est tir�e de la newlib.
 * \todo a optimiser en copiant plusieurs octets � la suite
 */
void * memcpy(void *dest, const void *src, size_t n);

/**Initialise une zone
 *
 * L'impl�mentation est tir�e de la newlib
 * \param s zone � initialiser
 * \param c initialisateur
 * \param taille de la zone
 */
void * memset(void *s, int c, size_t n);

/**Convertit un entier en chaine de charact�res
 * \param buf le buffer de destination
 * \param base la base :
 *          - 'd' �quivaut � d�cimal
 *          - 'x' �quivaut � hexad�cimal
 * \param n entier � convertir
 */
void itoa(char *buf, unsigned long int n, int base);

/**Retourne la longueur d'une chaine C*/
size_t strlen(const char *s);
#endif
