/** \file assert.h
   * Fournit une macro permettant de lancer une assertion.
   * \todo Créer une focntion halte ou abort pour arréter brutalement le 
   * système.
   */
   
#ifndef ASSERT_H_INCLUDED
#define ASSERT_H_INCLUDED

#define ASSERT(condition) if(!(condition)) \
	{ \
		printk("\nASSERT : "#condition" -> False");\
		while(1) \
			{asm volatile ("hlt");}\
	}

#endif