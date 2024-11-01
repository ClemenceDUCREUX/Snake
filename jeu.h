/// jeu.h

#ifndef JEU_H
#define JEU_H

#include <graph.h>

#define CYCLE 10000L

extern int seconde;
extern int minute;
extern int seconde_actuel;
extern int old_seconde;
extern char timer[6];
extern unsigned long int suivant;

extern int go_on;

extern int serpent;
extern int x;
extern int y;
extern int direction;
extern int t;

extern int segment;
extern int i;
extern int pos_x[60];
extern int pos_y[60];
extern int old_x[60];
extern int old_y[60];

extern int p;
extern int pp;
extern int pomme, pommex[5], pommey[5];
extern int fond;

extern int score;

extern int pixel_noir_x[5];
extern int pixel_noir_y[5];
extern int pixel_noir_present[5];

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

#endif // JEU_H
