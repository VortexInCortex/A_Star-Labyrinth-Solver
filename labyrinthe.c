//
// Created by duval on 2024-07-17.
//
#include "labyrinthe.h"
#include "couleurs.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

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
                couleurs_set(STYLE_RESET, FG_BRIGHT_CYAN, BG_BRIGHT_CYAN);
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
    int labyrinthe_nb_lignes = labyrinthe_get_nb_lignes(lab);
    int labyrinthe_nb_colonnes = labyrinthe_get_nb_colonnes(lab);

    const int deplacement[][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};

    for (int i = 0; i < 4; i++) {
        Noeud noeud_voisin_tmp;
        int voisin_tmp_ligne = caze_ligne + deplacement[i][0];
        int voisin_tmp_colonne = caze_colonne + deplacement[i][1];
        noeud_init(noeud_voisin_tmp, voisin_tmp_ligne, voisin_tmp_colonne, VALEUR_INCONNUE, VALEUR_INCONNUE, VALEUR_INCONNUE);
        //METTRE LE P COMME L'INDICE DU NOEUD L'AJOUTANT A LA LISTE CAZE? PEUT PAS LE FAIRE CAR AUCUN ACCES A LA LISTE FERME ET DONC PEUT PAS TROUVER CAZE

        //Si le Noeud voisin est dans le labyrinthe et n'est pas un mur, l'ajouter a la liste ouverte "voisins"
        if ((voisin_tmp_ligne > 0 && voisin_tmp_ligne <= labyrinthe_nb_lignes) && (voisin_tmp_colonne > 0 && voisin_tmp_colonne <= labyrinthe_nb_colonnes)
            && labyrinthe_lire_case(lab, noeud_voisin_tmp) == ' ')
            liste_ajouter_noeud(voisins, noeud_voisin_tmp);
    }
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

int labyrinthe_heuristique(const Noeud depart, const Noeud arrivee) {
    return 0;
}

void labyrinthe_creer_chemin(const Liste fermee, const Noeud arrivee, Liste chemin) {
}

int labyrinthe_deplacer_minimum(Liste fermee, Liste ouverte) {
    return 0;
}

bool labyrinthe_A_star_etape(const Labyrinthe lab, Liste fermee, Liste ouverte, const Noeud arrivee) {
    return 0;
}

bool labyrinthe_A_star(const Labyrinthe lab, Noeud depart, const Noeud arrivee, Liste chemin) {
    return 0;
}
