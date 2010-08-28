/** \file pmem.h
 * \brief Définition du gestionnaire de mémoire physique.
 *
 * Contient toutes les fonctions utiles à l'initialisation
 * et au bon fonctionnement du gestionnaire de mémoire.
 * \todo Ajouter une fonction permettant d'allouer plusieurs pages
 * \todo Ajouter une fonction permettant d'allouer plusieurs pages contiguës
 */
#ifndef PMEM_H_INCLUDED
#define PMEM_H_INCLUDED

#define PAGE_SIZE 4096
#include "utils.h"
/** \brief Header décrivant les structures de gestion de la mémoire
 *
 */
struct pmem_header
{
    /** nombre de pages d'où nombre de blocs*/
    unsigned int nbPages;
    /** taille d'un bloc*/
    unsigned int blockSize;
    /**Nombre de pages utilisées ...?...*/
    unsigned int nbPagesUsed;
    /**hauteur de l'arbre binaire*/
    unsigned int binaryHeight;
    /**Adresse de début de la bitmap, la memory map*/
    unsigned int  * mmap;
    /**Adresse du début de l'arbre binaire*/
    unsigned int* binaryTree;
    /**Décalage en bit vers le dernier bit mis à 1, désignant une page allouée*/
    unsigned long firstFreePage;
}__attribute__( (packed));
typedef struct pmem_header pmem_header;

/**L'adresse de début des structures de gestion de la mémoire physique
 * \todo  transformer pmem_adrr en pmem_header
 */
static pmem_header * header=NULL;


/**\brief marque une page comme utilisée
 * \param bit numéro de la page en comptant à partir de 0
 * \todo n'utiliser que les combinaisons de bits
 */
inline void mmap_set(unsigned int bit);
/** \brief marque une page comme non utilisée
 * \param bit numéro du bit en comptant à partir de à
 */
inline void mmap_unset(unsigned int bit);
/** \brief Teste si la page au bit demandé est libre
 * \param bit le numéro de la page à tester, en comptant à partir de 0
 */
inline bool mmap_test(unsigned int bit);
/** \brief Recherche la première page de libre
 * \return l'offset en bit de la première page de libre, -1 si toute la mémoire est occupée
 */
int mmap_first_free ();
/** \brief Marque une région comme utilisée
 * \param baseAddr adresse de début de la région dans la mémoire physique
 * \param taille taille de la région en bits
 */
void pmem_set_region(unsigned int baseAddr, size_t taille);
/** \brief Marque une région de la mémoire physique, une suite de pages, comme inutilisée
 *
 * On optimise cela en allouant ce qui est possible par groupes de 32, soit un int
 * \param baseAddr adresse de début de la région dans la mémoire physique \i pas dans la bitmap
 * \param taille taille de la région en bits
 */
void pmem_unset_region(unsigned int baseAddr, size_t taille);
/** \brief Prépare le gestionnaire de mémoire physique
 *
 * Les structures de données utiles à la gestion de la mémoire physique, c'est-à-dire, du système de pagination, sont
 * initialisées. A appeler en tout premier (sinon erreurs !)
 * \param addr adresse du debut des structures de données.
 * \param tailleMem la taille de la mémoire
 * \param taillePage la taille d'une page
 * \todo Permettre le passage d'une memory map
 */
int pmem_init(void *addr,unsigned long tailleMem, unsigned long taillePage);

/** \brief Alloue et initialise la bitmap
 * \return 0 en cas d'échec
 * \return 0 en cas de succès
 */
int init_mmap();

#endif // PMEM_H_INCLUDED
