//
// Created by duval on 2024-07-17.
//
#include "liste.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

//  Constantes pour une liste
//  -------------------------
#define LISTE_INDICE_LIGNE_META     0   /* la ligne qui contient des informations de la liste */
#define LISTE_INDICE_NB_ELEMENTS    0
#define LISTE_INDICE_LIMITE         1

//  Definitions des fonctions publiques (12)
//  ----------------------------------------

void liste_init(Liste liste, int limite) {
	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_LIMITE];
}

int liste_get_nb_elements(const Liste liste) {
	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_NB_ELEMENTS];
}

int liste_get_limite(const Liste liste) {
	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_LIMITE];
}

void liste_lire_noeud(const Liste liste, int indice, Noeud dest) {

	dest[0] = liste[indice][0];
	dest[1] = liste[indice][1];
	dest[2] = liste[indice][2];
	dest[3] = liste[indice][3];
	dest[4] = liste[indice][4];
}

void liste_ecrire_noeud(Liste liste, int indice, const Noeud src) {
		for(int colonne = 0; colonne < 5; colonne++)
	liste[indice][colonne] = src[colonne] ;
}

bool liste_est_vide(const Liste liste) {
	int verificateur = 0;
	for(int ligne = 1; ligne < MAX_LISTE;ligne++) {
		for(int colonne = 0; colonne < 5 ;colonne++) {
			if(liste[ligne][colonne] !=- 1 ) {
				verificateur++;
				return false;
				break;
			}
		}
	}
	if(verificateur == 0) {
		return true;
	}
}

bool liste_est_pleine(const Liste liste) {
	int limite = liste_get_limite(liste);
	int verificateur = 0;
	for(int ligne = 1; ligne <= limite;ligne++) {
		for(int colonne = 0; colonne < 5;colonne++) {
			if(liste[ligne][colonne] == -1) {
				verificateur++;
				return false;
			}
		}
	}
	if(verificateur == 0) {
		return true;
	}
}

void liste_afficher(const Liste liste) {
	int nb_de_noeud = liste_get_nb_elements(liste);
	for(int ligne = 1; ligne <= nb_de_noeud;ligne++) {
		for(int colonne = 0; colonne < 5; colonne++) {
			if(colonne == 0) {
				printf("Noeud#%d ligne:%d colonne:%d g: h:%d p:%d", liste[ligne][colonne],liste[ligne][colonne + 1],liste[ligne][colonne + 2],liste[ligne][colonne + 3], liste[ligne][colonne + 4] );
			}
		}
	}
}

int liste_chercher_noeud(const Liste liste, const Noeud noeud) {
	// A completer
}

int liste_chercher_noeud_min_distance(const Liste liste) {
	// A completer
}

int liste_ajouter_noeud(Liste liste, const Noeud noeud) {
	// A completer
}

void liste_supprimer_noeud(Liste liste, int indice) {
	// A completer
}
