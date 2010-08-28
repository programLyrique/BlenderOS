include $(PREFIX)/Variables.mk

OBJ:=gdt.o 

export PREFIX

all: $(OBJ)

gdt.o: gdt.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
.PHONY: clean
clean:
	cd $(PREFIX)/bin
	rm -f $(OBJ)