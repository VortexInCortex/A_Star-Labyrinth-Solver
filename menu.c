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
    const char base_file_path[] = "../";
    char file_name_buffer[33] = {0};
    const char file_type[] = ".txt";
    char file_path[40] = {0}; // l'adresse du fichier est stockable en 40 chars

    system("cls"); // Retire l'affichage du menu precedent, choix esthetique.
    printf("Veuillez saisir un nom de fichier labyrinthe que vous voulez charger : ");

    bool valide = false;
    do {
        // Regex permettant de comprendre le nom du fichier meme si l'utilisateur ajoute  .txt a la fin
        // + ne prend que 33 chars (la taille du buffe), le \x0 semble etre ajouteapres le tableau, car
        // nos test montre que meme un fichier de 33 chars arrive a loader sans specifier la taille
        // de file_name_buffer avec un snprintf plutot que sprintf
        valide = scanf(" %33[a-zA-Z0-9_-]s", &file_name_buffer);
        // valide est = 0 si le scanf ne stocke rien

        if (valide == false) {
            printf("\nVeuillez saisir un choix valide : ");

            // Ce fflush sert a eviter le cas ou le printf rentre dans stdin du prochain scanf et resulte
            // en une boucle infinie. Ce qui arrive dans le menu_saisir_case du .exe du corrige sur moodle ;)
            fflush(stdin);
        }
    } while (valide == false);

    // Concatene l'adresse du fichier pour eviter que l'utilisateur ait besoin de faire le travail
    // d'ecrire ../ et .txt
    sprintf(file_path, "%s%s%s", base_file_path, file_name_buffer, file_type);

    labyrinthe_lire_fichier(file_path, lab);
}

void menu_saisir_case(const Labyrinthe lab, Noeud caze) {
    int caze_ligne = 0;
    int caze_colonne = 0;

    noeud_set_ligne(caze, caze_ligne);
    noeud_set_colonne(caze, caze_colonne);

    int lab_ligne_max = labyrinthe_get_nb_lignes(lab);
    int lab_colonne_max = labyrinthe_get_nb_colonnes(lab);

    system("cls"); // Retire l'affichage du menu precedent, choix esthetique
    printf("Saisissez la ligne et la colonne : ");

    bool valide = false;
    do {
        // valide est = 0 si le scanf ne stocke rien
        valide = scanf("%d, %d", &caze_ligne, &caze_colonne);

        // L'adresse de la caze doit etre dans le labyrinthe et doit etre compose de chiffres
        if (valide == true && !labyrinthe_est_case_valide(lab, caze)) {
            noeud_set_ligne(caze, caze_ligne);
            noeud_set_colonne(caze, caze_colonne);
        } else {
            valide = false;

            printf("\nVeuillez saisir une case se trouvant dans les bornes du labyrinthe : ");

            // Ce fflush sert a eviter le cas ou le printf rentre dans stdin du prochain scanf et resulte
            // en une boucle infinie. Ce qui arrive dans le menu_saisir_case du .exe du corrige sur moodle ;)
            fflush(stdin);
        }
    } while (valide == false);
}

bool choix_est_correct(int choix, const Status status) {
    bool est_correct = false;

    switch (choix) {
        case MENU_CHOIX_CHARGER:
            est_correct = true; // Reproduit le fonctionnement de laby.exe
            break;
        case MENU_CHOIX_AFFICHER: // NOLINT(*-branch-clone) Retire message d'erreur Clang-Tidy
            if (status[MENU_STATUS_INDICE_CHARGER] == true)
                est_correct = true;
            break;
        case MENU_CHOIX_SPECIFIER_DEPART:
            if (status[MENU_STATUS_INDICE_CHARGER] == true)
                est_correct = true;
            break;
        case MENU_CHOIX_SPECIFIER_ARRIVEE:
            // Reproduit le fonctionnement de laby.exe
            if ((status[MENU_STATUS_INDICE_DEPART] == true) && (status[MENU_STATUS_INDICE_CHARGER] == true))
                est_correct = true;
            break;
        case MENU_CHOIX_CHERCHER:
            if ((status[MENU_STATUS_INDICE_CHARGER] == true) && (status[MENU_STATUS_INDICE_DEPART] == true)
                && (status[MENU_STATUS_INDICE_ARRIVEE] == true))
                est_correct = true;
            break;
        case MENU_CHOIX_QUITTER:
            est_correct = true;
            break;
        default:
            printf("\n\nErreur dans la lecture du choix du Menu."
                "\nAssurez-vous de choisir un nombre entre 1 et 6.\n");
            break;
    }

    return est_correct;
}

void menu_traiter_choix(const int choix, Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe,
                        Liste chemin) {
    switch (choix) {
        case MENU_CHOIX_CHARGER:
            menu_lire_fichier(labyrinthe);
            status[MENU_STATUS_INDICE_CHARGER] = true;
            break;
        case MENU_CHOIX_AFFICHER:
            system("cls"); // Retire l'affichage du menu precedent, choix esthetique.
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
            if (labyrinthe_A_star(labyrinthe, depart, arrivee, chemin) == true)
                liste_afficher(chemin);

            system("pause");
            break;
        case MENU_CHOIX_QUITTER:
            // programme_status_execution = STOP; va etre fait avant cette fonction, puisque nous
            // n'avons pas le droit d'ajouter d'arguments aux fonctions dans ce TP (?)
            break;
        default:
            printf("\n\nErreur dans la lecture du choix du Menu, comment etes-vous ici? "
                "Un photon a frappe votre memoire a l'adresse de choix et a bit-flip avant d'enter ici?"
                "Vous devriez appeler les nouvelles, vous etes une des rares personne a qui c'est arrive.\n");
            break;
    }
}

//  Definitions des fonctions publiques (2)
//  ---------------------------------------

bool menu(Status status, Noeud depart, Noeud arrivee, Labyrinthe labyrinthe, Liste chemin) {
#define RUN 1
#define STOP 0

    bool programme_status_execution = RUN;

    system("cls"); // Retire l'affichage du menu precedent, choix esthetique.
    printf("\tMENU\n");
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

    int choix;
    bool valide = false;
    do {
        // Ce fflush sert a eviter le cas ou le printf de "default:" dans choix_est_correct
        // rentre dans stdin du prochain scanf et resulte en une boucle infinie comme laby.exe ;)
        fflush(stdin);
        // valide = scanf("%d",&choix) ici met l'utilisateur dans une boucle jusqu'a ce qu'il
        // entre un entier, mais nous voulons lui indiquer quoi ecrire s'il se trompe avec une lettre
        // par exemple
        choix = getchar();
        choix -= 48;
        // valide est = true si le choix est entre 1 et 6
        if (choix_est_correct(choix, status)) {
            valide = true;
        } else {
            // Ce fflush sert a eviter le cas ou le printf de "default:" dans choix_est_correct
            // rentre dans stdin du prochain scanf et resulte en une boucle infinie comme laby.exe ;)
            fflush(stdin);
        }
    } while (valide == false);

    // Puisque nous ne pouvons pas donner la variable programme_status_exectuion a menu_traiter_choix
    // dans ce TP (?) sinon nous utiliserions a 100% menu_traiter_choix
    if (choix == MENU_CHOIX_QUITTER)
        programme_status_execution = STOP;
    else
        menu_traiter_choix(choix, status, depart, arrivee, labyrinthe, chemin);

    return programme_status_execution;
}
