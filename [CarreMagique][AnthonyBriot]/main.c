#include <stdio.h>
#include <stdlib.h>
#define TAILLE 7 //d�finir la taille du carr�

//BUT : Faire un carre magique, c'est-�-dire un carr� dans lequel les lignes/colonnes/les 2 diagonales ont la m�me somme
//ENTREE : On entre une taille en constante pour d�finir la longueur/largeur du carr�
//SORTIE : Le carr� magique

//Type structur� d'un point
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

    initTab(carremagique); //Initialisation du carr�

    premier.x=TAILLE/2-1;
    premier.y=TAILLE/2;
    carremagique[premier.x][premier.y]=1; //On place le 1 au nord du milieu

    while (n<=TAILLE*TAILLE)//Permet de continuer la proc�dure jusqu'� ce que le carr� soit complet
    {
        avancer(carremagique, &premier, &n, &test);

    }

    affichage(carremagique); //Affichage du carr�

    return 0;
}




//FONCTIONS ET PROCEDURES
//BUT Initialiser le carr�
//ENTREE Tableau reprensentant le carr�
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


//BUT Afficher le carr� magique
//ENTREE Tableau contenant les valeurs du carr� magique
//SORTIE Affichage du carr� avec les bonnes valeurs
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


//BUT Remplissage du carr� en suivant les consignes
//ENTREE    tableau representant le carr� (pour placer les valeurs � l'int�rieur), un point qui place la premi�re valeur (le 1)
//          un entier qui s'incr�mente � chaque passage dans le Tantque, un entier qui test les valeurs (comme un bool�en)
//SORTIE Tableau compl�ter avec les bonnes valeurs
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
