/** \file bochs_port.h
 * Pilote pour gérer le port 0xe9 de Bochs
 * 
 * Il s'agit d'un port de débuggage, qui affichera des informations dans la console de débuggage.
 */
 
 #ifndef BOCHS_PORT_H_INCLUDED
 #define BOCHS_PORT_H_INCLUDED
 
 #ifdef IA32
 #include "../../architecture/ia32/ioports.h"
 #else
 #error "Pas de support pour les ports du processeur."
 #endif
 
 #include "../../utils/errno.h"
 
 
 /** \brief Ecrit un caractère à travers le port de déboggage*/
 void bochs_putchar(const unsigned char c);
 /** \brief Ecrit une chaine sur le port de déboggage
  * \param str pointeur sur la chaine de caractère
  * \return BO_OK en cas de succès
  * \return BO_EINVAL si str baut NULL
  */
int bochs_puts(const char * str);

/** \brief Puts a breakpoint for the Bochs debugger*/
void bochs_breakpoint();
 
 #endif