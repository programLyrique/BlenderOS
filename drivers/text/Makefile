include $(PREFIX)/Variables.mk

TARGET:=screen.o
OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))

all: $(TARGET)

screen.o: screen.c
	$(CC) -c $^ -o $(PREFIX)/bin/$@
	
.o: $(wildcard *.c)
	$(CC) -c $^ -o {addprefix $(PREFIX)/bin/, $@}
	
.PHONY: clean
clean:
	cd $(PREFIX)/bin
	rm -f $(OBJ)