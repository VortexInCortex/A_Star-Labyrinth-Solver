#include "liste.h"
#include <assert.h>
#include <limits.h>
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
	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_LIMITE] = limite;
	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_NB_ELEMENTS] = 0;
}

int liste_get_nb_elements(const Liste liste) {
	return liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_NB_ELEMENTS];
}

int liste_get_limite(const Liste liste) {
	return liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_LIMITE];
}

void liste_lire_noeud(const Liste liste, int indice, Noeud dest) {
	noeud_copier(dest, liste[indice]);
}

void liste_ecrire_noeud(Liste liste, int indice, const Noeud src) {
	noeud_copier(liste[indice], src);
}

bool liste_est_vide(const Liste liste) {
	bool liste_vide = false;

	if (liste_get_nb_elements(liste) == 0)
		liste_vide = true;

	return liste_vide;
}

bool liste_est_pleine(const Liste liste) {
	bool plein = false;

	if (liste_get_nb_elements(liste) == liste_get_limite(liste)) {
		plein = true;
	}
	return plein;
}

void liste_afficher(const Liste liste) {
	int nb_elements = liste_get_nb_elements(liste);

	for (int indice = 1; indice <= nb_elements; indice++) {
		noeud_afficher(liste[indice]);
	}
}


int liste_chercher_noeud(const Liste liste, const Noeud noeud) {
	int indice_noeud = INDICE_NON_TROUVE;
	int nb_elements = liste_get_nb_elements(liste);

	for (int indice = 1; indice <= nb_elements; indice++)
		if (noeud_sont_egaux(noeud, liste[indice]))
			indice_noeud = indice;

	return indice_noeud;
}

int liste_chercher_noeud_min_distance(const Liste liste) {
	int indice_du_plus_petit_eval = INDICE_NON_TROUVE;
	int min_eval = INT_MAX;

	int nb_elements = liste_get_nb_elements(liste);
	for (int indice = 1; indice <= nb_elements; indice++) {
		if (min_eval > noeud_get_evaluation(liste[indice])) {
			min_eval = noeud_get_evaluation(liste[indice]);
			indice_du_plus_petit_eval = indice;
		} else if (min_eval == noeud_get_evaluation(liste[indice])
		           && noeud_get_heuristique(liste[indice_du_plus_petit_eval]) > noeud_get_heuristique(liste[indice])) {
			min_eval = noeud_get_evaluation(liste[indice]);
			indice_du_plus_petit_eval = indice;
		}
	}

	return indice_du_plus_petit_eval;
}

int liste_ajouter_noeud(Liste liste, const Noeud noeud) {
	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_NB_ELEMENTS] += 1;
	int indice_element_du_noeud_a_ajouter = liste_get_nb_elements(liste);

	noeud_copier(liste[indice_element_du_noeud_a_ajouter], noeud);

	return indice_element_du_noeud_a_ajouter;
}

void liste_supprimer_noeud(Liste liste, int indice) {
	for (int indice_deplacement = indice; indice_deplacement < liste_get_nb_elements(liste); indice_deplacement++)
		noeud_copier(liste[indice_deplacement], liste[indice_deplacement + 1]);

	liste[LISTE_INDICE_LIGNE_META][LISTE_INDICE_NB_ELEMENTS] -= 1;
}
