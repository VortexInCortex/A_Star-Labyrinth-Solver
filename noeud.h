//
// Created by duval on 2024-07-23.
//
#ifndef NOEUD_H
#define NOEUD_H

#include <stdbool.h>

//  Les constantes pour un noeud
//  ----------------------------
#define VALEUR_INCONNUE -1
#define NOEUD_NB_CHAMPS 5

//  Le type d'un noeud
//  ------------------
typedef int Noeud[NOEUD_NB_CHAMPS];

//  Declarations des fonction publiques (15)
//  ----------------------------------------

/*
Fonction: noeud_init
Description: Initialise un noeud avec toutes ses informations.
Paramètres:
    - noeud : le noeud a initialiser.
    - ligne : la ligne de la case correspondante pour ce noeud.
    - colonne : la colonne de la case correspondante pour ce noeud.
    - g : la distance du noeud de depart a ce noeud.
    - h : la distance heuristique de ce noeud au noeud d'arrivee.
    - p : l'indice du noeud precedent celui-ci dans le chemin trouve.
Retour: Aucun.
Paramètres modifiés: Les cases de noeud.
*/
void noeud_init(Noeud noeud, int ligne, int colonne, int g, int h, int p);

/*
Fonction: noeud_copier
Description: Copie les information d'un noeud vers un autre noeud.
Paramètres:
    - dest : le noeud qui ve recevoir les informations.
    - src : le noeud qui contient les informations a copier.
Retour: Aucun
Paramètres modifiés: Les cases du noeud dest.
*/
void noeud_copier(Noeud dest, const Noeud src);

/*
Fonction: noeud_get_ligne
Description: Retourne la ligne qui correspond a la case d'un noeud.
Paramètres:
    - noeud : le noeud a partir duquel on va lire l'informations.
Retour: La ligne qui correspond a la case de ce noeud.
Paramètres modifiés: aucun.
*/
int noeud_get_ligne(const Noeud noeud);

/*
Fonction: noeud_get_colonne
Description: Retourne la colonne qui correspond a la case d'un noeud.
Paramètres:
    - noeud : le noeud a partir duquel on va lire l'informations.
Retour: La colonne qui correspond a la case de ce noeud.
Paramètres modifiés: aucun.
*/
int noeud_get_colonne(const Noeud noeud);

/*
Fonction: noeud_get_distance
Description: Retourne la valeur de g contenue dans un noeud.
Paramètres:
    - noeud : le noeud a partir duquel on va lire l'informations.
Retour: La valeur g de ce noeud.
Paramètres modifiés: aucun.
*/
int noeud_get_distance(const Noeud noeud);

/*
Fonction: noeud_get_heuristique
Description: Retourne la valeur de h contenue dans un noeud.
Paramètres:
    - noeud : le noeud a partir duquel on va lire l'informations.
Retour: La valeur h de ce noeud.
Paramètres modifiés: aucun.
*/
int noeud_get_heuristique(const Noeud noeud);

/*
Fonction: noeud_get_precedent
Description: Retourne la valeur de p contenue dans un noeud.
Paramètres:
    - noeud : le noeud a partir duquel on va lire l'informations.
Retour: La valeur p de ce noeud
Paramètres modifiés: Aucun.
*/
int noeud_get_precedent(const Noeud noeud);

/*
Fonction: noeud_set_ligne
Description: Modifie l'information de ligne pour un noeud.
Paramètres:
    - noeud : le noeud dont il faut modifier l'information.
    - ligne : la valeur de ligne a ecrire dans le noeud.
Retour: Aucun.
Paramètres modifiés: la valeur de ligne pour le noeud.
*/
void noeud_set_ligne(Noeud noeud, int ligne);

/*
Fonction: noeud_set_colonne
Description: Modifie l'information de colonne pour un noeud.
Paramètres:
    - noeud : le noeud dont il faut modifier l'information.
    - colonne : la valeur de colonne a ecrire dans le noeud.
Retour: Aucun.
Paramètres modifiés: la valeur de colonne pour le noeud.
*/
void noeud_set_colonne(Noeud noeud, int colonne);

/*
Fonction: noeud_set_distance
Description: Modifie l'information g pour un noeud.
Paramètres:
    - noeud : le noeud dont il faut modifier l'information.
    - distance : la valeur de g a ecrire dans le noeud.
Retour: Aucun.
Paramètres modifiés: la valeur de g pour le noeud.
*/
void noeud_set_distance(Noeud noeud, int g);

/*
Fonction: noeud_set_heuristique
Description: Modifie l'information h pour un noeud.
Paramètres:
    - noeud : le noeud dont il faut modifier l'information.
    - h : distance heuristique entre la case de ce noeud et la case d'arrivee.
Retour: Aucun.
Paramètres modifiés: la valeur de h pour le noeud.
*/
void noeud_set_heuristique(Noeud noeud, int h);

/*
Fonction: noeud_set_precedent
Description: Modifie l'information p pour un noeud.
Paramètres:
    - noeud : le noeud dont il faut modifier l'information.
    - precedent : l'indice du noeud precedent dans la liste.
Retour: Aucun.
Paramètres modifiés: la valeur de p pour le noeud.
*/
void noeud_set_precedent(Noeud noeud, int p);

/*
Fonction: noeud_get_evaluation
Description: Retourne la valeur g+h d'un noeud.
Paramètres:
    - noeud : le noeud a partir duquel on va lire l'informations.
Retour: La valeur g+h de ce noeud.
Paramètres modifiés: aucun.
*/
int noeud_get_evaluation(const Noeud noeud);

/*
Fonction: noeud_sont_egaux
Description: Test si deux noeuds correspondent a la meme case du labyrinthe.
Paramètres:
    - n1 : le premier noeud.
    - n2 : le second noeud.
Retour: true si les 2 noeuds correspondent a la meme case, false sinon.
Paramètres modifiés: Aucun.
*/
bool noeud_sont_egaux(const Noeud n1, const Noeud n2);

/*
Fonction: noeud_afficher
Description: Affiche les informations d'un noeud.
Paramètres:
    - noeud : le noeud a afficher.
Retour: Aucun.
Paramètres modifiés: Aucun.
*/
void noeud_afficher(const Noeud noeud);

#endif //NOEUD_H
