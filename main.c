#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include <menu.h>
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

    // test_menu_lire_fichier(labyrinthe);
    // labyrinthe_afficher(labyrinthe);
    // test_noeud_afficher();
    //system("pause");
    // system("cls");
    // test_labyrinthe_voisins();
    //system("pause");
    //  Appel au menu tant que l'utilisateur ne choisit pas de quitter
    while (menu(status, depart, arrivee, labyrinthe, chemin));


    return EXIT_SUCCESS;
}
