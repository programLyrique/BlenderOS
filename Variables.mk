#Transmet des variables communes aux diff�rents Makefile, qui l'inclut
#comme l'architecture cible

#Pr�cise l'architecture, par d�faut, IA32
ARCH:=IA32

#Les fichiers objets doivent �tre stock�s dans bin
#Ajouter cette destination directement dans CC ?
#  Faire ainsi CC=gcc -D $(ARCH) -Wall -fno-hosted -m32 -mtune=i586 -c $^-o $(PREFIX)/bin/$@
# Garder alors = et pas  := !!
#D�finition du compilateur
CC:=gcc -D $(ARCH) -W -Wall -Wextra -O -fno-hosted -m32 -mtune=i586
# et du linker 
LD:=ld -melf_i386 --oformat binary 

#REMARQUE : on devrait tester la valeur de ARCH et s�lectionner en cons�quence 
# la ligne de compilation ainsi que le linker
