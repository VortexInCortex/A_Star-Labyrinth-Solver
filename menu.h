#ifndef LABYRINTHE_IO_H
#define LABYRINTHE_IO_H

#include "labyrinthe.h"
#include <stdbool.h>

//  Le type pour le status du menu
//  ------------------------------
typedef bool Status[3];

//  Declarations des fonctions publiques (2)
//  ----------------------------------------

/*
Fonction: menu
Description: Affiche le menu, demande un choix a l'utilisateur et traite ce choix.
             Le menu n'affiche que les options disponibles selon les valeurs booleennes passees en parametre.
Paramètres:
    - status : Le status actuel du menu.
    - depart : La case de depart.
    - arrivee : La case d'arrivee.
    - labyrinthe : La labyrinthe dans lequel chercher le chemin.
    - chemin : Le chemin trouve par l'algorithme.
Retour: true si l'utilisateur n'a pas choisi l'option de quitter, false sinon.
Paramètres modifiés: Tous.
*/
bool menu(Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin);

void test_menu_lire_fichier(Labyrinthe labyrinthe);

#endif //LABYRINTHE_IO_H
