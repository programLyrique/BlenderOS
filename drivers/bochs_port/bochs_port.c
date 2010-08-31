#include "bochs_port.h"
#include "../../architecture/ia32/ioports.h"
 void bochs_putchar(const unsigned char c)
 {
	 outb(0xe9, c);
 }
 
int bochs_puts(const char * str)
 {
	 if (!str)
	 {
		 while(*str != '\0')
		 {
			 outb(0xe9, *str);
			 str++;
		 }
		 return BOS_OK;
	 }
	 else
		 return -BOS_EINVAL;
 }
 
 void bochs_breakpoint()
 {
	 outw(0x8A00, 0x8A00);
	 outw(0x8A00, 0x8AE0);
 }