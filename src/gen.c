#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include "../includes/struct.h"

int gen_matrix(int seed) {
    srand(seed);

    float p = (float)rand()/(float)RAND_MAX;

    


    return 0;
}

int main() {
    gen_matrix(time(NULL));
    return 0;
}