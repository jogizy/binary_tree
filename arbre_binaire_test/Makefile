##########################################################################
# Script de compilation du programme de test de la librairie Arbre Binaire
# Auteur: Olivier Meloche
# Date: 2019-11-27
##########################################################################

UNAME=$(shell uname)

SUFIX=.exe
ifeq ($(UNAME), Linux)
SUFIX=
endif
ifeq ($(UNAME), Solaris)
SUFIX=
endif
ifeq ($(UNAME), Darwin)
SUFIX=
endif

all:debug release

obj/Debug/main.o:main.c ../arbre_binaire/arbre_binaire.h
	mkdir -p obj/Debug
	gcc -Wall -g -I../arbre_binaire -c main.c -o $@

bin/Debug/main$(SUFIX):obj/Debug/main.o ../arbre_binaire/bin/Debug/libarbre_binaire.a
	mkdir -p bin/Debug/
	gcc  -o $@ $^

obj/Release/main.o:main.c ../arbre_binaire/arbre_binaire.h
	mkdir -p obj/Release
	gcc -Wall -O2 -I../arbre_binaire  -c main.c -o $@

bin/Release/main$(SUFIX):obj/Release/main.o ../arbre_binaire/bin/Release/libarbre_binaire.a
	mkdir -p bin/Release/
	gcc -s -o $@ $^

debug: bin/Debug/main$(SUFIX)

release: bin/Release/main$(SUFIX)

clean:
	rm -rf obj
	rm -rf bin

.PHONY: all debug release clean
