#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include "liste.h"
#include <stdbool.h>

//  Les constantes d'un labyrinthe
//  ------------------------------
#define MAX_LIGNES 50
#define MAX_COLONNES 50

//  Le type pour un labyrinthe
//  --------------------------
typedef char Labyrinthe[MAX_LIGNES + 1][MAX_COLONNES + 1];

//  Declarations des fonctions publiques (12)
//  -----------------------------------------

/*
Fonction: labyrinthe_get_nb_lignes
Description: Retourne le nombre de lignes d'un lab.
Paramètres:
    - lab : le lab dont on veut le nombre de lignes.
Retour: Le nombre de lignes de ce lab.
Paramètres modifiés: Aucun.
*/
int labyrinthe_get_nb_lignes(const Labyrinthe lab);

/*
Fonction: labyrinthe_get_nb_colonnes
Description: Retourne le nombre de colonnes d'un lab.
Paramètres:
    - lab : le lab dont on veut le nombre de colonnes.
Retour: Le nombre de colonnes de ce lab.
Paramètres modifiés: Aucun.
*/
int labyrinthe_get_nb_colonnes(const Labyrinthe lab);

/*
Fonction: labyrinthe_est_position_valide
Description: Verifie si une position de case est valide pour un lab.
Paramètres:
    - lab : le lab.
    - ligne : la ligne de la case a tester.
    - colonne : la colonne de la case a tester.
Retour: true si la case se trouve a l'interieur du lab, false sinon.
Paramètres modifiés: Aucun.
*/
bool labyrinthe_est_case_valide(const Labyrinthe lab, const Noeud caze);

/*
Fonction: labyrinthe_lire_case
Description: Retourne la caractere contenu dans une case d'un lab.
Paramètres:
    - lab : le lab.
    - ligne : la ligne de la case.
    - colonne : la colonne de la case.
Retour: le caractere qui se trouve dans la case specifiee par ligne et colonne.
Paramètres modifiés: Aucun.
*/
char labyrinthe_lire_case(const Labyrinthe lab, const Noeud caze);

/*
Fonction: labyrinthe_charger
Description: Lit un lab a partir d'un fichier texte.
Paramètres:
    - nom_fichier : le nom du fichier texte contenant la description du lab.
    - lab : le lab a initialiser a partir du fichier.
Retour: Aucun.
Paramètres modifiés: Le lab.
*/
void labyrinthe_lire_fichier(const char nom_fichier[], Labyrinthe lab);

/*
Fonction: labyrinthe_afficher
Description: Affiche un lab dans la console.
Paramètres:
    - lab : le lab a afficher.
Retour: Aucun.
Paramètres modifiés: Aucun.
*/
void labyrinthe_afficher(const Labyrinthe lab);

/*
Fonction: labyrinthe_voisins
Description: Calcule la liste des voisins d'une case dans un lab.
Paramètres:
    - lab : le lab.
    - ligne : la ligne de la case dont on veut les voisins.
    - colonne : la colonne de la case dont on veut les voisins.
    - voisins : la liste ou seront ajoutes les voisins trouves.
Retour: Aucun.
Paramètres modifiés: La liste de voisins qui contiendra tous les voisins de la case apres execution de la fonction.
*/
void labyrinthe_voisins(const Labyrinthe lab, const Noeud caze, Liste voisins);

/*
Fonction: labyrinthe_heuristique
Description: Calcule la distance Manhattan entre 2 cases.
Paramètres:
    - ligne_depart : la ligne de la case de depart.
    - colonne_depart : la colonne de la case de depart.
    - ligne_arrivee : la ligne de la case d'arrivee.
    - colonne_arrivee : la colonne de la casse d'arrivee.
Retour: La distance Manhattan entre les 2 cases.
Paramètres modifiés: Aucune.
*/
int labyrinthe_heuristique(const Noeud depart, const Noeud arrivee);

/*
Fonction: labyrinthe_creer_chemin
Description: Cree un chemin a partir d'une liste fermee et de la case d'arrivee.
Paramètres:
    - fermee : la liste fermee a partir de laquelle on va reconstruire un chemin.
    - ligne_arrivee : la ligne de la case d'arrivee.
    - colonne_arrivee : la colonne de la case d'arrivee.
    - chemin : la liste qui contiendra tous les noeuds du chemin.
Retour: Aucun.
Paramètres modifiés: La liste contenant le chemin construit.
*/
void labyrinthe_creer_chemin(const Liste fermee, const Noeud arrivee, Liste chemin);

/*
Fonction: labyrinthe_deplacer_minimum
Description: Cherche un noeud qui minimise f dans une liste (ouverte) et le deplace dans une autre liste (fermee).
Paramètres:
    - fermee : La liste fermee dans laquelle on va deplacer le noeud minimal.
    - ouverte : La liste ouverte de laquelle on va extraire le noeud minimisant f.
Retour: L'indice du noeud dans la liste fermee ou on a place le noeud minimal.
Paramètres modifiés: La liste ouverte et la liste fermee.
*/
int labyrinthe_deplacer_minimum(Liste fermee, Liste ouverte);

/*
Fonction: labyrinthe_A_star_etape
Description: .
Paramètres:
    - lab : la liste fermee dans laquelle on va deplacer le noeud minimal.
    - fermee : La liste fermee.
    - ouverte : La liste ouverte.
    - arrivee : Le noeud d'arrivee.
Retour: True si on a atteint le noeud d'arrivee, false sinon.
Paramètres modifiés: La liste ouverte dont on a enleve un noeud et la liste fermee dans laquelle on a ajoute ce noeud.
*/
bool labyrinthe_A_star_etape(const Labyrinthe lab, Liste fermee, Liste ouverte, const Noeud arrivee
                             /*DEBUG*/, Liste chemin);

/*
Fonction: labyrinthe_A_star
Description: Calcule un plus court chemin entre 2 cases dans un lab.
Paramètres:
    - lab : le lab dans lequel on cherche un plus court chemin
    - extremites : une liste constitues des 2 cases a joindre.
    - chemin : la liste dans laquelle placer le plus court chemin trouve.
Retour: true si un chemin a ete trouve, false sinon.
Paramètres modifiés: Le chemin contiendra la liste des noeuds du plus court chemin trouve.
                     La liste sera vide si aucun chemin n'a ete trouve.
*/
bool labyrinthe_A_star(const Labyrinthe lab, Noeud depart, const Noeud arrivee, Liste chemin);

void test_labyrinthe_voisins();

void test_labyrinthe_A_Star(Labyrinthe lab, const Liste ouverte, const Liste fermee, const Liste chemin);

#endif //LABYRINTHE_H
