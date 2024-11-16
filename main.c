#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "liste.h"
#include "labyrinthe.h"

//  Fonction principale
//  -------------------
int main() {
    setbuf(stdout, NULL); //  Ne pas utiliser de tampon pour les affichages dans la console.

    Status status = {false, false, false}; //  Etat actuel des informations lues (aucune)
    Labyrinthe labyrinthe; //  Le labyrinthe dans lequel on va chercher un chemin
    Noeud depart, arrivee; //  Les cases de depart et d'arrivee
    Liste chemin; //  Le chemin trouve
    liste_init(chemin,MAX_LISTE);

    while (menu(status, depart, arrivee, labyrinthe, chemin));


    return EXIT_SUCCESS;
}
