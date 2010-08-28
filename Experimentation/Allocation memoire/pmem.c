#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "pmem.h"

inline void mmap_set(unsigned int bit)
{
    header->mmap[bit / 32] |= (1 << (bit % 32));
}
inline void mmap_unset(unsigned int bit)
{
    header->mmap[bit / 32] &= (1 << (bit % 32));
}
inline bool mmap_test(unsigned int bit)
{
    return header->mmap[bit/32] &  (1 << (bit % 32));
}
//A mettre en inline ?
int mmap_first_free ()
{
    unsigned int i=0, j=0;
	for (; i< header->nbPages / 32; i++)
		if (header->mmap[i] != 0xffffffff)
			for (j=0; j<32; j++)
			{

				int bit = 1 << j;
				if (! (header->mmap[i] & bit) )
					return i*32+j;
			}

	return -1;
}

void pmem_set_region(unsigned int baseAddr, size_t taille)
{
    int align = baseAddr / PAGE_SIZE;
	int blocks = taille / PAGE_SIZE;

	for (; blocks>0; blocks--) {
		mmap_set (align++);
		header->nbPagesUsed++;
	}
	mmap_set(align);

    /*unsigned int i=0;
    for(;i < taille;i++)
    {
        mmap_set(baseAddr+i);//Implémentation absolument pas performante.
        header->nbPagesUsed++;
    }*/
    /*int align = baseAddr >> 5 ;//Adresse de base alignée sur 32 bits en mots
    int begin = taille - baseAddr +  align;//On obtient les permier bits
    int middle = (taille-begin) >> 5;//On obtient le nombre de mots
    int end = taille - middle;//On obtient le nombre restant de bits
    int i=0;
    for(;i< begin;i++)
    {
        mmap_set(baseAddr+i);
        header->nbPagesUsed++;
        printf("\tbegin");
    }
    for(i=align;i < middle;i++)
    {
        header->mmap[align+i]=0xffffffff;
        printf("\tmiddle");
        header->nbPagesUsed+=32;
    }
    for(i=0;i < end;i++)
    {
        mmap_set(baseAddr+middle*32+i);
        header->nbPagesUsed++;
        printf("\tend");
    }
    //ajouter des tests de non dépassement de la mémoire
    printf("\nBegin : %d, Middle : %d End : %d . Taille calculee :%d", begin, middle, end, begin + middle*32+end);*/
}
void pmem_unset_region(unsigned int baseAddr, size_t taille)
{

}
int pmem_init(void *addr, unsigned long tailleMem, unsigned long taillePage)
{
    header = addr;
    header->nbPages = tailleMem/taillePage;
    header->blockSize=0;
    header->nbPagesUsed=0;
    header->binaryHeight=0;
    header->binaryTree=NULL;
    header->firstFreePage=0;

    unsigned int tailleHeader=sizeof(pmem_header);
    printf("\nTaille du header : %d", tailleHeader);
    /*
        On alloue la bitmap après le heaader, en veillant à l'aligner sur 32 bits (en 32 bits)
        à adapter de façon générique (modulo...)
        On cast le pointeur sur pm_header
    */
    header->mmap = (unsigned int *) (header+tailleHeader+(2*tailleHeader-32));
    if(!init_mmap())
        return 0;
    return 1;
}

int init_mmap()
{
    //inventé, mais devra tenir compte de la memory map passéé par Grub
    pmem_set_region(0, PAGE_SIZE*10);
    //pmem_set_region(PAGE_SIZE*50, 50*PAGE_SIZE);
    return 1;
}

void print_mmap()
{
    unsigned int i=0, begin=0, end=0, suite=0;
    printf("\n|");
    for(i=0; i < header->nbPages;i++)
    {
        if(mmap_test(i))
            putchar('¤');
        else
            putchar('-');
    }
    putchar('|');
    putchar('\n');
    for(i=0;i < header->nbPages/32;i++)
    {
        printf("%x|", header->mmap[i]);
    }
    //Afficher un texte
    printf("\nAlloue : ");
    for(i=0;i < header->nbPages;i++)
    {
        int test =mmap_test(i);
        if(test && suite)//on est dans une suite de mémoire allouée
        {
            end++;
        }
        else if(suite)//on est arrive à la fin d'une suite de bloc allouée
        {
            printf(" [%d - %d] ", begin, end);
            suite=0;
        }
        else if(test)//C'est le début d'une suite de bloc allouée
        {
            begin=i;
            end=begin;
            suite=1;
        }
    }
    printf("\nPages utilisées: %d", header->nbPagesUsed);

}
