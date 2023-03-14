#ifndef DEF_GENERAL
#define DEF_GENERAL

#include "../includes/struct.h"

int excentricite(VERTICE *s, DIST **dists, int n_dists);
LISTE *matrix_to_liste(MATRIX *m);
MATRIX *liste_to_matrix(LISTE *l);
void analyse_graph(MATRIX *m, FILE *stream);

#endif