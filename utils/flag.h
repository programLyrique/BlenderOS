/** \file flag.h
 * \brief Fournit des macros de manipulation de flags
 *
 * Manipule des bits d'un ensemble plus grand
 * \author Pierre Donat-Bouillud
 * \date
 */
#ifndef FLAG_H_INCLUDED
#define FLAG_H_INCLUDED

#include "types.h"

 /**Vérifie si le le bit dans flags est à 1*/
 #define CHEK_FLAG(flags, bit) ((flags) & (1 << (bit)))
 
 /**Positionne le bit dans flags à 1*/
 #define SET_FLAG(flags, bit) ((flags)  |= (1 << (bit)))
 
 /**Positionne le bit dans flags à 0*/
 #define UNSET_FLAG(flags, bit) ((flags)  &= ~(1 << (bit)))
 
 union octets_uint32 
 {
	 uint_32 uint32;
	 uint_8  ch0;
	 uint_8 ch1;
	 uint_8 ch2;
	 uint_8 ch3;
 };
 typedef union octets_uint32 octets_uint32;
 /** Extrait l'octet OCTET en partant de l'octet le moin significatif d'un uint32
  * \todo en l'état, cette macro ne fonctionne : la modifier
  */
 #define EXTRACT_OCTET(value, octet) ( ((octets_uint32) (value)).ch1)
 
#endif