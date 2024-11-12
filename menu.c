//
// Created by duval on 2024-09-14.
//
#include "menu.h"
#include "labyrinthe.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//  Les constantes privees pour un menu
//  -----------------------------------

//  Les constantes relatives aux options proposees par le menu
#define MENU_CHOIX_CHARGER              1
#define MENU_CHOIX_AFFICHER             2
#define MENU_CHOIX_SPECIFIER_DEPART     3
#define MENU_CHOIX_SPECIFIER_ARRIVEE    4
#define MENU_CHOIX_CHERCHER             5
#define MENU_CHOIX_QUITTER              6

//  Les constantes pour le status du menu
#define MENU_STATUS_INDICE_CHARGER             0
#define MENU_STATUS_INDICE_DEPART              1
#define MENU_STATUS_INDICE_ARRIVEE             2

//  Declarations des fonctions privees (4)
//  --------------------------------------

/*
Fonction: menu_lire_fichier
Description: Demande un nom de fichier de labyrinthe a l'utilisateur et charge le labyrinthe.
Paramètres:
    - lab : le lab a charger a partir du fichier.
Retour: Aucun.
Paramètres modifiés: Le labyrinthe qui a ete lu a partir du fichier.
*/
void menu_lire_fichier(Labyrinthe lab);

/*
Fonction: menu_saisir_case
Description: Demande la ligne et la colonne d'une case.
Paramètres:
    - lab : le lab dont on veut specifier une case.
    - ligne : l'adresse a laquelle on va placer la ligne lue.
    - colonne : l'adresse a laquelle on va placer la colonne lue.
Retour: Aucun.
Paramètres modifiés: Les zones pointees par les parametres ligne et colonne.
*/
void menu_saisir_case(const Labyrinthe lab, Noeud caze);

/*
Fonction: choix_est_correct
Description: Indique si un choix d'une option du menu est correcte selon le status du menu.
Paramètres:
    - choix : Un choix qui a ete saisi par l'utilisateur.
    - status : L'etat du menu (labyrinthe charge ou pas, case de depart lue ou pas, case d'arrivee lue ou pas).
Retour: true si le choix est correct par rapport au status, false sinon.
Paramètres modifiés: Aucun.
*/
bool choix_est_correct(int choix, const Status status);

/*
Fonction: menu_traiter_choix
Description: Genere les actions en fonction d'un choix au menu.
Paramètres:
    - choix : Le choix effectue dans le menu par l'utilisateur.
    - status : La status actuel du menu.
    - depart : Un noeud de depart pour la recherche d'un chemin.
    - arrivee : Un noeud d'arrivee pour la recherche d'une chemin.
    - labyrinthe : Le labyrinthe dans lequel chercher le chemin.
    - chemin : Le chemin qui sera trouve lors d'une recherche.
Retour: Aucun.
Paramètres modifiés: Les parametres sont mis a jour selon le choix du menu.
*/
void menu_traiter_choix(int choix, Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin);

//  Definitions des fonctions privees (4)
//  -------------------------------------

void menu_lire_fichier(Labyrinthe lab) {
    char base_file_path[] = "..\\"; // On prend que jusqu'a 40 chars pour la location du fichier labyrinthe
    char file_name_buffer[33] = {0};
    char file_type[] = ".txt";
    char file_path[40] = {0};

    scanf("%33[a-zA-Z0-9_-]s", &file_name_buffer);

    sprintf(file_path, "%s%s%s\x0", base_file_path, file_name_buffer, file_type);
    labyrinthe_lire_fichier(file_path, lab);
}

void menu_saisir_case(const Labyrinthe lab, Noeud caze) {
}

bool choix_est_correct(int choix, const Status status) {
    bool est_correct = false;

    switch (choix) {
        case MENU_CHOIX_CHARGER:
            if (status[MENU_STATUS_INDICE_CHARGER] == false)
                est_correct = true;
            break;
        case MENU_CHOIX_AFFICHER:
            if (status[MENU_STATUS_INDICE_CHARGER] == true)
                est_correct = true;
            break;
        case MENU_CHOIX_SPECIFIER_DEPART:
            if (status[MENU_STATUS_INDICE_DEPART] == false)
                est_correct = true;
            break;
        case MENU_CHOIX_SPECIFIER_ARRIVEE:
            if (status[MENU_CHOIX_SPECIFIER_ARRIVEE] == false)
                est_correct = true;
            break;
        case MENU_CHOIX_CHERCHER:
            if ((status[MENU_STATUS_INDICE_CHARGER] == true) && (status[MENU_STATUS_INDICE_DEPART] == true) && (status[MENU_STATUS_INDICE_ARRIVEE] == true))
                est_correct = true;
            break;
        default:
            printf("Erreur dans la lecture du choix du Menu.\nAssurez-vous de choisir un nombre entre 1 et 6.");
            break;
    }

    return est_correct;
}

void menu_traiter_choix(int choix, Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin) {
}

//  Definitions des fonctions publiques (1)
//  ---------------------------------------

bool menu(Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin) {
    printf(
        "MENU\n"
        "%i. Charger le labyrinthe\n"
        "%i. Afficher le labyrinthe\n"
        "%i. Specifier la case de depart\n"
        "%i. Specifier la case d’arrivee\n"
        "%i. Chercher un chemin\n"
        "%i. Quitter\n"
        "Votre choix ? ",
        MENU_CHOIX_CHARGER,MENU_CHOIX_AFFICHER,MENU_CHOIX_SPECIFIER_DEPART,MENU_CHOIX_SPECIFIER_ARRIVEE,MENU_CHOIX_CHERCHER, MENU_CHOIX_QUITTER);

    int choix = -1;
    scanf("%i", &choix);

    return true;
}

