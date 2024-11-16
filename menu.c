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
    const char base_file_path[] = "../"; // On prend que jusqu'a 40 chars pour la location du fichier labyrinthe
    char file_name_buffer[33] = {0};
    const char file_type[] = ".txt";
    char file_path[40] = {0};

    do {
        system("cls");
        printf("Veuillez saisir un nom de fichier labyrinthe que vous voulez charger : ");

        fflush(stdin);
        while (scanf(" %32[a-zA-Z0-9_-]s", &file_name_buffer) == false) {
            printf("\nVeuillez saisir un choix valide : ");
            fflush(stdin);
        }
    } while (file_name_buffer[0] == 0);

    sprintf(file_path, "%s%s%s\x0", base_file_path, file_name_buffer, file_type);
    labyrinthe_lire_fichier(file_path, lab);
}

void menu_saisir_case(const Labyrinthe lab, Noeud caze) {
    int caze_ligne = 0;
    int caze_colonne = 0;


    system("cls");
    printf("Saisissez la ligne et la colonne : ");

    int valide = false;
    fflush(stdin);
    while (valide == false || (labyrinthe_est_case_valide(lab, caze) == false)) {
        valide = scanf(" %d, %d", &caze_ligne, &caze_colonne);
        if (valide >= 0) {
            noeud_set_ligne(caze, caze_ligne);
            noeud_set_colonne(caze, caze_colonne);
        }
        printf("\nVeuillez saisir un choix valide : ");
        fflush(stdin);
    }
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
            if (status[MENU_STATUS_INDICE_DEPART] == false && status[MENU_STATUS_INDICE_CHARGER] == true)
                est_correct = true;
            break;
        case MENU_CHOIX_SPECIFIER_ARRIVEE:
            if (status[MENU_STATUS_INDICE_ARRIVEE] == false && status[MENU_STATUS_INDICE_CHARGER] == true)
                est_correct = true;
            break;
        case MENU_CHOIX_CHERCHER:
            if ((status[MENU_STATUS_INDICE_CHARGER] == true) && (status[MENU_STATUS_INDICE_DEPART] == true) && (
                    status[MENU_STATUS_INDICE_ARRIVEE] == true))
                est_correct = true;
            break;
        default:
            system("cls");
            printf("Erreur dans la lecture du choix du Menu, comment etes-vous ici? Un photon a frappe votre memoire a l'adresse de choix et a bit-flip?"
                "Vous devriez appeler les nouvelles, vous etes une des rares personne a qui c'est arrive.\n");
            break;
    }

    return est_correct;
}

void menu_traiter_choix(int choix, Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin) {
    switch (choix) {
        case MENU_CHOIX_CHARGER:
            menu_lire_fichier(labyrinthe);
            status[MENU_STATUS_INDICE_CHARGER] = true;
            break;
        case MENU_CHOIX_AFFICHER:
            system("cls");
            labyrinthe_afficher(labyrinthe);
            system("pause");
            break;
        case MENU_CHOIX_SPECIFIER_DEPART:
            menu_saisir_case(labyrinthe, depart);
            status[MENU_STATUS_INDICE_DEPART] = true;
            break;
        case MENU_CHOIX_SPECIFIER_ARRIVEE:
            menu_saisir_case(labyrinthe, arrivee);
            status[MENU_STATUS_INDICE_ARRIVEE] = true;
            break;
        case MENU_CHOIX_CHERCHER:
            liste_init(chemin,MAX_LISTE);

            if (labyrinthe_A_star(labyrinthe, depart, arrivee, chemin) == true)
                liste_afficher(chemin);
            system("pause");
            break;
        case MENU_CHOIX_QUITTER:
            //programme_status_execution = false;
            break;
        default:
            system("cls");
            printf("Erreur dans la lecture du choix du Menu.\nAssurez-vous de choisir un nombre entre 1 et 6.\n");
            break;
    }
}

//  Definitions des fonctions publiques (2)
//  ---------------------------------------

bool menu(Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin) {
    bool programme_status_execution = true;

    system("cls");
    printf("\tMENU\n");

    if (choix_est_correct(MENU_CHOIX_CHARGER, status))
        printf("%i. Charger le labyrinthe\n",MENU_CHOIX_CHARGER);

    if (choix_est_correct(MENU_CHOIX_AFFICHER, status))
        printf("%i. Afficher le labyrinthe\n",MENU_CHOIX_AFFICHER);

    if (choix_est_correct(MENU_CHOIX_SPECIFIER_DEPART, status))
        printf("%i. Specifier la case de depart\n",MENU_CHOIX_SPECIFIER_DEPART);

    if (choix_est_correct(MENU_CHOIX_SPECIFIER_ARRIVEE, status))
        printf("%i. Specifier la case d'arrivee\n",MENU_CHOIX_SPECIFIER_ARRIVEE);

    if (choix_est_correct(MENU_CHOIX_CHERCHER, status))
        printf("%i. Chercher un chemin\n",MENU_CHOIX_CHERCHER);

    printf("%i. Quitter\nVotre choix ? ", MENU_CHOIX_QUITTER);

    int choix = -1;
    while (scanf("%d", &choix) == false) {
        printf("\nVeuillez saisir un choix valide : ");
        fflush(stdin);
    }
    fflush(stdin);

    menu_traiter_choix(choix, status, depart, arrivee, labyrinthe, chemin);
    if (choix == MENU_CHOIX_QUITTER)
        programme_status_execution = false;

    return programme_status_execution;
}

void test_menu_lire_fichier(Labyrinthe labyrinthe) {
    menu_lire_fichier(labyrinthe);
}
