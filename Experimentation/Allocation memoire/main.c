/**  \mainpage Le testeur du gestionnaire de mémoire physique de BlenderOS
 * \author Pierre Donat-Bouillud
 *
 * \section Objectifs
 *
 * Ce programme permet de tester l'algorithme de gestion de la mémoire
 * physique de BlenderOS de manière pratique.
 * \section Moyens
 *
 * Ce programme, à travers une interface en console, va à l'aide de tests aléatoires, puis simulant quelques comportements
 * attendus de vrais programmes, tester la faisabilité et les performances du gestionnaire.
 */
#include <stdio.h>
#include <stdlib.h>

#include "pmem.h"

/** Taille maximale de la mémoire émulée */
#define MAX_MEM 33554432

/** Point d'entrée du programme
 *
 */
int main()
{
    unsigned long tailleMem=0;
    unsigned int taillePage=0;
    char * memPhysique=NULL;
    printf("Programme de test de l'allocateur memoire de BlenderOS\n");
    printf("Le programme alloue un buffer qui servira de memoire physique \n\
           puis cree sa structure de gestion de la memoire, et alloue des pages, en desalloue, a l'aide de taches virtuelles.\n");
    printf("Taille d'un mot : %ld octets\n", sizeof(unsigned int));
    printf("Entrez la taille de la memoire a emuler (limitee a 32 Mo, soit 33554432 o) en octets:\t");
    scanf("%ld", &tailleMem);
    if (tailleMem > MAX_MEM)
    {
        printf("Impossible d'emuler plus de 32 Mo");
        exit(EXIT_FAILURE);
    }
    //Allocation du buffer qui va représenter la mémoire physique
    if ((memPhysique = malloc(tailleMem * sizeof(char))) == NULL)
    {
        printf("Impossible d'allouer la mémoire.");
        exit(EXIT_FAILURE);
    }
    printf("Entrez la taille d'une page (4O96 o est recommende) en octets: \t");
    scanf("%d", &taillePage);
    if (taillePage > tailleMem)
    {
        printf("La taille de la page depasse la taille de la memoire disponible");
        exit(EXIT_FAILURE);
    }

    if(!pmem_init(memPhysique, tailleMem, taillePage))
    {
        printf("Impossible d'initialiser la mémoire physique.");
        exit(EXIT_FAILURE);
    }
    printf("\nDebut des tests d'allocation memoire.\n\n");
    fflush(stdout);//pour pouvoir afficher le dernier message.
    print_mmap();
    fflush(stdout);
    return EXIT_SUCCESS;
}
