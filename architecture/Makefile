include $(PREFIX)/Variables.mk

#TODO : fournir un m�canisme pour choisir selon ARCH l'archictecture � compiler
TARGET=ia32

export PREFIX

all: $(TARGET)

.PHONY:ia32
ia32:
	make -C ia32/
	
.PHONY: clean
clean:
	make -C $(TARGET)/ clean