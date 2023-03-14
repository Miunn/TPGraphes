#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "../includes/struct.h"
#include "../includes/matrix.h"

MATRIX *gen_matrix(int seed) {
    srand(seed);

    float p = (float)rand()/(float)RAND_MAX;

    int n = 1 + rand() % 9;

    printf("%d\n", n);

    MATRIX *m = graphe_vide_matrix();
    m->n = n;

    

    return 0;
}

int main() {
    gen_matrix(time(NULL));
    return 0;
}