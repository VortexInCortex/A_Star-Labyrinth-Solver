#include "labyrinthe.h"
#include "couleurs.h"
#include "liste.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

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

    if ((caze_ligne > 0 && caze_ligne <= lab_ligne_max) && (caze_colonne > 0 && caze_colonne <= lab_colonne_max) && (lab[caze_ligne][caze_colonne] == ' '))
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
                couleurs_set(STYLE_RESET, FG_BLACK, BG_BLACK);
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

        // Si le Noeud voisin est dans le labyrinthe, n'est pas un mur et que la liste voisins n'est pas pleine, l'ajouter a la liste ouverte "voisins"
        if (labyrinthe_est_case_valide(lab, noeud_voisin_tmp) && (liste_chercher_noeud(voisins, noeud_voisin_tmp) == INDICE_NON_TROUVE))
            liste_ajouter_noeud(voisins, noeud_voisin_tmp);
    }
}

int labyrinthe_heuristique(const Noeud depart, const Noeud arrivee) {
    int distance_x = abs(noeud_get_colonne(arrivee) - noeud_get_colonne(depart));

    int distance_y = abs(noeud_get_ligne(arrivee) - noeud_get_ligne(depart));

    int distance_heuristique = distance_x + distance_y;

    return distance_heuristique;
}

void labyrinthe_creer_chemin(const Liste fermee, const Noeud arrivee, Liste chemin) {
    int indice_tmp = liste_chercher_noeud(fermee, arrivee);

    while (noeud_get_precedent(fermee[indice_tmp]) != -1) {
        liste_ajouter_noeud(chemin, fermee[indice_tmp]); //erreur cest pas indice tmp car on connais pas lindice de larriver /// alors c a astar
        indice_tmp = noeud_get_precedent(fermee[indice_tmp]);
    }
    liste_ajouter_noeud(chemin, fermee[indice_tmp]);
}

int labyrinthe_deplacer_minimum(Liste fermee, Liste ouverte) {
    int indice_min = liste_chercher_noeud_min_distance(ouverte);

    liste_ajouter_noeud(fermee, ouverte[indice_min]);
    liste_supprimer_noeud(ouverte, indice_min);

    indice_min = liste_get_nb_elements(fermee);
    return indice_min;
}

bool labyrinthe_A_star_etape(const Labyrinthe lab, Liste fermee, Liste ouverte, const Noeud arrivee, /*DEBUG*/Liste chemin) {
    bool fin_trouve = false;

    //DEBUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUG
    Labyrinthe laby;

    Liste voisins;
    liste_init(voisins,MAX_LISTE);

    int indice_actuel = 1;
    int nb_nouveaux_voisins = 0;
    do {
        labyrinthe_voisins(lab, fermee[indice_actuel], voisins);

        nb_nouveaux_voisins = liste_get_nb_elements(ouverte);
        int nb_elements_copier = liste_get_nb_elements(voisins);
        for (int indice_copier = 1; indice_copier <= nb_elements_copier; indice_copier++) {
            if ((liste_chercher_noeud(fermee, voisins[indice_copier]) == INDICE_NON_TROUVE) && (
                    liste_chercher_noeud(ouverte, voisins[indice_copier]) == INDICE_NON_TROUVE))
                liste_ajouter_noeud(ouverte, voisins[indice_copier]);
        }
        nb_nouveaux_voisins = liste_get_nb_elements(ouverte) - nb_nouveaux_voisins;

        //DEBUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUG
        for (int j = 0; j < MAX_LIGNES; j++) {
            for (int i = 0; i < MAX_COLONNES; i++) {
                laby[j][i] = lab[j][i];
            }
        }
        test_labyrinthe_A_Star(laby, ouverte, fermee, chemin);
        int nb_elements_calcul_voisin = liste_get_nb_elements(ouverte);
        for (int indice_calcul_voisin = 1; indice_calcul_voisin <= nb_elements_calcul_voisin; indice_calcul_voisin++) {
            int voisin_ligne_tmp = noeud_get_ligne(ouverte[indice_calcul_voisin]);
            int voisin_colonne_tmp = noeud_get_colonne(ouverte[indice_calcul_voisin]);

            Liste adjacent_a_voisin;
            liste_init(adjacent_a_voisin,MAX_LISTE);
            const int deplacement[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};

            for (int i = 0; i < 4; i++) {
                Noeud tmp;
                noeud_init(tmp, voisin_ligne_tmp + deplacement[i][0], voisin_colonne_tmp + deplacement[i][1],VALEUR_INCONNUE,VALEUR_INCONNUE,VALEUR_INCONNUE);

                int indice_tmp = liste_chercher_noeud(fermee, tmp);
                if (indice_tmp != INDICE_NON_TROUVE)
                    liste_ajouter_noeud(adjacent_a_voisin, fermee[indice_tmp]);
            }

            int nb_elements_adjacent_a_voisin = liste_get_nb_elements(adjacent_a_voisin);
            for (int i = 1; i < nb_elements_adjacent_a_voisin; i++) {
                if (noeud_get_distance(adjacent_a_voisin[i]) > noeud_get_distance(adjacent_a_voisin[i + 1])) {
                    Noeud tmp;

                    noeud_copier(tmp, adjacent_a_voisin[i]);
                    noeud_copier(adjacent_a_voisin[i], adjacent_a_voisin[i + 1]);
                    noeud_copier(adjacent_a_voisin[i + 1], tmp);
                }
            }

            noeud_set_distance(ouverte[indice_calcul_voisin], (noeud_get_distance(adjacent_a_voisin[1]) + 1));
            noeud_set_heuristique(ouverte[indice_calcul_voisin], labyrinthe_heuristique(ouverte[indice_calcul_voisin], arrivee));
            noeud_set_precedent(ouverte[indice_calcul_voisin], liste_chercher_noeud(fermee, adjacent_a_voisin[1]));
        }

        labyrinthe_deplacer_minimum(fermee, ouverte);
        indice_actuel += 1;
        if (noeud_sont_egaux(fermee[indice_actuel], arrivee))
            fin_trouve = true;

        //DEBUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUG
        for (int j = 0; j < MAX_LIGNES; j++) {
            for (int i = 0; i < MAX_COLONNES; i++) {
                laby[j][i] = lab[j][i];
            }
        }
        test_labyrinthe_A_Star(laby, ouverte, fermee, chemin);
    } while (!(nb_nouveaux_voisins != 0) + (fin_trouve == false));
    return fin_trouve;
}

