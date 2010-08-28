include $(PREFIX)/Variables.mk

#TODO : fournir un mécanisme pour choisir selon ARCH l'archictecture à compiler
TARGET=ia32

export PREFIX

all: $(TARGET)

ia32:
	make -C ia32/
	
.PHONY: clean
clean:
	make -C $(TARGET)/ clean