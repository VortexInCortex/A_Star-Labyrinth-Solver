//
// Created by duval on 2024-07-23.
//
#include "noeud.h"
#include <stdio.h>

//  Definitions des constantes privees pour un noeud
//  ------------------------------------------------
#define NOEUD_INDICE_LIGNE      0
#define NOEUD_INDICE_COLONNE    1
#define NOEUD_INDICE_G          2
#define NOEUD_INDICE_H          3
#define NOEUD_INDICE_P          4

//  Definitions des fonction publiques (15)
//  ---------------------------------------

void noeud_init(Noeud noeud, int ligne, int colonne, int g, int h, int p) {
	// A completer
}

void noeud_copier(Noeud dest, const Noeud src) {
	// A completer
}

int noeud_get_ligne(const Noeud noeud) {
	// A completer
}

int noeud_get_colonne(const Noeud noeud) {
	// A completer
}

int noeud_get_distance(const Noeud noeud) {
	// A completer
}

int noeud_get_heuristique(const Noeud noeud) {
	// A completer
}

int noeud_get_precedent(const Noeud noeud) {
	// A completer
}

void noeud_set_ligne(Noeud noeud, int ligne) {
	// A completer
}

void noeud_set_colonne(Noeud noeud, int colonne) {
	// A completer
}

void noeud_set_distance(Noeud noeud, int g) {
	// A completer
}

void noeud_set_heuristique(Noeud noeud, int h) {
	// A completer
}

void noeud_set_precedent(Noeud noeud, int p) {
	// A completer
}

int noeud_get_evaluation(const Noeud noeud) {
	// A completer
}

bool noeud_sont_egaux(const Noeud n1, const Noeud n2) {
	// A completer
}

void noeud_afficher(const Noeud noeud) {
	// A completer
}
