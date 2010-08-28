/* multiboot.h - Multiboot header file. */
/* Copyright (C) 1999,2003,2007,2008,2009  Free Software Foundation, Inc.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to
*  deal in the Software without restriction, including without limitation the
*  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
*  sell copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
*  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
*  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/* Modified in 2010 to be used in BlenderOS.
* Taken from multiboot specification.
*/

/** \file multiboot.h
 * \brief Permet le boot avec un chargeur r�pondant � la sp�cification multiboot
 *
 * boot.asm contient le code en assembleur nasm de l'header multiboot
 *
 *
 * \todo multiboot.asm utiliser toutes les informations pass�es par le chargeur
 * \todo multiboot.asm D�finir une nouvelle pile plus sure.
 * \todo ajouter fonction qui recopie � un endroit s�r (dans l'espace du noyau par exemple ) la structure multiboot_info apr�s v�rification
 * ou la disperser en diverses structures selon les informations
 * \todo ajouter une fonction (ou des ...) d'affichage des informations pass�es par le chargeur multiboot
 */

#ifndef MULTIBOOT_HEADER
#define MULTIBOOT_HEADER 1

#include "multiboot.h"
#include "../../utils/string.h"
#include "../../utils/types.h"

/* This should be in %eax. */
#define MULTIBOOT_BOOTLOADER_MAGIC              0x2BADB002

/* The bits in the required part of flags field we don't support. */
#define MULTIBOOT_UNSUPPORTED                   0x0000fffc

/* Alignment of multiboot modules. */
#define MULTIBOOT_MOD_ALIGN                     0x00001000

/* Alignment of the multiboot info structure. */
#define MULTIBOOT_INFO_ALIGN                    0x00000004


/* Flags to be set in the 'flags' member of the multiboot info structure. */

/* is there basic lower/upper memory information? */
#define MULTIBOOT_INFO_MEMORY                   0x00000001
/* is there a boot device set? */
#define MULTIBOOT_INFO_BOOTDEV                  0x00000002
/* is the command-line defined? */
#define MULTIBOOT_INFO_CMDLINE                  0x00000004
/* are there modules to do something with? */
#define MULTIBOOT_INFO_MODS                     0x00000008

/* These next two are mutually exclusive */

/* is there a symbol table loaded? */
#define MULTIBOOT_INFO_AOUT_SYMS                0x00000010
/* is there an ELF section header table? */
#define MULTIBOOT_INFO_ELF_SHDR                 0X00000020

/* is there a full memory map? */
#define MULTIBOOT_INFO_MEM_MAP                  0x00000040

/* Is there drive info? */
#define MULTIBOOT_INFO_DRIVE_INFO               0x00000080

/* Is there a config table? */
#define MULTIBOOT_INFO_CONFIG_TABLE             0x00000100

/* Is there a boot loader name? */
#define MULTIBOOT_INFO_BOOT_LOADER_NAME         0x00000200

/* Is there a APM table? */
#define MULTIBOOT_INFO_APM_TABLE                0x00000400

/* Is there video information? */
#define MULTIBOOT_INFO_VIDEO_INFO               0x00000800


typedef unsigned short          multiboot_uint16_t;
typedef unsigned int            multiboot_uint32_t;
typedef unsigned long long      multiboot_uint64_t;


