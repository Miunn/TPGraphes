/**
 * @file general.c
 * @author BOUDADI Liam - CAULIER Rémi
 * @brief Contain function usefull or used for both representation (list and matrix)
 * @version 1.0
 * @date 2023-03-14
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/matrix.h"
#include "../includes/list.h"
#include "../includes/io.h"

/**
 * @brief Compute the eccentricity for a given vertice S
 *
 * @param s The VERTICE to long for
 * @param dists Array of all pairs distances
 * @param n_dists number of distances
 * @return int Graph's eccentricity
 */
int excentricite(VERTICE *s, DIST **dists, int n_dists)
{
    int eccentricity = 0;

    for (int i = 0; i < n_dists; i++)
    {
        if (strcmp(dists[i]->start->nom, s->nom) == 0 || strcmp(dists[i]->end->nom, s->nom) == 0)
        {
            if (dists[i]->d > eccentricity)
            {
                eccentricity = dists[i]->d;
            }
        }
    }
    return eccentricity;
}

/**
 * @brief Convert a graph under MATRIX representation to a LIST representation using a tempory file
 * 
 * @param m The matrix graph to convert
 * @return LISTE* The LIST representation
 */
LISTE *matrix_to_liste(MATRIX *m)
{
    save(m, "tempMATRIX");
    LISTE *l = load_liste("tempMATRIX");
    remove("tempMATRIX");
    return l;
}

/**
 * @brief Convert a graph under LIST representation to a MATRIX representation using a tempory file
 * 
 * @param l The list graph to convert
 * @return MATRIX* The MATRIX representation
 */
MATRIX *liste_to_matrix(LISTE *l) {
    save_list(l, "tempLIST");
    MATRIX *m = load("tempLIST");
    remove("tempLIST");
    return m;
}

/**
 * @brief Compute several caracteristics for the graph given.
 * - Distances between each edges pairs
 * - Diameter
 * - Eccentricities
 * - Centers
 * - Radius
 * - Levels for each edges
 * - Centers based on levels
 * 
 * @param m Matrix representation to display
 * @param stream Output stream, if NULL print to stdout
 */
void analyse_graph(MATRIX *m, FILE *stream) {
    if (stream == NULL) {
        stream = stdout;
    }

    display_graph_matrix(m, stream);

    fprintf(stream, "--------------------------------\n");
    fprintf(stream, "Si le graphe n'est pas connexe, certains résultats\nprésentés ci-dessous peuvent êtres erronés.\n");
    fprintf(stream, "--------------------------------\n");

    int n_dists = (m->n * (m->n - 1)) / 2;
    DIST **dists = (DIST **)malloc(n_dists * sizeof(DIST *));
    calculs_distances_matrix(m, dists);

    fprintf(stream, "------------Distances-----------\n");
    for (int i = 0; i < n_dists; i++) {
        fprintf(stream, "[%s - %s] -> %d\t", dists[i]->start->nom, dists[i]->end->nom, dists[i]->d);

        if (i % 2) {
            fprintf(stream, "\n");
        }
    }

    fprintf(stream, "\n--------------------------------\n");
    fprintf(stream, "------------Diametre------------\n");

    DIST *diameter = donne_diametre_matrix(m, dists);
    fprintf(stream, "[%s - %s] -> %d\n", diameter->start->nom, diameter->end->nom, diameter->d);

    fprintf(stream, "--------------------------------\n");
    fprintf(stream, "----------Excentricités---------\n");

    for (int i = 0; i < m->n; i++) {
        fprintf(stream, "[%s] -> %d\t", m->vertices[i].nom, excentricite(&m->vertices[i], dists, n_dists));

        if (i % 2) {
            fprintf(stream, "\n");
        }
    }

    fprintf(stream, "\n--------------------------------\n");
    fprintf(stream, "-------------Centres------------\n");

    VERTICE **centres = (VERTICE **)malloc(m->n * sizeof(VERTICE *));
    for (int i = 0; i < m->n; i++)
    {
        centres[i] = NULL;
    }

    int radius = 0;
    int n_centres = donne_centre_matrix(m, dists, centres, &radius);

    for (int i = 0; i < n_centres; i++) {
        fprintf(stream, "%s\t", centres[i]->nom);
    }

    for (int i = 0; i < n_dists; i++)
    {
        free(dists[i]);
    }
    free(dists);

    fprintf(stream, "\n--------------------------------\n");
    fprintf(stream, "--------------Rayon-------------\n");

    fprintf(stream, "Rayon: %d\n", radius);

    fprintf(stream, "--------------------------------\n");
    fprintf(stream, "--------------Degrés------------\n");
    int *degres = (int *) calloc(m->n, sizeof(int));
    calcul_degre_matrix(m, degres);
    for (int i = 0; i < m->n; i++) {
        fprintf(stream, "[%s] -> %d\t", m->vertices[i].nom, degres[i]);

        if (i % 2) {
            fprintf(stream, "\n");
        }
    }

    fprintf(stream, "\n--------------------------------\n");
    fprintf(stream, "---------Centres degrés---------\n");
    int deg_max;
    int n_centres_deg = donne_centre_degre_matrix(m, centres, &deg_max);
    for (int i = 0; i < n_centres_deg; i++) {
        fprintf(stream, "%s\t", centres[i]->nom);
    }
    fprintf(stream, "\n");
    fprintf(stream, "Degré max: %d\n", deg_max);

    fprintf(stream, "--------------------------------\n");

    free(centres); // Vertices struct in centres are vertices from matrix so we only free the array
}

