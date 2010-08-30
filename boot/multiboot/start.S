/* start.S - bootstrap the kernel */
/* Copyright (C) 1999, 2001  Free Software Foundation, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#define ASM_FILE        1

/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif

/* The size of our stack (16KB). */
#define STACK_SIZE                      0x4000

/* The flags for the Multiboot header.  On utilise le format elf.*/
#define MULTIBOOT_HEADER_MAGIC  0x1BADB002
# define MULTIBOOT_HEADER_FLAGS         0x00000003

	/*Le multiboot header doit se trouver au début du noyau (4096 premiers
	octets : on utilise alors un linker script, blenderos.ld, voir dans support*/
     .section ".multiboot"

     .globl  start, _start
start:
_start:
     jmp     multiboot_entry

     /* Align 32 bits boundary. */
     .align  4

     /* Multiboot header. */
multiboot_header:
     /* magic */
     .long   MULTIBOOT_HEADER_MAGIC
     /* flags */
     .long   MULTIBOOT_HEADER_FLAGS
     /* checksum */
     .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

multiboot_entry:
     /* Initialize the stack pointer. */
     movl    $(stack + STACK_SIZE), %ebp
     movl 	%ebp, %esp

     /* Reset EFLAGS. */
     pushl   $0
     popf

     /* Push the pointer to the Multiboot information structure. */
     pushl   %ebx
     /* Push the magic value. */
     pushl   %eax

     /* Now enter the C main function... */
     call    EXT_C(kmain)

     cli
     hlt


     /* Our stack area. */
     .comm   stack, STACK_SIZE
