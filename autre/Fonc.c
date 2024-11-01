#include<stdlib.h>
#include<graph.h>
#include<stdio.h>
#include"Fonc.h"

#define CYCLE 1000000UL


int CliqueBouton(int x, int y , int w, int z){
	int Clique = 0; 
        while (Clique == 0) {
      	SourisPosition(); 
	if (SourisCliquee()) 
	 { 
		 if (_X>= x && _X<= y + x && _Y>= w && _Y<= z + w){
			 EffacerEcran(CouleurParNom("White"));
		  Clique = 1;}
	 }
	return Clique;
	}
      
}



int Timer(){
    unsigned long start = Microsecondes();
    unsigned long secondes;
    char text[64];
  
     InitialiserGraphique();
     couleur c= CouleurParComposante(255,255,255);
    ChoisirEcran(1);
     while(1) {
       EffacerEcran(c);
       secondes = (Microsecondes() - start) / CYCLE;
       sprintf(text, "%02d:%02d", secondes / 60, secondes % 60);
       EcrireTexte(10,100, text, 2);
       CopierZone(1, 0, 0, 0, 600, 200, 0, 0);
  }
     return 0;
}