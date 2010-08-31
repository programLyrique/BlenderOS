include $(PREFIX)/Variables.mk
TARGET:=start.o multiboot.o
#CC:=gcc -D $(ARCH) -Wall -fno-hosted -m32 -mtune=i586

export PREFIX

all: $(TARGET) 

#DEPRECATED
#start.o: multiboot.asm
#	nasm -f elf -o $(PREFIX)/bin/$@ $^ ;

start.o: start.S
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
#cpp $^| as --warn --32 -mtune=i586 -o $(PREFIX)/bin/$@

multiboot.o:  multiboot.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
.PHONY: clean
clean:
	cd $(PREFIX)/bin
	rm -f $(TARGET)
