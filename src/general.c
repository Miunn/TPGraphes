#include <string.h>

#include "../headers/struct.h"
#include "../headers/list.h"

/**
 * @brief Compute the eccentricity for a given vertice S
 * 
 * @param s The VERTICE to long for
 * @param dists Array of all pairs distances
 * @param n_dists number of distances
 * @return int Graph's eccentricity 
 */
int excentricite(VERTICE *s, DIST **dists, int n_dists) {
    int eccentricity = 0;

    for (int i = 0; i < n_dists; i++) {
        if (strcmp(dists[i]->start->nom, s->nom) == 0 || strcmp(dists[i]->end->nom, s->nom) == 0) {
            if (dists[i]->d > eccentricity) {
                eccentricity = dists[i]->d;
            }
        }
    }
    return eccentricity;
}

LISTE *matrix_to_liste(MATRIX *m)
{
    LISTE *l = graphe_vide_liste();
    *l->vertices = *m->vertices;
    for (int i = 0; i < m->n; i++)
    {
        add_sommet_liste(l, l->vertices[i]);
    }
    for (int i = 0; i < m->n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (m->graph[j][i] == 1)
            {
                add_liste(l, &l->vertices[i], &l->vertices[j]);
            }
        }
    }
    return l;
}

/*MATRIX *liste_to_matrix(LISTE *l)
{
    MATRIX *m = graphe_vide_matrix();
    *m->vertices = *l->vertices;
    for (int i =0; i < l->n; i++) {
        add_sommet_matrix(m, l->vertices[i]);
    }
    int size;
    for (int i = 0; i < l->n; i++)
    {
        for (int j = 0; j < l->sizes[i]; j++)
        {
            add_matrix(m, i + 1, l->graph[i][j]);
        }
    }
    return m;
}*/
