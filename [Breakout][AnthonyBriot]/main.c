#include "header.h"

//MAIN
int main(int argc, char *argv[])
{

     game myGame;
     gameState state;
     int touches[2];    //utiliser dans le déplacement de la raquette
     raquette joueur;
     balle Balle;
     brique Briques[16][15];    //tableau pour afficher les briques

    //Pour les 60 fps
    unsigned int frameLimit = SDL_GetTicks() + 16;


    if(init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame)){

                state.g_bRunning=1;


    }else{

            return 1;//something's wrong

    }


   state.right=1;
   state.left=0;

    //initialisation des valeurs du paddle/balle/briques
    InitRaq(&joueur);
    InitBalle(&Balle);
    InitBriques(Briques);
    while(state.g_bRunning){     //(state.g_bRunning && Balle.position.y<=SCREEN_HEIGHT){// Si l'on veut faire perdre le joueur lorsque la balle sort de l'écran

           handleEvents(&state, touches);
           DeplacementRaq(touches,&joueur);
           AfficheRaq(&myGame,state,&joueur);
           AfficheMur(&myGame,state);
           CollisionBalle(&Balle,&joueur);
           DeplacementBalle(&Balle);
           AfficheBalle(&myGame,state,&Balle);
           CollisionBriques(Briques,&Balle);
           AfficheBriques(&myGame,state,Briques);


           SDL_RenderPresent(myGame.g_pRenderer); // Affichage
           SDL_RenderClear(myGame.g_pRenderer);


        // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;


    }

        destroy(&myGame);

        SDL_Quit();




  return 0;
}


/*  Ce que je n'ai pas pu finir :

- L'implémentation du score qui doit se faire lors de chaque collision de la balle avec une brique
- Une génération aléatoire des niveaux
- Un écran de fin

    Problème non résolu :

- L'utilisation du rand() pour changer la couleur des briques et la génération de niveaux aléatoires (j'ai quelques difficultés à utiliser le rand() )



Je n'ai malheurement pas eu le temps de retoucher à mon code depuis la séance de vendredi, je sais que ce n'est pas une excuse mais je tenais à le préciser.
*/

