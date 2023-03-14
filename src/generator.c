#include <stdlib.h>
#include <stdio.h>

#include "../includes/struct.h"
#include "../includes/matrix.h"

/**
 * @brief Generate a graph represented under matrix representation
 * 
 * @param seed Seed for the random generation
 * @param density Density of edges in the graph
 * @return MATRIX* 
 */
MATRIX *gen_matrix(int seed, float density) {
    srand(seed);

    // Generate an amount of vertices between 2 and 10
    int n = 2 + rand() % 9;

    MATRIX *m = graphe_vide_matrix();

    char alphabet[10] = "ABCDEFGHIJ";

    // Create the n-th vertices
    for (int i = 0; i < n; i++) {
        fflush(stdout);
        char *name = malloc(2*sizeof(char));
        name[0] = alphabet[i];
        name[1] = '\0';
        add_sommet_matrix(m, (VERTICE){name, i});
    }
    
    // Created the edges based on the density given
    for (int i = 0; i < m->n; i++) {
        for (int j = i + 1; j < m->n; j++) {
            if ((float)rand()/(float)RAND_MAX <= density) {
                add_matrix(m, &m->vertices[i], &m->vertices[j]);
            }
        }
    }
    return m;
}