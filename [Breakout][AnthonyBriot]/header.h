#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>


#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 780

typedef struct game{


     SDL_Window *g_pWindow;
     SDL_Renderer *g_pRenderer;
     SDL_Texture *g_texture;
     SDL_Surface *g_surface;


}game;

typedef struct gameState{

    int g_bRunning;
    int left;
    int right;


}gameState;


typedef struct coordonnees{

    double x;
    double y;



}coordonnees;

typedef struct raquette{

    coordonnees position;   //position x/y
    double vitesse;         //vitesse
    double hauteur;         //dimension paddle
    double largeur;

}raquette;

typedef struct balle{

    coordonnees position;
    double vitesse;     //vitesse de la balle
    double hauteur;     //dimension img
    double largeur;
    int haut_bas;       //savoir si la balle touche le haut/bas de l'écran
    int gauche_droite;  //savoir si la balle touche gauche/droite de l'écran

}balle;

typedef struct brique{

    coordonnees position;   //position x/y
    double hauteur;         //dimension img
    double largeur;
    int destroy;            //savoir si une brique doit être détruite, on l'utilise comme bool avec 0 ou 1

}brique;

enum collision{

    haut,bas,gauche,droite  //facilite déplacement paddle gauche/droite
};

//PROTOTYPES
int init(char *title, int xpos,int ypos,int height, int width,int flags,game *myGame);
void cutBitmapTexture(game *myGame,gameState state);
void delay(unsigned int frameLimit);
void destroyTexture(game *myGame);
void destroy(game *myGame);
void AfficheRaq(game *myGame,gameState state, raquette *joueur);
void DeplacementRaq(int touches[2],raquette *joueur);
void handleEvents(gameState *state, int touches[2]);
void InitRaq(raquette *joueur);
int CollisionRaq(raquette *joueur);
void AfficheMur(game *myGame,gameState state);
void InitBalle(balle *Balle);
void AfficheBalle(game *myGame,gameState state,balle *Balle);
void CollisionBalle(balle *Balle, raquette *joueur);
void DeplacementBalle(balle *Balle);
void InitBriques(brique Briques[15][15]);
void CollisionBriques(brique Briques[15][15], balle *Balle);
void AfficheBriques(game *myGame,gameState state, brique Briques[15][15]);

