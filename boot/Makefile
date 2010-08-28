include $(PREFIX)/Variables.mk

TARGET:=multiboot bootsector

export PREFIX

all: $(TARGET)

multiboot:
	make -C multiboot/

.PHONY:bootsector
bootsector : 
	make -C bootsector/
	@echo "Le bootsecteur n'est pas et ne sera pas probablement disponible."
	
.PHONY: clean
clean:
	make -C multiboot/ clean
	make -C bootsector/ clean