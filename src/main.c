/**
 * @file TP - Graphes BOUDADI Liam - CAULIER Remi.c
 * @author BOUDADI Liam & CAULIER Rémi
 * @brief Fichier final d'avancement
 * @version 2.0
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../includes/struct.h"
#include "../includes/general.h"
#include "../includes/matrix.h"
#include "../includes/list.h"
#include "../includes/io.h"
#include "../includes/generator.h"

int main()
{
    FILE *output_analyse = fopen("output.txt", "w");

    MATRIX *m = gen_matrix(time(NULL), 0.5);

    analyse_graph(m, output_analyse);
    fclose(output_analyse);

    save(m, "save.txt");

    free_matrix(m);

    return 0;
}