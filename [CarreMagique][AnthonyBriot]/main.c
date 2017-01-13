#include <stdio.h>
#include <stdlib.h>
#define TAILLE 7 //définir la taille du carré

//BUT : Faire un carre magique, c'est-à-dire un carré dans lequel les lignes/colonnes/les 2 diagonales ont la même somme
//ENTREE : On entre une taille en constante pour définir la longueur/largeur du carré
//SORTIE : Le carré magique

//Type structuré d'un point
typedef struct Point
{
    int x;
    int y;

}Point;

//Increment pour remplacer les variables i et j
typedef int increment;


//MUTATEURS
void initTab(int tab[][TAILLE]);
void affichage(int tab[][TAILLE]);
void avancer(int tab[][TAILLE], Point *a, int *n, int *test);



//MAIN
int main()
{
    int carremagique[TAILLE][TAILLE];
    Point premier;
    int n=2;
    int test=0;

    initTab(carremagique); //Initialisation du carré

    premier.x=TAILLE/2-1;
    premier.y=TAILLE/2;
    carremagique[premier.x][premier.y]=1; //On place le 1 au nord du milieu

    while (n<=TAILLE*TAILLE)//Permet de continuer la procédure jusqu'à ce que le carré soit complet
    {
        avancer(carremagique, &premier, &n, &test);

    }

    affichage(carremagique); //Affichage du carré

    return 0;
}




//FONCTIONS ET PROCEDURES
//BUT Initialiser le carré
//ENTREE Tableau reprensentant le carré
//SORTIE Tableau rempli de 0
void initTab(int tab[][TAILLE])
{
    increment i;
    increment j;

    for (i=0;i<TAILLE;i++)
    {
        for (j=0;j<TAILLE;j++)
        {
            tab[i][j]=0;
        }
    }
}


//BUT Afficher le carré magique
//ENTREE Tableau contenant les valeurs du carré magique
//SORTIE Affichage du carré avec les bonnes valeurs
void affichage(int tab[][TAILLE])
{
    increment i;
    increment j;

    for(i=0;i<TAILLE;i++)
    {

        for(j=0;j<TAILLE;j++)
        {
            printf("%d\t",tab[i][j]);
        }
    printf("\n");

    }
}


//BUT Remplissage du carré en suivant les consignes
//ENTREE    tableau representant le carré (pour placer les valeurs à l'intérieur), un point qui place la première valeur (le 1)
//          un entier qui s'incrémente à chaque passage dans le Tantque, un entier qui test les valeurs (comme un booléen)
//SORTIE Tableau compléter avec les bonnes valeurs
void avancer(int tab[][TAILLE], Point *a,int *n, int *test)
{

    a->x--;
    if (*test==0)
    {
       a->y++;
    }else
    {
        a->y--;
        *test=0;
    }



    if (a->x<0)
        {
            a->x=TAILLE-1;
        }


    if (a->x>TAILLE-1)
        {
            a->x=0;
        }


    if (a->y>TAILLE-1)
        {
            a->y=0;
        }


    if (a->y<0)
        {
            a->y=TAILLE-1;
        }


    if (tab[a->x][a->y]==0)
    {
        tab[a->x][a->y]=*n;
        *n=*n+1;

    }else
    {
        *test = 1;
    }
}
