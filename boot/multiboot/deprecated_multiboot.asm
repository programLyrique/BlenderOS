global _start, start
extern kmain
;extern stack;A définir dans le linker script !

;We load the kernel thanks to Grub and the Multiboot Specification
;It is also time to define a new stack for the kernel.
%define STACK_SIZE 0x4000;une pile de 16 Ko
%define MULTIBOOT_HEADER_MAGIC  0x1BADB002
%define MULTIBOOT_HEADER_FLAGS	0x00000003
%define CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

%define stack 0x3000000;Juste pour que ça compile, mais ne fonctionnera !

;-- Entry point
_start:
	jmp start


;-- Multiboot header --
align 4

multiboot_header:
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd CHECKSUM     
;--/Multiboot header --

start:
	mov ebp, stack + STACK_SIZE 
	mov esp, ebp
	;Lancement du kernel
	push ebx
	push eax
	call kmain

	cli ; stop interrupts
	hlt ; halt the CPU

