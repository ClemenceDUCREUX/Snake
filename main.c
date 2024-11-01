/// main.c
#include "jeu.h"
#include "serpent.h"
#include <stdlib.h>
#include <stdio.h> 


int main() {
    ///variable
int p;
int pp;
int pixel_noir_present[5];
int pos_x[60];
int pos_y[60];
int old_x[60];
int old_y[60];
int pixel_noir_x[5];
int pixel_noir_y[5];
int go_on;
int i;
int direction;
int segment;
int pomme, pommex[5], pommey[5];


    InitialiserGraphique();
    CreerFenetre(350, 100, 1200, 800);
    EffacerEcran(CouleurParComposante(0, 0, 0));
    suivant = Microsecondes() + CYCLE;
    old_seconde = (suivant / 1000000) % 10;
    DessinerScene();

    while (go_on) {
        Timer();
        Controle();
        Serpent();
        Pomme();
    }

    FinPartie();

    FermerGraphique();
    return EXIT_SUCCESS;
}
