#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <math.h>
#define rayon 20
#define SPEED 2


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_ptexture;
     SDL_Surface *g_psurface;


}game;

typedef struct gameState{

    int g_bRunning;


}gameState;

typedef struct coordonnees{

    double x;
    double y;

}coordonnees;

//PROTOTYPAGE


int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame);
void destroy(game *myGame);
void handleEvents(gameState *state,coordonnees *dep,coordonnees *dep2,coordonnees *z,coordonnees *s, int *raq1, int *raq2, coordonnees *balle, coordonnees *MouvementBallon);
void delay(unsigned int frameLimit);
void BallMouv (game *myGame, coordonnees *dep,coordonnees *dep2, coordonnees *balle);
void DessinRect(game *myGame);
void drawInSurface(game *myGame);
void renderTexture(game *myGame,coordonnees *dep,coordonnees *dep2, coordonnees *z);
void Mouvement(int raq1,int raq2,coordonnees *dep,coordonnees *dep2,coordonnees *z,coordonnees *s);


//MAIN


int main(int argc, char *argv[])
{


     game myGame;
     gameState state;

     unsigned int frameLimit = SDL_GetTicks() + 16;
     coordonnees dep;
     coordonnees dep2;
     coordonnees z;
     coordonnees s;
     coordonnees balle;
     coordonnees MouvementBallon;
     MouvementBallon.x=1;
     MouvementBallon.y=1;

     int raq1,raq2;

     int choix=0;

   balle.y=400;
   balle.x=200;

     state.g_bRunning=1;




        //Create texture for drawing in texture or load picture
        myGame.g_ptexture=SDL_CreateTexture(myGame.g_pRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,SCREEN_WIDTH,SCREEN_HEIGHT);


        while(state.g_bRunning){



                if(choix==0){
                    printf("5 PONG\n");

                    scanf("%i",&choix);


                }
                switch (choix){


                        case 5:init("Chapter 1 setting up SDL",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&myGame);
                                while(state.g_bRunning){

                                    handleEvents(&state,&dep,&dep2,&s,&z,&raq1,&raq2,&balle,&MouvementBallon);
                                    Mouvement(raq1,raq2,&dep,&dep2,&z,&s);
                                    renderTexture(&myGame,&dep,&dep2,&z);
                                    DessinRect(&myGame);
                                    BallMouv (&myGame,&dep,&dep2,&balle);
                                }

                                 break;
                        default:break;


                }

                 system ("cls");


             // Gestion des 60 fps (1000ms/60 = 16.6 -> 16
            delay(frameLimit);
            frameLimit = SDL_GetTicks() + 16;



        }

        destroy(&myGame);

        SDL_Quit();


    return 0;
}


int init(char *title, int xpos,int ypos,int width, int height,int flags,game *myGame){


    myGame->g_pWindow=NULL;
    myGame->g_pRenderer=NULL;
    myGame->g_psurface=NULL;
    myGame->g_ptexture=NULL;


    //initialize SDL

    if(SDL_Init(SDL_INIT_EVERYTHING)>=0){
            //if succeeded create our window
            myGame->g_pWindow=SDL_CreateWindow(title,xpos,ypos,width,height,flags);
            //if succeeded create window, create our render
            if(myGame->g_pWindow!=NULL){
                myGame->g_pRenderer=SDL_CreateRenderer(myGame->g_pWindow,-1,SDL_RENDERER_PRESENTVSYNC);
            }
    }else{
        return 0;

    }
        return 1;

}


void Mouvement(int raq1, int raq2, coordonnees *dep, coordonnees *dep2, coordonnees *z, coordonnees *s){

    if (raq1==1 && dep->y>0){
        dep->y-=SPEED;
    }else if (raq1==2 && dep->y<SCREEN_HEIGHT-100){
        dep->y+=SPEED;
    }

    if (raq2==1 && z->y>0){
        z->y-=SPEED;
    }else if (raq2==2 && z->y<SCREEN_HEIGHT-100){
        z->y+=SPEED;
    }

}

