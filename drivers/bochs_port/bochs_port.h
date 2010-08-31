/** \file bochs_port.h
 * Pilote pour g�rer le port 0xe9 de Bochs
 * 
 * Il s'agit d'un port de d�buggage, qui affichera des informations dans la console de d�buggage.
 */
 
 #ifndef BOCHS_PORT_H_INCLUDED
 #define BOCHS_PORT_H_INCLUDED
 
 #ifdef IA32
 #include "../../architecture/ia32/ioports.h"
 #else
 #error "Pas de support pour les ports du processeur."
 #endif
 
 #include "../../utils/errno.h"
 
 
 /** \brief Ecrit un caract�re � travers le port de d�boggage*/
 void bochs_putchar(const unsigned char c);
 /** \brief Ecrit une chaine sur le port de d�boggage
  * \param str pointeur sur la chaine de caract�re
  * \return BO_OK en cas de succ�s
  * \return BO_EINVAL si str baut NULL
  */
int bochs_puts(const char * str);

/** \brief Puts a breakpoint for the Bochs debugger*/
void bochs_breakpoint();
 
 #endif