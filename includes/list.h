#ifndef DEF_LIST
#define DEF_LIST

#include "../includes/struct.h"

void display_graph_liste(LISTE *l);
void free_liste(LISTE *l);
LISTE *graphe_vide_liste();
void add_sommet_liste(LISTE *G, VERTICE v);
void add_liste(LISTE *G, VERTICE *v1, VERTICE *v2);
void supp_liste(LISTE *G, VERTICE *v1, VERTICE *v2);
int est_voisin_liste(LISTE *G, int i, int j);
int inclus_sommet_liste(LISTE *G1, LISTE *G2, int strict);
int inclus_aretes_liste(LISTE *l1, LISTE *l2);
int est_partiel_liste(LISTE *m1, LISTE *m2);
int est_sous_graphe_liste(LISTE *l1, LISTE *l2);
int est_sous_graphe_partiel_liste(LISTE *l1, LISTE *l2);
int est_clique_liste(LISTE *l1, LISTE *l2);
int est_stable_liste(LISTE *l1, LISTE *l2);
int calcul_distance_liste(LISTE *l, VERTICE *a, VERTICE *b, VERTICE **ban, int n_ban, int d);
void calculs_distances_liste(LISTE *l, DIST **dists);
DIST *donne_diametre_liste(LISTE *l, DIST **dists);
int donne_centre_liste(LISTE *l, DIST **dists, VERTICE **centres_list, int *m_radius);
void calcul_degre_liste(LISTE *l, int *degs);
int donne_centre_degre_liste(LISTE *l, VERTICE **centres_list, int *deg_max);

#endif