//PERMET D'AVOIR LA LIGNE BLANCHE AU MILIEU DU TERRAIN
void DessinRect(game *myGame){

           //Définition du rectangle a dessiner
        SDL_Rect rectangle;


        SDL_SetRenderDrawColor(myGame->g_pRenderer, 0,0 , 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(myGame->g_pRenderer);

        SDL_SetRenderDrawColor(myGame->g_pRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

        //Triangle
        SDL_RenderDrawLine(myGame->g_pRenderer, 400, 0, 400, 700);

}


void renderTexture(game *myGame,coordonnees *dep,coordonnees *dep2,coordonnees *z ) {

       //COORDONNES RAQ1
        SDL_Rect rectangle;
        rectangle.x=0;//debut x
        rectangle.y=dep->y;//debut y
        rectangle.w=10; //Largeur
        rectangle.h=100; //Hauteur


        //COORDONNES RAQ2
        SDL_Rect rectangle2;
        rectangle2.x=SCREEN_WIDTH-10;//debut x
        rectangle2.y=z->y;//debut y
        rectangle2.w=10; //Largeur
        rectangle2.h=100; //Hauteur



        //Draw in texture
        SDL_SetRenderDrawColor(myGame->g_pRenderer,255,0,0,255);
        SDL_SetRenderTarget(myGame->g_pRenderer, myGame->g_ptexture);

        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle);
        SDL_RenderFillRect(myGame->g_pRenderer, &rectangle2);

        SDL_SetRenderTarget(myGame->g_pRenderer, NULL);

        SDL_Rect position;
        position.x = 0;
        position.y = 0;
        SDL_QueryTexture(myGame->g_ptexture, NULL, NULL, &position.w, &position.h);
        SDL_RenderCopy(myGame->g_pRenderer,myGame->g_ptexture,NULL,&position);


         SDL_RenderPresent(myGame->g_pRenderer);

         SDL_SetRenderDrawColor(myGame->g_pRenderer,0,0,0,255);
         SDL_DestroyTexture(myGame->g_ptexture);
         SDL_RenderClear(myGame->g_pRenderer);




}


//GESTION DES MOUVEMENTS DE LA BALLE

void BallMouv (game *myGame, coordonnees *dep, coordonnees *dep2, coordonnees *balle){

    int i;
    int j;

    SDL_Point boule;

        for(j=rayon;j!=0;j--){

            for(i=1;i<=360;i++){

                    boule.x=j*cos(i);
                    boule.y=j*sin(i);
                    SDL_SetRenderDrawColor(myGame->g_pRenderer,0,84,114,174);
                    SDL_RenderDrawPoint(myGame->g_pRenderer,boule.x+balle->x,boule.y+balle->y);
                                }
                            }
}



void destroy(game *myGame){

      //Destroy render
     if(myGame->g_pRenderer!=NULL)
        SDL_DestroyRenderer(myGame->g_pRenderer);

      //Destroy texture
     if(myGame->g_ptexture!=NULL)
        SDL_DestroyTexture(myGame->g_ptexture);

    //Destroy surface
     if(myGame->g_psurface!=NULL)
         SDL_FreeSurface(myGame->g_psurface);

    //Destroy window
    if(myGame->g_pWindow!=NULL)
        SDL_DestroyWindow(myGame->g_pWindow);

}



//GESTION DES MOUVEMENTS DES RAQUETTES (RAQ1, RAQ2)
void handleEvents(gameState *state,coordonnees *dep,coordonnees *dep2,coordonnees *z,coordonnees *s, int *raq1, int *raq2,coordonnees *balle, coordonnees *MouvementBallon){

    balle->x-= MouvementBallon->x;
    balle->y-=MouvementBallon->y;

    SDL_Event event;

    if(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
              state->g_bRunning=0;break;
        case SDL_KEYDOWN:
                            if (event.key.keysym.sym == SDLK_UP){
                                *raq1 = 1;
                            }

                            if (event.key.keysym.sym == SDLK_DOWN){
                                *raq1 = 2;
                            }
                            if (event.key.keysym.sym == SDLK_z){
                                *raq2 = 1;
                            }

                            if (event.key.keysym.sym == SDLK_s){
                                *raq2 = 2;
                            };break;

        case SDL_KEYUP:

                            if (event.key.keysym.sym == SDLK_UP){
                                *raq1 = 0;
                            }

                            if (event.key.keysym.sym == SDLK_DOWN){
                                *raq1 = 0;
                            }
                            if (event.key.keysym.sym == SDLK_z){
                                *raq2 = 0;
                            }

                            if (event.key.keysym.sym == SDLK_s){
                                *raq2 = 0;
                            };break;

        default:break;

        }
    }

}

void delay(unsigned int frameLimit)
{
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





