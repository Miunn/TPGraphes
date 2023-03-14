/**
 * @file TP - Graphes BOUDADI Liam - CAULIER Remi.c
 * @author BOUDADI Liam & CAULIER Rémi
 * @brief 1er fichier de l'avancement du TP
 * @version 2.0
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/general.h"
#include "../includes/matrix.h"
#include "../includes/list.h"
#include "../includes/io.h"

void analyse_graph(char *path) {
    MATRIX *m = load(path);

    display_graph_matrix(m);

    printf("------------------------\n");

    int n_dists = (m->n * (m->n - 1)) / 2;
    DIST **dists = (DIST **)malloc(n_dists * sizeof(DIST *));
    calculs_distances_matrix(m, dists);

    printf("--------Distances-------\n");
    for (int i = 0; i < n_dists; i++) {
        printf("[%s - %s] -> %d\t", dists[i]->start->nom, dists[i]->end->nom, dists[i]->d);

        if (i % 2) {
            printf("\n");
        }
    }

    printf("\n------------------------\n");
    printf("--------Diametre--------\n");

    DIST *diameter = donne_diametre_matrix(m, dists);
    printf("[%s - %s] -> %d\n", diameter->start->nom, diameter->end->nom, diameter->d);

    printf("------------------------\n");
    printf("------Excentricités-----\n");

    for (int i = 0; i < m->n; i++) {
        printf("[%s] -> %d\t", m->vertices[i].nom, excentricite(&m->vertices[i], dists, n_dists));

        if (i % 2) {
            printf("\n");
        }
    }

    printf("\n------------------------\n");
    printf("---------Centres--------\n");

    VERTICE **centres = (VERTICE **) malloc(m->n * sizeof(VERTICE *));
    for (int i = 0; i < m->n; i++) {
        centres[i] = NULL;
    }

    int radius = 0;
    int n_centres = donne_centre_matrix(m, dists, centres, &radius);

    for (int i = 0; i < n_centres; i++) {
        printf("%s\t", centres[i]->nom);
    }

    for (int i = 0; i < n_dists; i++) {
        free(dists[i]);
    }
    free(dists);

    printf("\n------------------------\n");
    printf("----------Rayon---------\n");

    printf("Rayon: %d\n", radius);

    printf("------------------------\n");
    printf("----------Degrés--------\n");
    int *degres = (int *) calloc(m->n, sizeof(int));
    calcul_degre_matrix(m, degres);
    for (int i = 0; i < m->n; i++) {
        printf("[%s] -> %d\t", m->vertices[i].nom, degres[i]);

        if (i % 2) {
            printf("\n");
        }
    }

    printf("\n------------------------\n");
    printf("-----Centres degrés-----\n");
    int deg_max;
    int n_centres_deg = donne_centre_degre_matrix(m, centres, &deg_max);
    for (int i = 0; i < n_centres_deg; i++) {
        printf("%s\t", centres[i]->nom);
    }
    printf("\n");
    printf("Degré max: %d\n", deg_max);

    printf("------------------------\n");

    free(centres);  // Vertices struct in centres are vertices from matrix so we only free the array
    free_matrix(m);
}

int main()
{
    analyse_graph("g1.txt");

    MATRIX *m = load("g1.txt");
    display_graph_matrix(m);
    save(m, "save.txt");

    MATRIX *t = load("save.txt");
    display_graph_matrix(t);
    return 0;
}