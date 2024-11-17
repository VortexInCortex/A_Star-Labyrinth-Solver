#include "labyrinthe.h"
#include "couleurs.h"
#include "liste.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//  Constantes privees pour un labyrinthe
//  -------------------------------------
#define LABYRINTHE_INDICE_LIGNE_META    0   /* indice de la ligne contenant les informations de lignes et de colonnes */
#define LABYRINTHE_INDICE_NB_LIGNES     1   /* numero de colonne qui contient le nombre de lignes du labyrinthe */
#define LABYRINTHE_INDICE_NB_COLONNES   2   /* numero de colonne qui contient le nombre de colonnes du labyrinthe */

//  Declaration des fonctions privees (2)
//  -------------------------------------

void labyrinthe_set_nb_lignes(Labyrinthe lab, int nb_lignes);

void labyrinthe_set_nb_colonnes(Labyrinthe lab, int nb_colonnes);

//  Definitions des fonctions privees (2)
//  -------------------------------------

void labyrinthe_set_nb_lignes(Labyrinthe lab, int nb_lignes) {
    lab[LABYRINTHE_INDICE_NB_LIGNES][LABYRINTHE_INDICE_LIGNE_META] = (char) nb_lignes;
}

void labyrinthe_set_nb_colonnes(Labyrinthe lab, int nb_colonnes) {
    lab[LABYRINTHE_INDICE_NB_COLONNES][LABYRINTHE_INDICE_LIGNE_META] = (char) nb_colonnes;
}

//  Definitions des fonctions publiques (12)
//  ----------------------------------------

int labyrinthe_get_nb_lignes(const Labyrinthe lab) {
    return lab[LABYRINTHE_INDICE_NB_LIGNES][LABYRINTHE_INDICE_LIGNE_META];
}

int labyrinthe_get_nb_colonnes(const Labyrinthe lab) {
    return lab[LABYRINTHE_INDICE_NB_COLONNES][LABYRINTHE_INDICE_LIGNE_META];
}

bool labyrinthe_est_case_valide(const Labyrinthe lab, const Noeud caze) {
    bool est_case_valide = false;

    int lab_ligne_max = labyrinthe_get_nb_lignes(lab);
    int lab_colonne_max = labyrinthe_get_nb_colonnes(lab);
    int caze_ligne = noeud_get_ligne(caze);
    int caze_colonne = noeud_get_colonne(caze);

    // la caze doit se trouvée dans le labyrinthe.
    if ((caze_ligne > 0 && caze_ligne <= lab_ligne_max) && (caze_colonne > 0 && caze_colonne <= lab_colonne_max))
        est_case_valide = true;

    return est_case_valide;
}

char labyrinthe_lire_case(const Labyrinthe lab, const Noeud caze) {
    int caze_ligne = noeud_get_ligne(caze);
    int caze_colonne = noeud_get_colonne(caze);

    return lab[caze_ligne][caze_colonne];
}

void labyrinthe_lire_fichier(const char *nom_fichier, Labyrinthe lab) {
    FILE *fichier = fopen(nom_fichier, "r");
    assert(fichier != NULL);

    int l = 1, c = 1;
    char car;

    labyrinthe_set_nb_lignes(lab, VALEUR_INCONNUE);
    labyrinthe_set_nb_colonnes(lab, VALEUR_INCONNUE);

    while (fscanf(fichier, "%c", &car) != EOF) {
        switch (car) {
            case '*':
            case ' ':
                lab[l][c] = car;
                c++;
                break;
            case '\n':
                if (labyrinthe_get_nb_colonnes(lab) == VALEUR_INCONNUE) {
                    labyrinthe_set_nb_colonnes(lab, c - 1);
                } else if (labyrinthe_get_nb_colonnes(lab) != c - 1) {
                    fprintf(stderr, "Le labyrinthe du fichier '%s' n'est pas un rectangle.\n", nom_fichier);
                    exit(-1);
                }
                l++;
                c = 1;
                break;
            case '\r':
                break;
            default:
                fprintf(stderr, "Caractere '%c' non reconnu dans le fichier de lab %s (ligne %d, colonne %d).\n",
                        car, nom_fichier, l, c);
                exit(-1);
        }
    }
    labyrinthe_set_nb_lignes(lab, l);

    fclose(fichier);
}

void labyrinthe_afficher(const Labyrinthe lab) {
    for (int ligne = 1; ligne <= labyrinthe_get_nb_lignes(lab); ligne++) {
        for (int colonne = 1; colonne <= labyrinthe_get_nb_colonnes(lab); colonne++) {
            char tmp = lab[ligne][colonne];
            if (tmp == '*')
                couleurs_set(STYLE_RESET, FG_BRIGHT_WHITE, BG_BRIGHT_WHITE);
            else
                couleurs_reset();

            printf("%c", tmp);
        }
        printf("\n");
    }
    couleurs_reset();
}

