# snake : fichier Makefile 

# CHAPITRE 1 : BUT FINAL

but : snake

# CHAPITRE 2 : VARIABLES

OFILES = main.o \
         serpent.o \
       
CC = gcc

CFLAGS = -Wall -g -lgraph

# CHAPITRE 3 : DEPENDANCES (REGLES IMPLICITES)

main.o : serpent.h jeu.h
   
serpent.o : serpent.h jeu.h 


#CHAPITRE 4 : DEPENDANCES AVEC COMMANDES


snake : $(OFILES)
	$(CC) $(CFLAGS) -o snake $(OFILES)

#CHAPITRE 5 : NETTOYAGE DES FICHIERS GENERES

clean :
	-rm -f $(OFILES) snake

#CHAPITRE 6 : BUTS FACTICES

.PHONY : but clean
