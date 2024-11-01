/// serpent.c
#include "jeu.h"
#include <time.h>
#include "serpent.h"
#include <stdlib.h>
#include <stdio.h> 

void SpawnPixelNoir(int index) {
    pixel_noir_x[index] = ((rand() % (58) + 1) * 20);
    pixel_noir_y[index] = ((rand() % (35) + 1) * 20);
    pixel_noir_present[index] = 1;
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    RemplirRectangle(pixel_noir_x[index], pixel_noir_y[index], 20, 20);
}

void Update_PixelNoir(int index) {
    pixel_noir_present[index] = 0;
    ChoisirCouleurDessin(CouleurParComposante(91, 222, 122));
    RemplirRectangle(pixel_noir_x[index], pixel_noir_y[index], 20, 20);
}

void DessinerScene() {
    snprintf(timer, 6, "%02d:%02d", minute, seconde);
    ChoisirCouleurDessin(CouleurParComposante(91, 222, 122));
    RemplirRectangle(20, 20, 1160, 700);
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    EcrireTexte(10, 760, timer, 2);
    serpent = ChargerSprite("serpent.png");
    fond = ChargerSprite("fond.png");

    for (i = 0; i < segment; i++) {
        AfficherSprite(serpent, x - (i * 20), y);
        pos_x[i] = x - (i * 20);
        pos_y[i] = y;
        old_x[i] = pos_x[i];
        old_y[i] = pos_y[i];
    }
    srand(time(NULL));
    pomme = ChargerSprite("pomme.png");
    for (p = 0; p < 5; p++) {
        do {
            pommex[p] = ((rand() % (58) + 1) * 20);
            pommey[p] = ((rand() % (35) + 1) * 20);
        } while (pommex[p] <= 400 && pommey[p] <= 640);
        AfficherSprite(pomme, pommex[p], pommey[p]);

        // Appel de la nouvelle fonction pour générer les pixels noirs
        SpawnPixelNoir(p);
    }
}

void Update_Timer() {
    snprintf(timer, 6, "%02d:%02d", minute, seconde);
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    RemplirRectangle(0, 700, 1200, 800);
    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    EcrireTexte(10, 760, timer, 2);
}

void Update_Serpent() {
    AfficherSprite(fond, pos_x[segment - 1], pos_y[segment - 1]);
    AfficherSprite(serpent, pos_x[0], pos_y[0]);

    // Vérification de la collision avec les pixels noirs
    for (pp = 0; pp < 5; pp++) {
        if (pixel_noir_present[pp] && pos_x[0] == pixel_noir_x[pp] && pos_y[0] == pixel_noir_y[pp]) {
            go_on = 0;  // Le serpent meurt en touchant un pixel noir
        }
    }

    // Vérification de la collision avec le corps
    for (i = 1; i < segment; i++) {
        if (pos_x[0] == pos_x[i] && pos_y[0] == pos_y[i]) {
            go_on = 0;  // Le serpent se tue lui-même
        }
    }

    for (i = 1; i < segment; i++) {
        pos_x[i] = old_x[i - 1];
        pos_y[i] = old_y[i - 1];
        AfficherSprite(serpent, pos_x[i], pos_y[i]);
    }
    old_x[0] = pos_x[0];
    old_y[0] = pos_y[0];
    for (i = 1; i < segment; i++) {
        old_x[i] = pos_x[i];
        old_y[i] = pos_y[i];
    }
}

void Terrain() {
    if (pos_x[0] > 1140 || pos_x[0] <= 20)
        go_on = 0;
    if (pos_y[0] < 40 || pos_y[0] >= 680)
        go_on = 0;
}

void Timer() {
    if (Microsecondes() > suivant) {
        suivant = Microsecondes() + CYCLE;
        seconde_actuel = (suivant / 1000000) % 10;
        if (seconde_actuel != old_seconde) {
            old_seconde = seconde_actuel;
            if (seconde == 59) {
                minute = minute + 1;
                seconde = 0;
                Update_Timer();
            } else {
                seconde = seconde + 1;
                Update_Timer();
            }
        }
    }
}

void Controle() {
    while (ToucheEnAttente()) {
        t = Touche();
        switch (t) {
        case XK_Left:
            direction = 3;
            break;
        case XK_Right:
            direction = 4;
            break;
        case XK_Up:
            direction = 1;
            break;
        case XK_Down:
            direction = 2;
            go_on = 2;
            break;
        case XK_Escape:
            direction = 0;
            break;
        case XK_p:
            direction = 0;
            break;
        }
    }
}

void Update_Score() {
    score += 5;
}

void Serpent() {
    // Vérification de la collision avec les pixels noirs
    for (pp = 0; pp < 5; pp++) {
        if (pixel_noir_present[pp] && pos_x[0] == pixel_noir_x[pp] && pos_y[0] == pixel_noir_y[pp]) {
            go_on = 0;  // Le serpent meurt en touchant un pixel noir
        }
    }

    // Vérification de la collision avec le corps
    for (i = 1; i < segment; i++) {
        if (pos_x[0] == pos_x[i] && pos_y[0] == pos_y[i]) {
            go_on = 0;  // Le serpent se tue lui-même
        }
    }

    if (direction == 1) {
        pos_y[0] = old_y[0] - 20;
    }
    if (direction == 2) {
        pos_y[0] = old_y[0] + 20;
    }
    if (direction == 3) {
        pos_x[0] = old_x[0] - 20;
    }
    if (direction == 4) {
        pos_x[0] = old_x[0] + 20;
    }

    // Génération de nouveaux pixels noirs de manière aléatoire
    for (pp = 0; pp < 5; pp++) {
        if (!pixel_noir_present[pp] && rand() % 100 < 5) {
            SpawnPixelNoir(pp);
        }
    }

    for (p = 0; p < 5; p++) {
        // Vérification de la collision avec les pommes
        if (pommex[p] == pos_x[0] && pommey[p] == pos_y[0]) {
            segment += 2;
            pommex[p] = ((rand() % (58) + 1) * 20);
            pommey[p] = ((rand() % (35) + 1) * 20);
            Update_Score();
        }

        // Affichage des pommes
        AfficherSprite(pomme, pommex[p], pommey[p]);
    }

    Update_Serpent();
    Terrain();
    clock_t delay = 100000 * CLOCKS_PER_SEC / 1000000;
    clock_t start_time = clock();

    while (clock() < start_time + delay) {
        // Attendre
    }
}