void analyse_graph_liste(LISTE *m)
{
    display_graph_liste(m);

    printf("--------------------------------\n");
    printf("Si le graphe n'est pas connexe, certains résultats\nprésentés ci-dessous peuvent êtres erronés.\n");
    printf("--------------------------------\n");

    int n_dists = (m->n * (m->n - 1)) / 2;
    DIST **dists = (DIST **)malloc(n_dists * sizeof(DIST *));
    calculs_distances_liste(m, dists);

    printf("------------Distances-----------\n");
    for (int i = 0; i < n_dists; i++)
    {
        printf("[%s - %s] -> %d\t", dists[i]->start->nom, dists[i]->end->nom, dists[i]->d);

        if (i % 2)
        {
            printf("\n");
        }
    }

    printf("\n--------------------------------\n");
    printf("------------Diametre------------\n");

    DIST *diameter = donne_diametre_liste(m, dists);
    printf("[%s - %s] -> %d\n", diameter->start->nom, diameter->end->nom, diameter->d);

    printf("--------------------------------\n");
    printf("----------Excentricités---------\n");

    for (int i = 0; i < m->n; i++)
    {
        printf("[%s] -> %d\t", m->vertices[i].nom, excentricite(&m->vertices[i], dists, n_dists));

        if (i % 2)
        {
            printf("\n");
        }
    }

    printf("\n--------------------------------\n");
    printf("-------------Centres------------\n");

    VERTICE **centres = (VERTICE **)malloc(m->n * sizeof(VERTICE *));
    for (int i = 0; i < m->n; i++)
    {
        centres[i] = NULL;
    }

    int radius = 0;
    int n_centres = donne_centre_liste(m, dists, centres, &radius);

    for (int i = 0; i < n_centres; i++)
    {
        printf("%s\t", centres[i]->nom);
    }

    for (int i = 0; i < n_dists; i++)
    {
        free(dists[i]);
    }
    free(dists);

    printf("\n--------------------------------\n");
    printf("--------------Rayon-------------\n");

    printf("Rayon: %d\n", radius);

    printf("--------------------------------\n");
    printf("--------------Degrés------------\n");
    int *degres = (int *)calloc(m->n, sizeof(int));
    calcul_degre_liste(m, degres);
    for (int i = 0; i < m->n; i++)
    {
        printf("[%s] -> %d\t", m->vertices[i].nom, degres[i]);

        if (i % 2)
        {
            printf("\n");
        }
    }

    printf("\n--------------------------------\n");
    printf("---------Centres degrés---------\n");
    int deg_max;
    int n_centres_deg = donne_centre_degre_liste(m, centres, &deg_max);
    for (int i = 0; i < n_centres_deg; i++)
    {
        printf("%s\t", centres[i]->nom);
    }
    printf("\n");
    printf("Degré max: %d\n", deg_max);

    printf("--------------------------------\n");

    free(centres); // Vertices struct in centres are vertices from matrix so we only free the array
}