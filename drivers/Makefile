include $(PREFIX)/Variables.mk
TARGET:=text
export PREFIX

all: $(TARGET)

text:
	$(MAKE) -C text

.PHONY: clean
clean:
	make -C text/ clean
