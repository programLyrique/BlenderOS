#TODO :
#Il faudrait effectuer la phase de liaison seulement une bonne fois pour toute
# à la fin, avec tous les .o créés dans le répertoire bin
export PREFIX:=$(PWD)
TARGET:=BlenderOS_Kernel

all: $(TARGET) 

.PHONY : boot kernel userland drivers architecture clean

BlenderOS_Kernel: boot architecture utils drivers kernel
	ld -melf_i386 -Tsupport/blenderos.ld bin/*.o -Map=BlenderOS.map
	#Il faudra améliorer la sélection des .o à lier
	#cat boot/bootsect kern/kernel /dev/zero | dd of=image bs=512 count=2880

boot: 
	$(MAKE) -C boot
	
kernel: 
	$(MAKE) -C kern
		
utils:
	$(MAKE) -C utils

userland:
	$(MAKE) -C userland

drivers:
	$(MAKE) -C drivers

architecture:
	$(MAKE) -C architecture

clean:
	rm -fr bin/*.o
	rm -fr  $(TARGET) *.o
	$(MAKE) -C boot clean
	$(MAKE) -C architecture clean
	$(MAKE) -C utils clean
	$(MAKE) -C kern clean
	$(MAKE) -C drivers clean
	$(MAKE) -C userland clean
