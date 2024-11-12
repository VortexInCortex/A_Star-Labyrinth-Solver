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
	noeud[NOEUD_INDICE_LIGNE] = ligne;
	noeud[NOEUD_INDICE_COLONNE] = colonne;
	noeud[NOEUD_INDICE_G] = g;
	noeud[NOEUD_INDICE_H] = h;
	noeud[NOEUD_INDICE_P] = p;
}

void noeud_copier(Noeud dest, const Noeud src) {
	dest[NOEUD_INDICE_LIGNE] = src[NOEUD_INDICE_LIGNE];
	dest[NOEUD_INDICE_COLONNE] = src[NOEUD_INDICE_COLONNE];
	dest[NOEUD_INDICE_G] = src[NOEUD_INDICE_G];
	dest[NOEUD_INDICE_H] = src[NOEUD_INDICE_H];
	dest[NOEUD_INDICE_P] = src[NOEUD_INDICE_P];
}

int noeud_get_ligne(const Noeud noeud) {
	return noeud[NOEUD_INDICE_LIGNE];
}

int noeud_get_colonne(const Noeud noeud) {
	return noeud[NOEUD_INDICE_COLONNE];
}

int noeud_get_distance(const Noeud noeud) {
	return noeud[NOEUD_INDICE_G];
}

int noeud_get_heuristique(const Noeud noeud) {
	return noeud[NOEUD_INDICE_H];
}

int noeud_get_precedent(const Noeud noeud) {
	return noeud[NOEUD_INDICE_P];
}

void noeud_set_ligne(Noeud noeud, int ligne) {
	noeud[NOEUD_INDICE_LIGNE] = ligne;
}

void noeud_set_colonne(Noeud noeud, int colonne) {
	noeud[NOEUD_INDICE_COLONNE] = colonne;
}

void noeud_set_distance(Noeud noeud, int g) {
	noeud[NOEUD_INDICE_G] = g;
}

void noeud_set_heuristique(Noeud noeud, int h) {
	noeud[NOEUD_INDICE_H] = h;
}

void noeud_set_precedent(Noeud noeud, int p) {
	noeud[NOEUD_INDICE_P] = p;
}

int noeud_get_evaluation(const Noeud noeud) {
	int evaluation = noeud[NOEUD_INDICE_G] + noeud[NOEUD_INDICE_H];
	return evaluation;
}

bool noeud_sont_egaux(const Noeud n1, const Noeud n2) {
	bool sont_egaux = false;

	if (n1[NOEUD_INDICE_LIGNE] == n2[NOEUD_INDICE_LIGNE] && n1[NOEUD_INDICE_COLONNE] == n2[NOEUD_INDICE_COLONNE])
		sont_egaux = true;

	return sont_egaux;
}

void noeud_afficher(const Noeud noeud) {
	printf("[(l: %i, c: %i) g: %i,h: %i,p: %i\n", noeud[NOEUD_INDICE_LIGNE], noeud[NOEUD_INDICE_COLONNE]
	       , noeud[NOEUD_INDICE_G], noeud[NOEUD_INDICE_H], noeud[NOEUD_INDICE_P]);
}

void test_noeud_afficher() {
	Noeud noeud_test;
	noeud_init(noeud_test, 6, 6, -1, -1, -1);

	noeud_afficher(noeud_test);
}
