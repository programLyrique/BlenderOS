include $(PREFIX)/Variables.mk
TARGET:=text bochs_port
export PREFIX

all: $(TARGET)

.PHONY:text clean bochs_port

text:
	$(MAKE) -C text

bochs_port:
	$(MAKE) -C bochs_port
	
clean:
	make -C text/ clean
