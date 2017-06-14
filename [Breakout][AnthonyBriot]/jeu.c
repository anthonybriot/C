#include "header.h"


int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame){


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0)
    {
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,height,width,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_ACCELERATED);


            }


    }else{


        return 0;
    }




    return 1;


}

void handleEvents(gameState *state, int touches[2]){


    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:touches[0]=1; break;     //déplacement raquette
                                case SDLK_RIGHT:touches[1]=1 ; break;   //      "          "
                                case SDLK_UP:    ; break;
                                case SDLK_DOWN:  ; break;
                            }
                            break;

        case SDL_KEYUP:
                        switch (event.key.keysym.sym)
                            {
                                case SDLK_LEFT:touches[0]=0; break;
                                case SDLK_RIGHT:touches[1]=0 ; break;
                                case SDLK_UP:    ; break;
                                case SDLK_DOWN:  ; break;
                            }
                            break;


        default:break;

        }
    }


}

//affichage des 2 sides à gauche et à droite
void AfficheMur(game *myGame,gameState state){

        SDL_Rect rectangleDest;
        SDL_Rect rectangleSource;

        SDL_Rect rectangleDest2;
        SDL_Rect rectangleSource2;


        myGame->g_surface = IMG_Load("./assets/side.png");//Chargement de l'image bitmap

         if(!myGame->g_surface) {
            fprintf(stdout,"IMG_Load: %s\n", SDL_GetError());
            // handle error
        }

        if(myGame->g_surface){

                 myGame->g_texture = SDL_CreateTextureFromSurface(myGame->g_pRenderer,myGame->g_surface);
                 SDL_FreeSurface(myGame->g_surface);

                if(myGame->g_texture){

                    //mur1 taille/emplacement

                    rectangleSource.x=0;
                    rectangleSource.y=0;
                    rectangleSource.w=16;
                    rectangleSource.h=SCREEN_HEIGHT;




                    rectangleDest.x=0;//debut x
                    rectangleDest.y=0;//debut y
                    rectangleDest.w=rectangleSource.w; //Largeur
                    rectangleDest.h=rectangleSource.h; //Hauteur


                    //mur2 taille/emplacement

                    rectangleSource2.x=0;
                    rectangleSource2.y=0;
                    rectangleSource2.w=16;
                    rectangleSource2.h=SCREEN_HEIGHT;




                    rectangleDest2.x=SCREEN_WIDTH-16;//debut x
                    rectangleDest2.y=0;//debut y
                    rectangleDest2.w=rectangleSource2.w; //Largeur
                    rectangleDest2.h=rectangleSource2.h; //Hauteur

                    //mur1 affichage
                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource,&rectangleDest);
                    //mur2 affichage
                    SDL_RenderCopy(myGame->g_pRenderer,myGame->g_texture,&rectangleSource2,&rectangleDest2);


                }

                else{
                        fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
                }



        }else{
            fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
        }

    destroyTexture(myGame);


}


void delay(unsigned int frameLimit){
    // Gestion des 60 fps (images/seconde)
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}




void destroy(game *myGame){


    //Destroy render
    if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);


    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}



void destroyTexture(game *myGame){


    //Destroy texture
    if(myGame->g_texture!=NULL)
            SDL_DestroyTexture(myGame->g_texture);

}
