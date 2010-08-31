/** \mainpage
 * BlenderOS est un système d'exploitation qui veut fournir un environnement idéal
 * pour le graphisme, en particulier la 3D, avec le logiciel Blender.
 * Il peut-être qualifié de Unix-like, au moins du point de vue utilisateur.
 * \todo Créer des macros pour printk avec un préfixe tel que _KWARNING="Attention"...
 * \todo Créer fonction pour afficher OK, ou l'inverse [!!] ?
 */

/** \file kernel.c
 * \author Pierre Donat-Bouillud
 * \date
 * \todo appeler la fonction qui utilise et explote le multiboot header
 * \todo mieux gérer les inclusions de fichiers
 * \todo Créer une fonction d'affichage plus rapide, sans formatage.
 */
 #include "../boot/multiboot/multiboot.h"
 #include "printk.h"
 //Abstraire de l'architecture l'effacement de l'écran
 #include "../drivers/text/screen.h"
 #include "../drivers/bochs_port/bochs_port.h"


 /** \brief La fonction d'entrée du noyau
  *
  * Les paramétres sont ceux fournis par le chargeur répondant
  *  A  la spécification multiboot
  */
 void kmain(unsigned long magic, unsigned long addr)
 {
	 cls();
	printk("Entering BlenderOS.\nLoading boot information.\n");
	 printk("Magic is %x and addr is %p.", magic, addr);
	 bochs_puts("Testing Bochs puts.\nIt seems to go well !"); 
	 //On vérifie si le noyau a été chargé par un chargeur multiboot
	 if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	 {
		 printk("\nThe loader has to be multiboot standard compliant : wrong magic := %x.", magic);
		 return;
	 }
	init_multiboot_info((multiboot_info_t *)addr);
	 printk("\nLower mem: %d and upper mem %d.", get_mem(MEM_LOWER), get_mem(MEM_UPPER));
 }
