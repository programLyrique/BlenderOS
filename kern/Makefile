include $(PREFIX)/Variables.mk
OBJ := kernel.o printk.o
#CC=gcc -D $(ARCH) -Wall -fno-hosted -m32 -mtune=i586
#LD=ld -melf_i386 --oformat binary -Ttext 1000 $^-o $@

export PREFIX

all: $(OBJ) 

#mettre la liaison au niveau global, au premier makefile
kernel.o: kernel.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@

printk.o: printk.c 
	$(CC) -c $^ -o $(PREFIX)/bin/$@

.PHONY: clean
clean:
	cd $(PREFIX)/bin
	rm -f $(OBJ)