bool labyrinthe_A_star(const Labyrinthe lab, Noeud depart, const Noeud arrivee, Liste chemin) {
    bool chemin_trouve = false;

    noeud_init(depart, noeud_get_ligne(depart), noeud_get_colonne(depart), 0, labyrinthe_heuristique(depart, arrivee), -1);

    Liste ouverte, fermee;
    liste_init(ouverte,MAX_LISTE);
    liste_init(fermee,MAX_LISTE);

    liste_ajouter_noeud(fermee, depart);

    system("cls");
    if ((chemin_trouve = labyrinthe_A_star_etape(lab, fermee, ouverte, arrivee, chemin)) == true) {
        labyrinthe_creer_chemin(fermee, arrivee, chemin);
        //DEBUUUUUUUUUUUUUUUUUUG
        Labyrinthe laby;

        for (int j = 0; j < MAX_LIGNES; j++) {
            for (int i = 0; i < MAX_COLONNES; i++) {
                laby[j][i] = lab[j][i];
            }
        }
        test_labyrinthe_A_Star(laby, ouverte, fermee, chemin);

        printf("\n\nBravo! Vous avez trouvez le chemin! Vous[A*] etes trop cool!!1!1!11\n");

        system("pause");
    } else {
        //DEBUUUUUUUUUUUUUUUUUUG
        Labyrinthe laby;

        for (int j = 0; j < MAX_LIGNES; j++) {
            for (int i = 0; i < MAX_COLONNES; i++) {
                laby[j][i] = lab[j][i];
            }
        }
        test_labyrinthe_A_Star(laby, ouverte, fermee, chemin);

        printf("\n\nBooooo! \x1b[%d;%d;%dmVous avez donnez un labyrinthe impossible au A* >:C",STYLE_BLINK,FG_BLACK,BG_BLACK);
        couleurs_reset();

        system("pause");
    }
    return chemin_trouve;
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

void test_labyrinthe_A_Star(Labyrinthe lab, const Liste ouverte, const Liste fermee, const Liste chemin) {
    // system("cls");
    for (int i = 1; i <= liste_get_nb_elements(ouverte); i++) {
        int noeud_ouvert_ligne = noeud_get_ligne(ouverte[i]);
        int noeud_ouvert_colonne = noeud_get_colonne(ouverte[i]);
        lab[noeud_ouvert_ligne][noeud_ouvert_colonne] = 'o';
    }
    for (int i = 1; i <= liste_get_nb_elements(fermee); i++) {
        int noeud_fermee_ligne = noeud_get_ligne(fermee[i]);
        int noeud_fermee_colonne = noeud_get_colonne(fermee[i]);
        lab[noeud_fermee_ligne][noeud_fermee_colonne] = 'f';
    }
    for (int i = 1; i <= liste_get_nb_elements(chemin); i++) {
        int noeud_chemin_ligne = noeud_get_ligne(chemin[i]);
        int noeud_chemin_colonne = noeud_get_colonne(chemin[i]);
        lab[noeud_chemin_ligne][noeud_chemin_colonne] = 'c';
    }

    for (int ligne = 1; ligne <= labyrinthe_get_nb_lignes(lab); ligne++) {
        for (int colonne = 1; colonne <= labyrinthe_get_nb_colonnes(lab); colonne++) {
            char tmp = lab[ligne][colonne];
            if (tmp == '*')
                couleurs_set(STYLE_RESET, FG_BLACK, BG_BLACK);
            else if (tmp == 'o')
                couleurs_set(STYLE_RESET, FG_BRIGHT_GREEN, BG_BRIGHT_GREEN);
            else if (tmp == 'f')
                couleurs_set(STYLE_RESET, FG_BRIGHT_RED, BG_BRIGHT_RED);
            else if (tmp == 'c')
                couleurs_set(STYLE_RESET, FG_BRIGHT_CYAN, BG_BRIGHT_CYAN);
            else
                couleurs_reset();

            printf("%s%d;%dH%c", "\x1b[", ligne, colonne, tmp);
        }
        printf("\n");
    }
    couleurs_reset();
}
