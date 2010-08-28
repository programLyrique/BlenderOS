/** \file types.h
 * Définition des types.
 */
 
 #ifndef TYPE_H_INCLUDED
 #define TYPE_H_INCLUDED
 
 #ifdef IA32
 #include "../architecture/ia32/ia32_types.h"
 #else
 #error "Pas de definition des types pour l'architecture cible"
 #endif
 
 typedef unsigned int bool;
 #define true 1
 #define false 0
 
 //NULL :
 #define NULL  ((void *) 0)
 
 #endif