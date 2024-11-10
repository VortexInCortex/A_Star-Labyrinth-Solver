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
	mdwqmdpo
}

int liste_get_nb_elements(const Liste liste) {
	// A completer
}

int liste_get_limite(const Liste liste) {
	// A completer
}

void liste_lire_noeud(const Liste liste, int indice, Noeud dest) {
	// A completer
}

void liste_ecrire_noeud(Liste liste, int indice, const Noeud src) {
	// A completer
}

bool liste_est_vide(const Liste liste) {
	// A completer
}

bool liste_est_pleine(const Liste liste) {
	// A completer
}

void liste_afficher(const Liste liste) {
	// A completer
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
