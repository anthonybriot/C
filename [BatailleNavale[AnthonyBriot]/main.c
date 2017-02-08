#include <stdio.h>
#include <stdlib.h>
#define TAILLE_BATEAU 3
#define TAILLE_FLOTTE 5
//BUT : Produire un code en C de la bataille navale
//ENTREE : On entre des points
//SORTIE : Le programme nous dit si on touche les points ou non

//TYPE STRUCT
typedef struct Cellule  //structure cellule ou case  avec : x (ligne) et y (colonne)
{
    int x;
    int y;

}Cellule;



typedef struct Bateau   //structure bateau qui contient un tableau à une dimension de cellule, d'une taille définit plus haut, ici les bateaux font 3 cellules
{
    Cellule cel[TAILLE_BATEAU];

}Bateau;



typedef struct Flotte   //structure d'une flotte qui contient un tableau à une dimension de bateau, de taille TAILLE_FLOTTE, ici il y a 5 bateaux dans 1 flotte
{
    Bateau bat[TAILLE_FLOTTE];

}Flotte;




//ENUM à utiliser pour fonction de vérification

enum BOOL{
    True,False, //True=0, False=1,
};



//PROTO & MUTATEURS
Cellule createCellule(int x, int y);
Bateau createBateau(Cellule cel1,Cellule cel2,Cellule cel3);
void createFlotte(Flotte *flotte);
enum BOOL verifCellule(Cellule cel1, Cellule cel2);



//MAIN
int main()
{
    Flotte flotte[2]; // pour 0 1 donc 2 joueurs

    createFlotte(flotte);   //On remplit les flottes avec les emplacements des bateaux

    //Le main n'est pas complété car je n'ai pas réussi à terminer les fonctions de vérification, je ne trouve pas comment utiliser les pointeurs dans la fonction verifbateau


    return 0;
}




//FONCTIONS ET PROCEDURES


//BUT : Créer une cellule
//ENTREE : 2 entiers
//SORTIE : 1 cellule
Cellule createCellule(int x, int y)
{
    Cellule cel;
    cel.x=x;
    cel.y=y;

    return cel;
}


//BUT : Créer un bateau
//ENTREE : 3 cellules composant un bateau
//SORTIE : 1 bateau completé avec 3 cellules
Bateau createBateau(Cellule cel1,Cellule cel2,Cellule cel3)
{

    Bateau bat;

    bat.cel[0] = cel1;
    bat.cel[1] = cel2;
    bat.cel[2] = cel3;


    return bat;
}


//BUT : Créer une flotte
//ENTREE : 3 cellules de chaque bateau pour chaque flotte
//SORTIE : 2 flottes complétées de bateaux complétés de celulles
void createFlotte(Flotte *flotte)
{

    flotte[0].bat[0] = createBateau(createCellule(1,1),createCellule(1,2),createCellule(1,3));
    flotte[0].bat[1] = createBateau(createCellule(4,6),createCellule(4,7),createCellule(4,8));
    flotte[0].bat[2] = createBateau(createCellule(7,3),createCellule(8,3),createCellule(9,3));
    flotte[0].bat[3] = createBateau(createCellule(3,1),createCellule(3,2),createCellule(3,3));
    flotte[0].bat[4] = createBateau(createCellule(7,9),createCellule(8,9),createCellule(9,9));

    flotte[1].bat[0] = createBateau(createCellule(5,1),createCellule(6,1),createCellule(7,1));
    flotte[1].bat[1] = createBateau(createCellule(3,3),createCellule(4,3),createCellule(5,3));
    flotte[1].bat[2] = createBateau(createCellule(8,3),createCellule(8,4),createCellule(8,5));
    flotte[1].bat[3] = createBateau(createCellule(1,6),createCellule(1,7),createCellule(1,8));
    flotte[1].bat[4] = createBateau(createCellule(6,8),createCellule(7,8),createCellule(8,8));


}

//BUT : Verification si une cellule se trouve déjà sur un x et un y
//ENTREE : 2 cellules
//SORTIE : True si les 2 cellules se supersposent, False si les 2 cellules ne se superposent pas
enum BOOL verifCellule(Cellule cel1, Cellule cel2)
{
    if(cel1.x==cel2.x && cel1.y==cel2.y)
    {
        return True;

    }else
    {
        return False;
    }

}

//BUT : Verification qu'une cellule appartient à un bateau
//ENTREE : 1 cellule et 1 bateau
//SORTIE : True si une cellule appartient au bateau, False si elle n'appartient pas au bateau
enum BOOL verifBateau(Cellule celtest, Bateau *bat)
{


    if (verifCellule == False)
    {
        if ((celtest == bat.cel[0]) || (celtest == bat.cel[1]) || (celtest == bat.cel[2]))
        {
            return True;

        }else
        {
            return False;
        }
    }
}

