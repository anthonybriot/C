#include "header.h"

//Initialise la position en x et y du paddle, sa vitesse, ses dimensions(celle de l'img)
void InitRaq(raquette *joueur){

    joueur->position.x=SCREEN_WIDTH/2-64;
    joueur->position.y=SCREEN_HEIGHT-32;

    joueur->vitesse=7;

    joueur->hauteur=32;
    joueur->largeur=128;


}

//Permet l'affichage du paddle
void AfficheRaq(game *myGame,gameState state, raquette *joueur){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/paddle.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    //On donne les dimensions du paddle
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=joueur->largeur;
                    rectangleSource.h=joueur->hauteur;



                    //Destination du paddle
                    rectangleDest.x=joueur->position.x;//debut x
                    rectangleDest.y=joueur->position.y;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur

                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}

//Permet les déplacements
//touches[]=1 quand KEYDOWN
//droite est la limite maximale à droite de l'écran
//gauche est la limite maximale à gauche de l'écran
void DeplacementRaq(int touches[2],raquette *joueur){

    if ((touches[0]==1) && (CollisionRaq(joueur)!=gauche)){

        joueur->position.x-=joueur->vitesse;

    }
    else if ((touches[1]==1) && (CollisionRaq(joueur)!=droite)){
        joueur->position.x+=joueur->vitesse;
    }

}


//Fonction de collision, renvoie droite si le paddle est trop à droite, gauche si trop à gauche
int CollisionRaq(raquette *joueur){

    if (joueur->position.x>=SCREEN_WIDTH-144){

        return droite;

    }else if (joueur->position.x<=16){

        return gauche;
    }

    return 0; //= return haut; qui n'est pas utilisé dans cette fonction, donc il n'y a pas de problème

}