void labyrinthe_voisins(const Labyrinthe lab, const Noeud caze, Liste voisins) {
    int caze_ligne = noeud_get_ligne(caze);
    int caze_colonne = noeud_get_colonne(caze);

    const int deplacement[][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};

    for (int i = 0; i < 4; i++) {
        Noeud noeud_voisin_tmp;
        int voisin_tmp_ligne = caze_ligne + deplacement[i][0];
        int voisin_tmp_colonne = caze_colonne + deplacement[i][1];
        noeud_init(noeud_voisin_tmp, voisin_tmp_ligne, voisin_tmp_colonne, VALEUR_INCONNUE, VALEUR_INCONNUE,
                   VALEUR_INCONNUE);

        // Si le Noeud voisin est dans le labyrinthe, n'est pas un mur et qu'il n'est pas deja dans
        // la liste voisin, l'ajouter a la liste voisins
        if (labyrinthe_est_case_valide(lab, noeud_voisin_tmp) && (lab[voisin_tmp_ligne][voisin_tmp_colonne] == ' ')
            && (liste_chercher_noeud(voisins, noeud_voisin_tmp) == INDICE_NON_TROUVE))
            liste_ajouter_noeud(voisins, noeud_voisin_tmp);
    }
}

int labyrinthe_heuristique(const Noeud depart, const Noeud arrivee) {
    int distance_x = abs(noeud_get_colonne(arrivee) - noeud_get_colonne(depart));

    int distance_y = abs(noeud_get_ligne(arrivee) - noeud_get_ligne(depart));

    int distance_heuristique = distance_x + distance_y;

    return distance_heuristique;
}

void labyrinthe_creer_chemin(const Liste fermee, const Noeud arrivee, Liste chemin) {
    int indice_tmp = liste_chercher_noeud(fermee, arrivee);

    Noeud noeud_tmp;
    liste_lire_noeud(fermee, indice_tmp, noeud_tmp);
    while (noeud_get_precedent(noeud_tmp) != -1) {
        liste_ajouter_noeud(chemin, noeud_tmp);

        indice_tmp = noeud_get_precedent(noeud_tmp);
        liste_lire_noeud(fermee, indice_tmp, noeud_tmp);
    }
    liste_ajouter_noeud(chemin, noeud_tmp);
}

// Information tres contradictoire, la description des parametres modifie dit que nous ajoutons n a la liste ferme ici
// Alors que dans l'enonce du tp, on utilise indice_min pour ajouter a la liste fermer, on ne peut pas faire les deux
int labyrinthe_deplacer_minimum(Liste fermee, Liste ouverte) {
    int indice_min = liste_chercher_noeud_min_distance(ouverte);

    Noeud noeud_min;
    liste_lire_noeud(ouverte, indice_min, noeud_min);

    liste_ajouter_noeud(fermee, noeud_min);
    liste_supprimer_noeud(ouverte, indice_min);

    indice_min = liste_get_nb_elements(fermee);
    return indice_min;
}

bool labyrinthe_A_star_etape(const Labyrinthe lab, Liste fermee, Liste ouverte, const Noeud arrivee) {
    bool fin_trouve = false;

    Noeud noeud_ajoute;

    const int indice_ajoutee = labyrinthe_deplacer_minimum(fermee, ouverte);
    liste_lire_noeud(fermee, indice_ajoutee, noeud_ajoute);

    if (noeud_sont_egaux(noeud_ajoute, arrivee))
        fin_trouve = true;
    else {
        Liste voisins;
        liste_init(voisins,MAX_LISTE);

        labyrinthe_voisins(lab, noeud_ajoute, voisins);

        int nb_voisins_calcul = liste_get_nb_elements(voisins);
        for (int indice_calcul = 1; indice_calcul <= nb_voisins_calcul; indice_calcul++) {
            Noeud voisin_calcul;
            liste_lire_noeud(voisins, indice_calcul, voisin_calcul);

            if (liste_chercher_noeud(fermee, voisin_calcul) == INDICE_NON_TROUVE) {
                noeud_set_distance(voisin_calcul, noeud_get_distance(noeud_ajoute) + 1);
                noeud_set_heuristique(voisin_calcul, labyrinthe_heuristique(voisin_calcul, arrivee));
                noeud_set_precedent(voisin_calcul, indice_ajoutee);

                int indice_existant = liste_chercher_noeud(ouverte, voisin_calcul);
                if (indice_existant != INDICE_NON_TROUVE) {
                    Noeud noeud_existant;
                    liste_lire_noeud(ouverte, indice_existant, noeud_existant);

                    int distance_voisin_calcul = noeud_get_distance(voisin_calcul);
                    if (noeud_get_distance(noeud_existant) > distance_voisin_calcul) {
                        noeud_set_distance(noeud_existant, distance_voisin_calcul);
                        noeud_set_precedent(noeud_existant, indice_ajoutee);

                        liste_supprimer_noeud(ouverte, indice_existant);
                        liste_ajouter_noeud(ouverte, noeud_existant);
                    }
                } else
                    liste_ajouter_noeud(ouverte, voisin_calcul);
            }
        }
    }

    return fin_trouve;
}

