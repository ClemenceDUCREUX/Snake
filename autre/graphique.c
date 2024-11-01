#include<stdlib.h>
#include<graph.h>
#include"Fonc.h"
#include"Fonc.c"

#define CYCLE 1000000UL
 
int main (void){
    int x,y;
    InitialiserGraphique();

    CreerFenetre(10,10,1000,600);
    ChargerImageFond("img/serpent.jpg");
    EcrireTexte(500 ,100,"SNAKE ",2);
    ///ChargerImageFond("img/serpent.jpg");
    ChargerImage("img/d.jpg", 300, 250, 160, 0, 350, 350); 
    RemplirRectangle(410, 325, 200, 100);
   
   
    Touche();
    while(ToucheEnAttente() == 0 || Touche() != XK_Escape){
	   
  	        if (CliqueBouton(410, 325, 200, 100) == 1){
                RemplirRectangle(410, 325, 200, 600);

               
                
	        
	
	        			 		      	 		
	    }
    return EXIT_SUCCESS;
    }
}