/**The symbol table for a.out. */
struct multiboot_aout_symbol_table
{
multiboot_uint32_t tabsize;
multiboot_uint32_t strsize;
multiboot_uint32_t addr;
multiboot_uint32_t reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

/** The section header table for ELF. */
struct multiboot_elf_section_header_table
{
multiboot_uint32_t num;
multiboot_uint32_t size;
multiboot_uint32_t addr;
multiboot_uint32_t shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

/** \brief La structure contient les informations donn�es par le  secteur de boot
 *
 */
struct multiboot_info
{
/** Multiboot info version number */
multiboot_uint32_t flags;

/** Available memory from BIOS */
multiboot_uint32_t mem_lower;
multiboot_uint32_t mem_upper;

/*** "root" partition */
multiboot_uint32_t boot_device;

/** Kernel command line */
multiboot_uint32_t cmdline;

/** Boot-Module list */
multiboot_uint32_t mods_count;
multiboot_uint32_t mods_addr;

union
{
 multiboot_aout_symbol_table_t aout_sym;
 multiboot_elf_section_header_table_t elf_sec;
} u;

/** Memory Mapping buffer */
multiboot_uint32_t mmap_length;
multiboot_uint32_t mmap_addr;

/** Drive Info buffer */
multiboot_uint32_t drives_length;
multiboot_uint32_t drives_addr;

/** ROM configuration table */
multiboot_uint32_t config_table;

/** Boot Loader Name */
multiboot_uint32_t boot_loader_name;

/** APM table */
multiboot_uint32_t apm_table;

/** Video */
multiboot_uint32_t vbe_control_info;
multiboot_uint32_t vbe_mode_info;
multiboot_uint16_t vbe_mode;
multiboot_uint16_t vbe_interface_seg;
multiboot_uint16_t vbe_interface_off;
multiboot_uint16_t vbe_interface_len;
}__attribute__((packed));
typedef struct multiboot_info multiboot_info_t;

/** La memory map fournit par l'appel � une fonction du BIOS*/
struct multiboot_mmap_entry
{
multiboot_uint32_t size;
multiboot_uint64_t addr;
multiboot_uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
multiboot_uint32_t type;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

/** Les modules charg�es*/
struct multiboot_mod_list
{
/** the memory used goes from bytes 'mod_start' to 'mod_end-1' inclusive */
multiboot_uint32_t mod_start;
multiboot_uint32_t mod_end;

/** Module command line */
multiboot_uint32_t cmdline;

/** padding to take it to 16 bytes (must be zero) */
multiboot_uint32_t pad;
}__attribute__((packed));
typedef struct multiboot_mod_list multiboot_module_t;


//Les fonctions
/** \brief Stocke et v�rifie les informations du standard multiboot
 * \param info pointeur sur la  structure multiboot fournie par le chargeur
 */
int init_multiboot_info(multiboot_info_t * info);
/** \brief Permet d'utiliser la structure multiboot_info stcck�e � l'abri
 * \param multiboot_info_t la structure multiboot_info
 * \return 0 en cas de succ�s, 1 si et une table de symbole pour out et une autre pour elf
 * sont d�finies.
 */
multiboot_info_t * get_multiboot_info();

#define MEM_LOWER 0
#define MEM_UPPER 1
/** \brief Renseigne sur la quantit� de m�moire disponible
 *
 * <p> La m�moire basse commence � l'adresse 0, tandis que la m�moire haute commence
 * � partir des 1 Mo La valeur maximale  pour la m�moire basse est de 640 Ko.
 * La valeur retourn�e pour la m�moire haute est au plus l'adresse du
 * premier trou dans la m�moire, mais les 1 Mo de d�but. Il n'est pas garanti que ce
 * soit cette valeur. </p>
 * <p>Il est donc conseill� d'utiliser la memory map pour une plus pr�cise d�tection de
 * la m�moire disponible</p>
 * \param mem type de m�moire demand�e :
 *			- MEM_LOWER pour la m�moire basse
 *			- MEM_UPPER pour la m�moire haute
 * \return la quantit� de m�moire d�sign�e, 0 en cas d'erreur, le tout en ko
 */
unsigned int get_mem(int mem);

#define DRIVE 0
#define PART1 1
#define PART2 2
#define PART3 3
/** \brief Renseigne sur la partition, et le disque dur d�sign� comme racine
 * \param partition_level  indique quel information pr�cise est demand� :
 *					- DRIVE renvoie le num�ro du disque dur
 *					- PART1 renvoie le num�ro de la partition
 *					- PART2 renvoie le num�ro de la partion dans les partitions
 *						de niveau 1 (partition BSD dans partition de type DOS par
 *							exemple)
 *					- PART3 idem
 * Les partitions DOS �tendus ne sont pas consid�r�es comme des sous partitions
 * \return 0xFF en cas d'erreur, par exemple de non existence de partition au niveau
 * demand�
 */
uint_8 get_boot_device(unsigned int partition_level);
/** \brief Fournit la ligne de commande donn�e en param�tres au bootloader
 * \return la ligne de commande, ou NULL si elle n'est pas pr�sente
 */
char * get_cmdline();
/** \brief Fournit le nombre de modules charg�s
 */
unsigned int get_nbModules();
/** \brief Fournit la liste des modules
 * \return renvoie un pointeur sur le d�but d'un tableau de longueur get_nbModules()
 * et de taille d'une case sizeof(multiboot_module_t)
 * vaut NULL si elle n'existe pas.
 */
multiboot_module_t * get_modules();
/** \brief Fournit la taille de la memory map renseign�e par le bios
 * \return 0 si elle n'existe pas
 */
unsigned int get_mmap_length();
/** \brief Renvoie la memory map renseign�e par le BIOS
 *
 * La memory map est un tableau de taille get_mmap_length() de zones de m�moire, chacune contenant
 * sa taille, son adresse de base, son type.
 * \return un pointeur sur la premi�re de ces zones, ou NULL si aucune memory map n'est
 * disponible
 */
multiboot_memory_map_t * get_mmap();
/** \brief It�rateur qui permet de parcourir la memory map
 * \param mmap pointeur vers le d�but de la memory map
 * \param length longuer de la m�mory map
 * \param i zone sur laquelle it�rer
 *
 * \example \code multiboot_memory_map_t *mm;
 * mmap_foreach(get_mmap(), get_mmap_length(), mm) { kprintf("type = ox%x\n", (unsigned) mmap->type); }
 */
#define mmap_foreach(mmap, length, i) for (i = (multiboot_memory_map_t *) (mmap);\
                (unsigned long) i < (mmap) + (length);\
                i = (multiboot_memory_map_t *) ((unsigned long) i\
                                         + i->size + sizeof (i->size)))

/** \brief D�crit un disque dur
 *
 */
struct multiboot_drive_t
{
	/**Taille de la structure avec tous les ports, peut ne pas �tre exactement �gal �
	 * 10 + 2 * nombre de ports*/
	multiboot_uint32_t size;
	/**Num�ro du disque dur*/
	char drive_number;
	/**Mode d'acc�s utilis� :
	 *	- CHS (cylinder/head/sector) : 0
	 *	- LBA (Logical Block Adressing) : 1
	 */
	char drive_mode;
	/**Nombre de cylindres*/
	multiboot_uint16_t drive_cylinders;
	/**Nombre de t�tes*/
	char drive_heads;
	/**Nombre de  secteurs par piste*/
	char drive_sectors;
	/**D�but d'un tableau renseignant sur les ports permettant l'utilisation du disque
	 * dur, cod�s sur deux octets, non sign�s. La liste des ports est termin�e par un
	 * z�ro.
	 */
	multiboot_uint16_t drive_ports;
}__attribute__((packed));
typedef struct multiboot_drive_t multiboot_drive_t;

/** \brief Fournit la longueur totale des renseignements sur les disques durs.
*/
unsigned int get_drives_length();

/** \brief Fournit un pointeur vers le premier disque dur
 *
 */
multiboot_drive_t * get_drive();

/**\brief retourne l'adresse de la table de configuration dans la ROM retourner par
 *l'appel du BIOS GET CONFIGURATION
 * \todo Cr�er une structure repr�sentant cette structure
 * \return void* � pr�ciser donc
 */
void *  get_config_table();

#endif /* MULTIBOOT_HEADER */