bool labyrinthe_A_star(const Labyrinthe lab, Noeud depart, const Noeud arrivee, Liste chemin) {
    bool chemin_trouve = false;

    Liste ouverte, fermee;
    liste_init(ouverte,MAX_LISTE);
    liste_init(fermee,MAX_LISTE);
    liste_init(chemin,MAX_LISTE);

    noeud_init(depart, noeud_get_ligne(depart), noeud_get_colonne(depart)
               , 0, labyrinthe_heuristique(depart, arrivee), -1);

    liste_ajouter_noeud(ouverte, depart);

    while (liste_get_nb_elements(ouverte) != 0) {
        if (labyrinthe_A_star_etape(lab, fermee, ouverte, arrivee) == true)
            chemin_trouve = true;
    }

    if (chemin_trouve == true) {
        labyrinthe_creer_chemin(fermee, arrivee, chemin);

        printf("\nBravo! Vous[A*] avez trouvez le chemin! Vous[A*] etes trop cool!!1!1!11\n\n");
    } else {
        printf("\nBooooo! \x1b[%d;%d;%dmVous avez donnez un labyrinthe impossible au A* >:C\n\n",STYLE_BOLD,
               FG_BRIGHT_WHITE,
               BG_BLACK);
        couleurs_reset();
    }

    return chemin_trouve;
}

void test_labyrinthe_voisins() {
    Labyrinthe labyrinthe;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            labyrinthe[i][j] = ' ';
        }
    }

    Liste voisin;
    liste_init(voisin, 4);

    Noeud noeud_test;
    noeud_init(noeud_test, 6, 6, -1, -1, -1);
    labyrinthe_voisins(labyrinthe, noeud_test, voisin);

    liste_afficher(voisin);
}

void test_labyrinthe_A_Star(Labyrinthe lab, const Liste ouverte, const Liste fermee, const Liste chemin) {
    // system("cls");
    for (int i = 1; i <= liste_get_nb_elements(ouverte); i++) {
        int noeud_ouvert_ligne = noeud_get_ligne(ouverte[i]);
        int noeud_ouvert_colonne = noeud_get_colonne(ouverte[i]);
        lab[noeud_ouvert_ligne][noeud_ouvert_colonne] = 'o';
    }
    for (int i = 1; i <= liste_get_nb_elements(fermee); i++) {
        int noeud_fermee_ligne = noeud_get_ligne(fermee[i]);
        int noeud_fermee_colonne = noeud_get_colonne(fermee[i]);
        lab[noeud_fermee_ligne][noeud_fermee_colonne] = 'f';
    }
    for (int i = 1; i <= liste_get_nb_elements(chemin); i++) {
        int noeud_chemin_ligne = noeud_get_ligne(chemin[i]);
        int noeud_chemin_colonne = noeud_get_colonne(chemin[i]);
        lab[noeud_chemin_ligne][noeud_chemin_colonne] = 'c';
    }

    for (int ligne = 1; ligne <= labyrinthe_get_nb_lignes(lab); ligne++) {
        for (int colonne = 1; colonne <= labyrinthe_get_nb_colonnes(lab); colonne++) {
            char tmp = lab[ligne][colonne];
            if (tmp == '*')
                couleurs_set(STYLE_RESET, FG_BRIGHT_WHITE, BG_BRIGHT_WHITE);
            else if (tmp == 'o')
                couleurs_set(STYLE_RESET, FG_BRIGHT_GREEN, BG_BRIGHT_GREEN);
            else if (tmp == 'f')
                couleurs_set(STYLE_RESET, FG_BRIGHT_RED, BG_BRIGHT_RED);
            else if (tmp == 'c')
                couleurs_set(STYLE_RESET, FG_BRIGHT_CYAN, BG_BRIGHT_CYAN);
            else
                couleurs_reset();

            printf("%s%d;%dH%c", "\x1b[", ligne, colonne, tmp);
        }
        printf("\n");
    }
    couleurs_reset();
}

