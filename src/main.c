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
    /*MATRIX *m = gen_matrix(time(NULL), 0.5);
    analyse_graph(m);

    save(m, "save.txt");

    free_matrix(m);*/

    LISTE *l = load_liste("g1.txt");
    LISTE *l2 = load_liste("g2.txt");

    display_graph_liste(l);
    display_graph_liste(l2);
    //  save_list(l, "savelist.txt");

    for (int i = 0; i < l->n; i++)
    {
        printf("%s   ", l->vertices[i]);
    }
    printf("\n");
    for (int i = 0; i < l2->n; i++)
    {
        printf("%s   ", l2->vertices[i]);
    }
    printf("\n");

    MATRIX *m = liste_to_matrix(l);

    // analyse_graph_liste(l);

    printf("%d", est_sous_graphe_partiel_liste(l2, l));

    free_liste(l);
    free_matrix(m);

    return 0;
}