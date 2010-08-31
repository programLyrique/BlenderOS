/** \mainpage
 * BlenderOS est un syst�me d'exploitation qui veut fournir un environnement id�al
 * pour le graphisme, en particulier la 3D, avec le logiciel Blender.
 * Il peut-�tre qualifi� de Unix-like, au moins du point de vue utilisateur.
 * \todo Cr�er des macros pour printk avec un pr�fixe tel que _KWARNING="Attention"...
 * \todo Cr�er fonction pour afficher OK, ou l'inverse [!!] ?
 */

/** \file kernel.c
 * \author Pierre Donat-Bouillud
 * \date
 * \todo appeler la fonction qui utilise et explote le multiboot header
 * \todo mieux g�rer les inclusions de fichiers
 * \todo Cr�er une fonction d'affichage plus rapide, sans formatage.
 */
 #include "../boot/multiboot/multiboot.h"
 #include "printk.h"
 //Abstraire de l'architecture l'effacement de l'�cran
 #include "../drivers/text/screen.h"
 #include "../drivers/bochs_port/bochs_port.h"


 /** \brief La fonction d'entr�e du noyau
  *
  * Les param�tres sont ceux fournis par le chargeur r�pondant
  *  A� la sp�cification multiboot
  */
 void kmain(unsigned long magic, unsigned long addr)
 {
	 cls();
	printk("Entering BlenderOS.\nLoading boot information.\n");
	 printk("Magic is %x and addr is %p.", magic, addr);
	 bochs_puts("Testing Bochs puts.\nIt seems to go well !"); 
	 //On v�rifie si le noyau a �t� charg� par un chargeur multiboot
	 if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
	 {
		 printk("\nThe loader has to be multiboot standard compliant : wrong magic := %x.", magic);
		 return;
	 }
	init_multiboot_info((multiboot_info_t *)addr);
	 printk("\nLower mem: %d and upper mem %d.", get_mem(MEM_LOWER), get_mem(MEM_UPPER));
 }
