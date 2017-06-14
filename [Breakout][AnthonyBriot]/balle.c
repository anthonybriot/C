#include "header.h"
//Initialisation de Balle
void InitBalle(balle *Balle){

    Balle->position.x=SCREEN_WIDTH/2-24;
    Balle->position.y=SCREEN_HEIGHT/2+200; //+200 pour ne pas faire spawn la balle au milieu des briques
    Balle->vitesse=5;
    Balle->hauteur=24;
    Balle->largeur=24;
    Balle->haut_bas=0;
    Balle->gauche_droite=0;


}

//Affichage de la balle
void AfficheBalle(game *myGame,gameState state,balle *Balle){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/ball.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){

                    //gestion des animations
                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=Balle->largeur;
                    rectangleSource.h=Balle->hauteur;



                    //Définition du rectangle dest pour dessiner Bitmap
                    rectangleDest.x=Balle->position.x;//debut x
                    rectangleDest.y=Balle->position.y;//debut y
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

//Deplacement de la balle en fonction des collisions
void DeplacementBalle(balle *Balle){

    if (Balle->haut_bas==1){    //si haut_bas==1, la balle descends

        Balle->position.y+=Balle->vitesse;

    }
    else if (Balle->haut_bas==0){   //si haut_bas==0, la balle monte

        Balle->position.y-=Balle->vitesse;

    }

    if (Balle->gauche_droite==1){      //si gauche_droite==1, la balle va vers la droite

        Balle->position.x+=Balle->vitesse;
    }
    else if (Balle->gauche_droite==0){  //si gauche_droite==0, la balle va vers la gauche

        Balle->position.x-=Balle->vitesse;
    }

}

//gestion des collisions de la balle avec le paddle et les murs
void CollisionBalle(balle *Balle, raquette *joueur){

    if (Balle->position.x>=SCREEN_WIDTH-40){ //si la balle touche le side à droite 16px(side) + 24px(balle) =40px

        Balle->gauche_droite=0;

    }else if (Balle->position.x<=16){   //si la balle touche le side à gauche, on a pas besoin de faire +24px(balle) car x de balle se trouve
                                        //à gauche de celle ci

        Balle->gauche_droite=1;
    }

    //Collision balle-raquette, on calcul également en fonction de la position en x/y et on ajoute +24/+128 pour la largeur/hauteur du paddle et de la balle
    if ((Balle->position.y+24>=joueur->position.y) && (Balle->position.x>=joueur->position.x) && (Balle->position.x+24<=joueur->position.x+128)){

        Balle->haut_bas=0;

    }else if (Balle->position.y<=0){

        Balle->haut_bas=1;
    }



}
