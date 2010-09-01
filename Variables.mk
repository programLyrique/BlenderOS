#Transmet des variables communes aux différents Makefile, qui l'inclut
#comme l'architecture cible

#Précise l'architecture, par défaut, IA32
ARCH:=IA32

#Les fichiers objets doivent être stockés dans bin
#Ajouter cette destination directement dans CC ?
#  Faire ainsi CC=gcc -D $(ARCH) -Wall -fno-hosted -m32 -mtune=i586 -c $^-o $(PREFIX)/bin/$@
# Garder alors = et pas  := !!
#Définition du compilateur
CC:=gcc -D $(ARCH) -W -Wall -Wextra -O -fno-hosted -m32 -mtune=i586
# et du linker 
LD:=ld -melf_i386 --oformat binary 

#REMARQUE : on devrait tester la valeur de ARCH et sélectionner en conséquence 
# la ligne de compilation ainsi que le linker
