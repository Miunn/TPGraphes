#ifndef DEF_GENERAL
#define DEF_GENERAL

#include "../includes/struct.h"

int excentricite(VERTICE *s, DIST **dists, int n_dists);
LISTE *matrix_to_liste(MATRIX *m);
MATRIX *liste_to_matrix(LISTE *l);
<<<<<<< HEAD
void analyse_graph(MATRIX *m, FILE *stream);
=======
void analyse_graph(MATRIX *m);
void analyse_graph_liste(LISTE *m);
>>>>>>> origin/feat-6

#endif