include $(PREFIX)/Variables.mk
OBJ:=bochs_port.o
export PREFIX

all: $(OBJ)

.PHONY:clean

bochs_port.o: bochs_port.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
clean:
	rm -f $(addprefix $(PREFIX)/bin/, $(OBJ)}
