/* The linker script for ld.
 *
 */
 
 /*The first executed byte is here, i.e. in multiboot.asm*/
 ENTRY(_start)
 
 /*OUTPUT_FORMAT(elf32-i386)*/
 
 /* The multiboot structure has to be localized at the beginning of the kernel.
  * -> Is-it really useful with the SECTION and its part multiboot ?
  */
 /*STARTUP(start.o)*/
 
 OUTPUT(BlenderOS_Kernel)
 
  /*TODO : Add an INPUT command where putting all the objet files
   * A coupler avec SEARCH_DIR(PATH) où PATH=../bin ?
   */
  SECTIONS
  {
	  /*The adress where the kernel is loaded*/
	. = 0x200000;
	/*Utiliser .=.; pour empêcher le linker de placer des sections orphelines
		avant notre symbole
		b signifie ici beginning
		e 		   end
		*/
	__b_load	= .;
	
	/*We put the multiboot header at the beginning of the kernel
	but in the .text section, otherwise, stuffs won't go well !*/
	
	__b_kernel = . ;
	.text : 
	{ 
		*(.multiboot)
		bin/kernel.o(.text)
		*(.text)
		PROVIDE(_etext = .);
	}
	
	.data :
	{ 
		*(.data) 
		PROVIDE(_edata = .);
	}
	
	.rodata : 
	{ 
		*(.rodata) 
		PROVIDE(_rodata = . );
	}
	
	__e_load = . ;
	.bss : 
	{ 
		*(COMMON)
		*(.bss)
		PROVIDE(_ebss = . );
	}
	___e_kernel = . ;
	.comment : { *(.comment) }
  }
  