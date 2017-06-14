#include "header.h"

//initialisation des briques une par une
void InitBriques(brique Briques[15][15]){

    int i;
    int j;

    for (i=0;i<15;i++){
        for (j=0;j<15;j++){

            Briques[i][j].hauteur=24;
            Briques[i][j].largeur=64;
            Briques[i][j].position.x=32+i*Briques[i][j].largeur; //16 pour le side
            Briques[i][j].position.y=j*Briques[i][j].hauteur;
            Briques[i][j].destroy=0;

        }
    }


}

//affichage des briques, si une brique est détruite elle ne s'affiche plus
void AfficheBriques(game *myGame,gameState state, brique Briques[15][15]){


        int i;
        int j;
        int couleur;

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;


        myGame->g_surface = IMG_Load("./assets/bricks.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface); // Préparation du sprite
                 SDL_FreeSurface(myGame->g_surface); // Libération de la ressource occupée par le sprite

                if(myGame->g_texture){



                    for (i=0;i<15;i++){
                        for (j=0;j<15;j++){
                            if (Briques[i][j].destroy==0){  //si une brique est détruite elle ne s'affiche plus

                            couleur=rand()%4;

                            //petit soucis pour les epileptiques
                            //gestion des couleurs des briques grâce au rand
                            if (couleur==0){
                            //gestion des animations
                            rectangleSource.x=64; //x=0 y=0 => rouge    x=64 y=0 =>jaune     x=0 y=24 => vert   x=64 y=24 =>bleu
                            rectangleSource.y=0;
                            rectangleSource.w=Briques[i][j].largeur;
                            rectangleSource.h=Briques[i][j].hauteur;
                            } else if (couleur==1){
                            rectangleSource.x=0;
                            rectangleSource.y=0;
                            rectangleSource.w=Briques[i][j].largeur;
                            rectangleSource.h=Briques[i][j].hauteur;
                            } else if (couleur==2){
                            rectangleSource.x=0;
                            rectangleSource.y=24;
                            rectangleSource.w=Briques[i][j].largeur;
                            rectangleSource.h=Briques[i][j].hauteur;
                            } else if (couleur==3){
                            rectangleSource.x=64;
                            rectangleSource.y=24;
                            rectangleSource.w=Briques[i][j].largeur;
                            rectangleSource.h=Briques[i][j].hauteur;
                            }



                            //Définition du rectangle dest pour dessiner Bitmap
                            rectangleDest.x=Briques[i][j].position.x;//debut x
                            rectangleDest.y=Briques[i][j].position.y;//debut y
                            rectangleDest.w=rectangleSource.w; //Largeur
                            rectangleDest.h=rectangleSource.h; //Hauteur

                            SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);

                            }
                        }
                    }

                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}

//gestion des collisions briques/balle
void CollisionBriques(brique Briques[15][15], balle *Balle){

    int i;
    int j;

    for (i=0;i<15;i++){
        for (j=0;j<15;j++){
            //si la balle touche un des cotés d'une brique
            if ((Balle->position.x+Balle->largeur>=Briques[i][j].position.x)&&(Balle->position.x<=Briques[i][j].position.x+Briques[i][j].largeur)&&
            (Balle->position.y+Balle->hauteur>=Briques[i][j].position.y)&&(Balle->position.y<=Briques[i][j].position.y+Briques[i][j].hauteur) && Briques[i][j].destroy==0){

                    if (Balle->position.x + Balle->largeur >= Briques[i][j].position.x && Balle->position.x + Balle->largeur <= Briques[i][j].position.x+5){

                        Balle->gauche_droite=0;

                    } else if (Balle->position.x <= Briques[i][j].position.x+Briques[i][j].largeur && Balle->position.x >= Briques[i][j].position.x+Briques[i][j].largeur-5){

                        Balle->gauche_droite=1;

                    } else if (Balle->position.y+Balle->hauteur >= Briques[i][j].position.y && Balle->position.y <= Briques[i][j].position.y+5){

                        Balle->haut_bas=0;

                    } else if (Balle->position.y <= Briques[i][j].position.y+Briques[i][j].hauteur && Balle->position.y >= Briques[i][j].position.y+Briques[i][j].hauteur-5){

                        Balle->haut_bas=1;
                    }

                Briques[i][j].destroy=1; //la balle la détruit

            }

        }
    }

}


