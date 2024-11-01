#include <stdlib.h>
#include <stdio.h>
#include <graph.h>
#include <time.h>

#define CYCLE 10000L

int seconde = 0;
int minute = 0;
int seconde_actuel = 0;
int old_seconde = 0;
char timer[6];
unsigned long int suivant;
int go_on = 1;
int serpent;
int x = 600;
int y = 400;
int direction = 4;
int t;
int segment = 10;
int i = 0;
int pos_x[60];
int pos_y[60];
int old_x[60];
int old_y[60];
int p = 0;
int pp = 0;
int pomme, pommex[5], pommey[5];
int fond;
int score = 0;
int pixel_noir_x[5];
int pixel_noir_y[5];
int pixel_noir_present[5];
int pause = 0;

// Ajout des tableaux pour sauvegarder les positions des pommes et des pixels noirs
int saved_pommex[5];
int saved_pommey[5];
int saved_pixel_noir_x[5];
int saved_pixel_noir_y[5];
int saved_pixel_noir_present[5];

void SauvegarderPositions() {
    for (int index = 0; index < 5; ++index) {
        saved_pommex[index] = pommex[index];
        saved_pommey[index] = pommey[index];
        saved_pixel_noir_x[index] = pixel_noir_x[index];
        saved_pixel_noir_y[index] = pixel_noir_y[index];
        saved_pixel_noir_present[index] = pixel_noir_present[index];
    }
}

void RestaurerPositions() {
    for (int index = 0; index < 5; ++index) {
        pommex[index] = saved_pommex[index];
        pommey[index] = saved_pommey[index];
        pixel_noir_x[index] = saved_pixel_noir_x[index];
        pixel_noir_y[index] = saved_pixel_noir_y[index];
        pixel_noir_present[index] = saved_pixel_noir_present[index];
    }
}

void SpawnPixelNoir(int index);
void Update_PixelNoir(int index);
void DessinerScene();
void Update_Timer();
void Update_Serpent();
void Terrain();
void Timer();
void Controle();
void Update_Score();
void Serpent();
void Pomme();
void FinPartie();
void Pause();

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

    for (pp = 0; pp < 5; pp++) {
        if (pixel_noir_present[pp] && pos_x[0] == pixel_noir_x[pp] && pos_y[0] == pixel_noir_y[pp]) {
            go_on = 0;
        }
    }

    for (i = 1; i < segment; i++) {
        if (pos_x[0] == pos_x[i] && pos_y[0] == pos_y[i]) {
            go_on = 0;
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
    if (!pause && Microsecondes()
> suivant) {
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
        case XK_space:
            if (!pause) {
                pause = 1;
                Pause();
            }
            break;
        }
    }
}

void Update_Score() {
    score += 5;
}

void Serpent() {
    for (pp = 0; pp < 5; pp++) {
        if (pixel_noir_present[pp] && pos_x[0] == pixel_noir_x[pp] && pos_y[0] == pixel_noir_y[pp]) {
            go_on = 0;
        }
    }

    for (i = 1; i < segment; i++) {
        if (pos_x[0] == pos_x[i] && pos_y[0] == pos_y[i]) {
            go_on = 0;
        }
    }

    if (!pause) {
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

        for (pp = 0; pp < 5; pp++) {
            if (!pixel_noir_present[pp] && rand() % 100 < 5) {
                SpawnPixelNoir(pp);
            }
        }

        for (p = 0; p < 5; p++) {
            if (pommex[p] == pos_x[0] && pommey[p] == pos_y[0]) {
                segment += 2;
                pommex[p] = ((rand() % (58) + 1) * 20);
                pommey[p] = ((rand() % (35) + 1) * 20);
                Update_Score();
            }
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
}

void Pomme() {
    for (pp = 0; pp < 5; ++pp) {
        AfficherSprite(pomme, pommex[pp], pommey[pp]);
    }

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    EcrireTexte(1050, 760, "Score:", 2);
    char score_text[5];
    snprintf(score_text, 5, "%d", score);
    EcrireTexte(1150, 760, score_text, 2);
}

void FinPartie() {
    EffacerEcran(CouleurParComposante(0, 0, 0));

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    EcrireTexte(500, 300, "Game Over !", 2);
    char score_final[20];
    snprintf(score_final, 20, "Score final : %d", score);
    EcrireTexte(500, 350, score_final, 2);

    clock_t delay = 20000000 * CLOCKS_PER_SEC / 9000000;
    clock_t start_time = clock();

    while (clock() < start_time + delay) {
        // Attendre
    }
}

void Pause() {
    int key;
    SauvegarderPositions();

    EffacerEcran(CouleurParComposante(0, 0, 0));
    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    EcrireTexte(500, 300, "Pause", 2);
    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    EcrireTexte(500, 400, "Appuyez sur espace pour reprendre", 2);

    while (1) {
        if (ToucheEnAttente()) {
            key = Touche();
            if (key == XK_space) {
                EffacerEcran(CouleurParComposante(0, 0, 0));
                DessinerScene();
                RestaurerPositions();
                pause = 0;
                return;
            }
        }
    }
}

int main() {
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



