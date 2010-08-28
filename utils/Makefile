include $(PREFIX)/Variables.mk

OBJ:=string.o

export PREFIX

all: $(OBJ)

string.o: string.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
.PHONY: clean
clean:
	rm -f $(addprefix $(PREFIX)/, $(OBJ)}