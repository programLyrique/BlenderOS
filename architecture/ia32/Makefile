include $(PREFIX)/Variables.mk

OBJ:=gdt.o ioports.o

export PREFIX

all: $(OBJ)

gdt.o: gdt.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@

ioports.o: ioports.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
.PHONY: clean
clean:
	cd $(PREFIX)/bin
	rm -f $(OBJ)