#ifndef LISTE_H
#define LISTE_H

#include "noeud.h"
#include <stdbool.h>

//  Les constantes pour une liste de noeuds
//  ---------------------------------------
#define INDICE_NOEUD_INCONNU -1
#define INDICE_NON_TROUVE -1
#define MAX_LISTE 500

//  Le type d'une liste
//  -------------------
typedef Noeud Liste[MAX_LISTE + 1];

//  Declarations des fonctions publiques (12)
//  -----------------------------------------

/*
Fonction: liste_init
Description: Initialise une liste vide avec une taille maximale donnee en parametre.
Paramètres:
    - liste: la liste a initialiser.
    - limite : nombre d'elements maximum pouvant etre mis dans cette liste.
Retour: Aucun.
Paramètres modifiés: Le nombre d'elements de la liste et sa limite.
*/
void liste_init(Liste liste, int limite);

/*
Fonction: liste_get_nb_elements
Description: Retourne le nombre d'elements contenus d'une liste.
Paramètres:
    - liste: la liste dont on veut connaitre le nombre d'elements.
Retour: Le nombre de noeuds contenus dans la liste.
Paramètres modifiés: Aucun.
*/
int liste_get_nb_elements(const Liste liste);

/*
Fonction: liste_get_limite
Description: Retourne le nombre d'elements maximum que l'on peut placer dans cette liste.
Paramètres:
    - liste: la liste dont on veut connaitre la limite.
Retour: Le nombre maximum de noeuds que peut contenir la liste.
Paramètres modifiés: Aucun.
*/
int liste_get_limite(const Liste liste);

/*
Fonction: liste_lire_noeud
Description: Retourne le noeud de la liste dont on donne l'indice.
Paramètres:
    - liste: la liste dont on veut connaitre la limite.
    - indice : indice du noeud desire dans le liste.
Retour: Le noeud de la liste a l'indice .
Paramètres modifiés: Aucun.
*/
void liste_lire_noeud(const Liste liste, int indice, Noeud dest);

/*
Fonction: liste_ecrire_noeud
Description: Copie les valeurs d'un src dans un src de la liste dont on donne son indice.
Paramètres:
    - liste: la liste dont on veut modifier un src.
    - indice : indice du src a modifier dans la liste.
    - src : le src dont on veut copier les valeurs dans celles du src a modifier.
Retour: Aucun.
Paramètres modifiés: Les valeurs du src de la liste dont on donne l'indice.
*/
void liste_ecrire_noeud(Liste liste, int indice, const Noeud src);

/*
Fonction: liste_est_vide
Description: Retourne true si la liste ne contient pas de noeuds, false sinon.
Paramètres:
    - liste: la liste a tester.
Retour: true si la liste est vide, false sinon.
Paramètres modifiés: Aucun.
*/
bool liste_est_vide(const Liste liste);

/*
Fonction: liste_est_pleine
Description: Retourne true si la liste a atteint sa limite en terme de nombre de noeuds.
Paramètres:
    - liste: la liste a tester.
Retour: true si la liste est pleine, false sinon.
Paramètres modifiés: Aucun.
*/
bool liste_est_pleine(const Liste liste);

/*
Fonction: liste_afficher
Description: Affiche les noeuds d'une liste.
Paramètres:
    - liste: La liste dont on veut afficher les noeuds.
Retour: Aucun.
Paramètres modifiés: Aucun.
*/
void liste_afficher(const Liste liste);

/*
Fonction: liste_chercher_noeud
Description: Cherche un noeud dans une liste et retourne son indice dans la liste.
Paramètres:
    - liste: La liste dans laquelle chercher le noeud.
    - noeud : Le noeud recherche.
Retour: L'indice du noeud qui correspond a la meme case que celui donne en parametre.
        Si aucun noeud ne correspond, la fonction retourne INDICE_NON_TROUVE.
Paramètres modifiés: Aucun.
*/
int liste_chercher_noeud(const Liste liste, const Noeud noeud);

/*
Fonction: liste_chercher_noeud_min_distance
Description: Cherche un noeud de la liste dont la valeur f=g+h est minimale.
Paramètres:
    - liste: La liste dans laquelle chercher le noeud.
Retour: L'indice d'un noeud qui minimise sa valeur f.
        Si aucun noeud ne correspond, la fonction retourne INDICE_NON_TROUVE.
Paramètres modifiés: Aucun.
*/
int liste_chercher_noeud_min_distance(const Liste liste);

/*
Fonction: liste_ajouter_noeud
Description: Ajoute un noeud dans une liste.
Paramètres:
    - liste: La liste dans laquelle ajouter le noeud.
    - noeud : Le noeud a ajouter.
Retour: L'indice auquel on a ajouter le noeud.
Paramètres modifiés: Le prochain noeud non utilise dans la liste ainsi que le nombre de noeuds dans la liste.
*/
int liste_ajouter_noeud(Liste liste, const Noeud noeud);

/*
Fonction: liste_supprimer_noeud
Description: Ajoute un noeud dans une liste.
Paramètres:
    - liste: La liste dans laquelle supprimer le noeud.
    - indice : L'indice du noeud a supprimer.
Retour: Aucun.
Paramètres modifiés: L'information du nombre de noeuds dans la liste.
*/
void liste_supprimer_noeud(Liste liste, int indice);

#endif //LISTE_H
