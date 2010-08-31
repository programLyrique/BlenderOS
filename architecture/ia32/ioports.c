#include "ioports.h"

inline void outb(const uint_16 port, const uint_8 byte)
{
	asm volatile ("outb %0,%1" : : "a"(byte), "Nd" (port));
}

inline uint_8 inb(const uint_16 port)
{
	unsigned char byte;
	asm volatile("inb %1,%0" : "=a"(byte) : "Nd"(port));
	return byte;
}

inline void outw(const uint_16 port, const uint_16 word)
{
	asm volatile("outw %0,%1" : : "a"(word), "Nd"(port));
}

inline uint_16 inw(const uint_16 port)
{
	uint_16 word;
	asm volatile("inw %1,%0" : "=a"(word) : "Nd"(port));
	return word;
}

inline void io_wait()
{
	asm volatile("outb %%al, $0x80" : : "a"(0));
	// port 80 is used for chekpoints during POST
	//Linux kernel seems to think it's free for use
}
