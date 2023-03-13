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

#include "../headers/struct.h"
#include "../headers/general.h"
#include "../headers/matrix.h"
#include "../headers/list.h"
#include "../headers/io.h"


int main()
{
    MATRIX *g1 = load("g1.txt");
    display_graph_matrix(g1);

    DIST **dists = (DIST **)malloc(((g1->n * (g1->n - 1)) / 2) * sizeof(DIST *));
    calculs_distances_matrix(g1, dists);

    for (int i = 0; i < ((g1->n * (g1->n - 1)) / 2); i++) {
        printf("[%s - %s] -> %d\n", dists[i]->start->nom, dists[i]->end->nom, dists[i]->d);
    }

    DIST *diameter = donne_diametre_matrix(g1, dists);
    printf("Diametre: %d (%s - %s)\n", diameter->d, diameter->start->nom, diameter->end->nom);
    printf("Excentricite de %s: %d\n", g1->vertices[0].nom, excentricite(&g1->vertices[0], dists, (g1->n * (g1->n - 1)) / 2));

    VERTICE **centres = (VERTICE **) malloc(g1->n * sizeof(VERTICE *));
    for (int i = 0; i < g1->n; i++) {
        centres[i] = NULL;
    }
    int radius = 0;
    int n_centres = donne_centre_matrix(g1, dists, centres, &radius);

    for (int i = 0; i < n_centres; i++) {
        printf("Centre: %s\n", centres[i]->nom);
    }

    printf("Rayon: %d\n", radius);

    int *degres = (int *) calloc(g1->n, sizeof(int));
    calcul_degre_matrix(g1, degres);
    for (int i = 0; i < g1->n; i++) {
        printf("Degre de %s: %d\n", g1->vertices[i].nom, degres[i]);
    }

    int deg_max;
    int n_centres_deg = donne_centre_degre_matrix(g1, centres, &deg_max);
    printf("Deg max: %d\n", deg_max);
    for (int i = 0; i < n_centres_deg; i++) {
        printf("CentreDeg: %s\n", centres[i]->nom);
    }

    /*add_sommet_matrix(m, verticeA);
    add_sommet_matrix(m, verticeB);
    display_graph_matrix(m);*/

    /*add_matrix(m, &verticeA, &verticeB);
    display_graph_matri%x(m);*/

    // save(m, "d2.txt");

    /*LISTE *l = graphe_vide_liste();

    add_sommet_liste(l, &verticeA);
    display_graph_liste(l);
    add_sommet_liste(l, &verticeB);
    display_graph_liste(l);
    add_liste(l, &verticeA, &verticeB);
    display_graph_liste(l);
    supp_liste(l, &verticeA,&verticeB);
    display_graph_liste(l);*/

    /*MATRIX *M1 = graphe_vide_matrix();
    MATRIX *M2 = graphe_vide_matrix();

    VERTICE v1 = {"a", 0};
    VERTICE v2 = {"b", 1};
    VERTICE v3 = {"c", 2};

    add_sommet_matrix(M1, v1);
    add_sommet_matrix(M1, v2);
    add_sommet_matrix(M1, v3);

    add_sommet_matrix(M2, v1);
    add_sommet_matrix(M2, v2);
    add_sommet_matrix(M2, v3);

    add_matrix(M1, &v1, &v2);
    add_matrix(M1, &v2, &v3);
    add_matrix(M1, &v1, &v3);

    add_matrix(M2, &v1, &v2);
    add_matrix(M2, &v2, &v3);

    if (inclus_aretes_matrix(M1, M2))
    {
        printf("est inclus\n");
    }
    else
        printf("non inclus\n");
    */

    /*LISTE *l1 = graphe_vide_liste();
    LISTE *l2 = graphe_vide_liste();

    VERTICE v1 = {"a", 0};
    VERTICE v2 = {"b", 1};
    VERTICE v3 = {"c", 2};

    add_sommet_liste(l1, &v1);
    add_sommet_liste(l1, &v2);
    add_sommet_liste(l1, &v3);

    add_sommet_liste(l2, &v1);
    add_sommet_liste(l2, &v2);
    add_sommet_liste(l2, &v3);

    add_liste(l1, &v1, &v2);
    printf("1\n");
    add_liste(l1, &v2, &v3);
    printf("2\n");
    add_liste(l1, &v1, &v3);
    printf("links added for l1\n");

    add_liste(l2, &v1, &v2);
    printf("3\n");
    add_liste(l2, &v2, &v3);
    printf("TOUT AJOUTE\n");

    for (int i = 0; i < l2->n; i++)
    {
        printf("nom sommet %d : %s\n", i, l2->vertices[i]);
    }
    if (inclus_aretes_liste(l1, l2))
    {
        printf("est inclus\n");
    }
    else
        printf("non inclus\n");*/

    /*MATRIX *lm = load("g1.txt");
    display_graph_matrix(lm);

    LISTE *l = load_liste("g1.txt");
    display_graph_liste(l);*/

    /*LISTE *l = matrix_to_liste(lm);
    display_graph_liste(l);*/
    /*MATRIX *verif = load("d3.txt");
    display_graph_matrix(verif);*/

    /*LISTE *lverif = load_liste("ex1_text.txt");
    display_graph_liste(lverif);

    MATRIX *m = liste_to_matrix(lverif);
    display_graph_matrix(m);*/

    // free_matrix(m);
    /*free_matrix(lm);
    free_liste(l);*/
    // free_liste(l);

    /*MATRIX *g1 = load("g1.txt");
    MATRIX *g2 = load("g2.txt");
    MATRIX *g3 = load("g3.txt");

    printf("%d %d\n", est_sous_graphe_partiel_matrix(g2, g1), est_sous_graphe_partiel_matrix(g3, g1));*/

    // calcul_distance_matrix(g1, &g1->vertices[0], &g1->vertices[1], ban, 0);
    //  free(dists);
    return 0;
}