#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "../includes/struct.h"
#include "../includes/matrix.h"

MATRIX *gen_matrix(int seed) {
    srand(seed);

    float p = 0.7;

    int n = 2 + rand() % 9; // Génération d'un nombre de sommets compris entre 2 et 10

    printf("%d\n", n);

    MATRIX *m = graphe_vide_matrix();

    for (int i = 0; i < n; i++) {
        fflush(stdout);
        char *name = malloc(2*sizeof(char));
        name[0] = 65+i;
        name[1] = '\0';
        add_sommet_matrix(m, (VERTICE){name, i});
    }
    
    for (int i = 0; i < m->n; i++) {
        for (int j = i + 1; j < m->n; j++) {
            if ((float)rand()/(float)RAND_MAX <= p) {
                add_matrix(m, &m->vertices[i], &m->vertices[j]);
            }
        }
    }
    return m;
}