/** \file assert.h
   * Fournit une macro permettant de lancer une assertion.
   * \todo Cr�er une focntion halte ou abort pour arr�ter brutalement le 
   * syst�me.
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