/** Définit un "early printk"
 * \todo Copier stdarg dans les sources de l'OS
 * \todo Ajouter un putk (ou kput...) : afficher rapidement une chaine non formatée
 * \todo Ajouter préfixes : définitions telles que _KWARN "WARNING : "
 */
#ifndef PRINTK_H_INCLUDED
#define PRINTK_H_INCLUDED

#include "../utils/types.h"
#include "../drivers/text/screen.h"
#include "../utils/string.h"
#include "../drivers/text/colors.h"



/** Affiche une chaine de charactère formatée
 *
 * Supporte les formateurs d, u, x, p et s
 */
void printk (const char *format, ...);


#endif
