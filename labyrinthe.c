//
// Created by duval on 2024-07-17.
//
#include "labyrinthe.h"
#include "couleurs.h"
#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
	// A completer
}

void labyrinthe_set_nb_colonnes(Labyrinthe lab, int nb_colonnes) {
	// A completer
}

//  Definitions des fonctions publiques (12)
//  ----------------------------------------

int labyrinthe_get_nb_lignes(const Labyrinthe lab) {
	// A completer
}

int labyrinthe_get_nb_colonnes(const Labyrinthe lab) {
	// A completer
}

bool labyrinthe_est_case_valide(const Labyrinthe lab, const Noeud caze) {
	// A completer
}

char labyrinthe_lire_case(const Labyrinthe lab, const Noeud caze) {
	// A completer
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
	// A completer
}

void labyrinthe_voisins(const Labyrinthe lab, const Noeud caze, Liste voisins) {
	// A completer
}

int labyrinthe_heuristique(const Noeud depart, const Noeud arrivee) {
	// A completer
}

void labyrinthe_creer_chemin(const Liste fermee, const Noeud arrivee, Liste chemin) {
	// A completer
}

int labyrinthe_deplacer_minimum(Liste fermee, Liste ouverte) {
	// A completer
}

bool labyrinthe_A_star_etape(const Labyrinthe lab, Liste fermee, Liste ouverte, const Noeud arrivee) {
	// A completer
}

bool labyrinthe_A_star(const Labyrinthe lab, Noeud depart, const Noeud arrivee, Liste chemin) {
	// A completer
}
