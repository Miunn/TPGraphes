#ifndef DEF_MATRIX
#define DEF_MATRIX

#include "../includes/struct.h"

void display_graph_matrix(MATRIX *m);
void free_matrix(MATRIX *m);
MATRIX *graphe_vide_matrix();
void add_sommet_matrix(MATRIX *m, VERTICE s);
void add_matrix(MATRIX *m, VERTICE *i, VERTICE *j);
void supp_matrix(MATRIX *m, VERTICE *i, VERTICE *j);
int est_voisin(MATRIX *m, VERTICE *i, VERTICE *j);
int inclus_sommet_matrix(MATRIX *G1, MATRIX *G2, int strict);
int inclus_aretes_matrix(MATRIX *g1, MATRIX *g2);
int est_partiel_matrix(MATRIX *m1, MATRIX *m2);
int est_sous_graphe_matrix(MATRIX *m1, MATRIX *m2);
int est_sous_graphe_partiel_matrix(MATRIX *m1, MATRIX *m2);
int est_clique_matrix(MATRIX *m1, MATRIX *m2);
int est_stable_matrix(MATRIX *m1, MATRIX *m2);
int calcul_distance_matrix(MATRIX *m, VERTICE *a, VERTICE *b, VERTICE **ban, int n_ban,  int d);
void calculs_distances_matrix(MATRIX *m, DIST **dists);
DIST *donne_diametre_matrix(MATRIX *m, DIST **dists);
int donne_centre_matrix(MATRIX *m, DIST **dists, VERTICE **centres_list, int *m_radius);
void calcul_degre_matrix(MATRIX *m, int *degs);
int donne_centre_degre_matrix(MATRIX *m, VERTICE **centres_list, int *deg_max);

#endif