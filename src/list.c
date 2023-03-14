#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../includes/struct.h"
#include "../includes/general.h"

void display_graph_liste(LISTE *l)
{
    for (int i = 0; i < l->n; i++)
    {
        printf("[%d  %s] -> [", l->vertices[i].id, l->vertices[i].nom);
        for (int j = 0; j < l->sizes[i]; j++)
        {
            if (l->graph[i][j] != -1)
            {
                printf("%d ", l->graph[i][j]);
            }
        }
        printf("]\n");
    }
    printf("\n");
}

/**
 * @brief Libère la mémoire occupée par la structure de listes représentant un graphe
 *
 * @param l La structure de listes à libérer
 */
void free_liste(LISTE *l)
{
    for (int i = 0; i < l->n; i++)
    {
        free(l->graph[i]);
    }
    free(l->graph);
    free(l->sizes);
}

LISTE *graphe_vide_liste()
{
    LISTE *l = (LISTE *)malloc(sizeof(LISTE));
    l->n = 0;
    l->vertices = NULL;
    l->sizes = NULL;
    l->graph = NULL;
    return l;
}

void add_sommet_liste(LISTE *G, VERTICE v)
{
    if (G->n == 0)
    {
        G->sizes = (int *)calloc(1, sizeof(int));
        G->graph = (int **)malloc(sizeof(int *));
        G->vertices = (VERTICE *)calloc(1, sizeof(VERTICE));

        G->graph[G->n] = (int *)malloc(sizeof(int));
        G->graph[G->n][0] = -1;
        G->sizes[G->n] = 0;
        G->vertices[G->n] = v;
        G->n++;
    }
    else
    {
        G->graph = (int **)realloc(G->graph, (G->n + 1) * sizeof(int *));
        G->sizes = (int *)realloc(G->sizes, (G->n + 1) * sizeof(int));
        G->vertices = (VERTICE *)realloc(G->vertices, (G->n + 1) * sizeof(VERTICE));

        G->graph[G->n] = (int *)malloc(sizeof(int));
        G->graph[G->n][0] = -1;
        G->sizes[G->n] = 0;
        G->vertices[G->n] = (VERTICE){v.nom, v.id};
        G->n++;
    }
}

void add_liste(LISTE *G, VERTICE *v1, VERTICE *v2)
{
    int taillei = G->sizes[v1->id];
    int taillej = G->sizes[v2->id];

    for (int k = 0; k < taillei; k++)
    {
        if (G->graph[v1->id][k] == v2->id)
        {
            printf("existe déjà");
            return;
        }
    }

    G->graph[v1->id] = (int *)realloc(G->graph[v1->id], (taillei + 1) * sizeof(int));

    if (G->graph[v1->id][0] == -1)
    {
        G->graph[v1->id][0] = v2->id;
        G->sizes[v1->id] = taillei + 1;
    }
    else
    {
        for (int l = 0; l < taillei + 1; l++)
        {

            if (G->graph[v1->id][l] <= v2->id)
            {

                for (int m = taillei; m > l; m--)
                {
                    G->graph[v1->id][m] = G->graph[v1->id][m - 1];
                }
                G->graph[v1->id][l] = v2->id;
                G->sizes[v1->id] = taillei + 1;
                break;
            }
        }
    }

    if (v1->id != v2->id)
    {
        G->graph[v2->id] = (int *)realloc(G->graph[v2->id], (taillej + 1) * sizeof(int));
        if (G->graph[v2->id][0] == -1)
        {

            G->graph[v2->id][0] = v1->id;
            G->sizes[v2->id] = taillej + 1;
        }
        else
        {
            for (int l = 0; l < taillej + 1; l++)
            {
                if (G->graph[v2->id][l] <= v2->id)
                {

                    for (int m = taillej; m > l; m--)
                    {
                        G->graph[v2->id][m] = G->graph[v2->id][m - 1];
                    }
                    G->graph[v2->id][l] = v1->id;
                    G->sizes[v2->id] = taillej + 1;
                    break;
                }
            }
        }
    }
}

void supp_liste(LISTE *G, VERTICE *v1, VERTICE *v2)
{
    int taillei = G->sizes[v1->id];
    int taillej = G->sizes[v2->id];

    for (int k = 0; k < taillei; k++)
    {
        if (G->graph[v1->id][k] == v2->id)
        {
            for (int l = k; l < taillei - 1; l++)
            {
                G->graph[v1->id][k] = G->graph[v1->id][k + 1];
            }
            G->graph[v1->id] = (int *)realloc(G->graph[v1->id], (taillei - 1) * sizeof(int));
            G->sizes[v1->id]--;
            break;
        }
    }

    for (int k = 0; k < taillej; k++)
    {
        if (G->graph[v2->id][k] == v1->id)
        {
            for (int l = k; l < taillej - 1; l++)
            {
                G->graph[v2->id][k] = G->graph[v2->id - 1][k + 1];
            }
            G->graph[v2->id] = (int *)realloc(G->graph[v2->id], (taillej - 1) * sizeof(int));
            G->sizes[v2->id]--;
            break;
        }
    }
}

int est_voisin_liste(LISTE *G, int i, int j)
{
    int taillei = G->sizes[i - 1];

    for (int k = 0; k < taillei; k++)
    {
        if (G->graph[i - 1][k] == j)
        {
            return 1;
        }
    }
    return 0;
}

int inclus_sommet_liste(LISTE *G1, LISTE *G2, int strict)
{
    int nbsommets = 0;

    for (int i = 0; i < G1->n; i++)
    {
        for (int j = 0; j < G2->n; j++)
        {
            if (G1->vertices[i].nom == G2->vertices[j].nom)
            {
                nbsommets++;
                break;
            }
            if (j == G2->n - 1)
            {
                return 0;
            }
        }
    }

    if (nbsommets == G2->n && strict)
    {
        return 0;
    }
    return 1;
}

int inclus_aretes_liste(LISTE *l1, LISTE *l2)
{
    int aretescommun = 0, aretesl2 = 0;
    char *s1, *s2;
    int index1 = -1, index2 = -1;

    for (int i = 0; i < l2->n; i++)
    {
        for (int j = 0; j < l2->sizes[i]; j++)
        {
            aretesl2++;
        }
    }
    aretesl2 = aretesl2 / 2;

    for (int i = 0; i < l1->n; i++)
    {
        for (int j = 0; j < l1->sizes[i]; j++)
        {
            s1 = l1->vertices[i].nom;
            s2 = l1->vertices[l1->graph[i][j]].nom;
            for (int k = 0; k < l2->n; k++)
            {
                if (!strcmp(l2->vertices[k].nom, s1))
                {
                    index1 = k;
                }
                if (!strcmp(l2->vertices[k].nom, s2))
                {
                    index2 = k;
                }
            }
            if (index1 == -1)
            {
                printf("Sommet %s non trouvé dans le deuxième graphe\n", s1);
                return 0;
            }
            else if (index2 == -1)
            {
                printf("Sommet %s non trouvé dans le deuxième graphe\n", s2);
                return 0;
            }
            for (int g = 0; g < l2->sizes[index1]; g++)
            {
                if (l2->graph[index1][g] == index2)
                {
                    aretescommun++;
                    break;
                }
                else if (g == l2->sizes[index1] - 1)
                {
                    printf("connection entre %d et %d non trouvée\n", index1, index2);
                    return 0;
                }
            }
        }
    }
    if (aretescommun == aretesl2)
    {
        printf("Ensembles d'arêtes de l1 et l2 égaux\n");
        return 0;
    }
    return 1;
}

int est_partiel_liste(LISTE *m1, LISTE *m2)
{
    int segaux = 0;
    if (inclus_sommet_liste(m1, m2, 0) && !inclus_sommet_liste(m1, m2, 1))
        segaux = 1;
    if (segaux && inclus_aretes_liste(m1, m2))
        return 1;
    return 0;
}

int est_sous_graphe_liste(LISTE *l1, LISTE *l2)
{
    if (inclus_sommet_liste(l1, l2, 1) && inclus_aretes_liste(l1, l2))
    {
        return 1;
    }
    return 0;
}

/**
 * return 1 if l1 clique of l2, 0 else
 */
int est_clique_liste(LISTE *l1, LISTE *l2)
{
    if (est_sous_graphe_liste(l1, l2))
    {
        for (int i = 0; i < l1->n; i++)
        {
            for (int j = 0; j < l1->n; j++)
            {
                if (i != j)
                {
                    for (int k = 0; k < l1->sizes[i]; k++)
                    {
                        if (l1->graph[i][k] == j)
                        {
                            break;
                        }
                        else if (k == l1->sizes[i] - 1)
                        {
                            return 0;
                        }
                    }
                }
            }
        }
        return 1;
    }
    return 0;
}

int est_stable_liste(LISTE *l1, LISTE *l2)
{
    if (est_sous_graphe_liste(l1, l2))
    {
        for (int i = 0; i < l1->n; i++)
        {
            if (l1->graph[i][0] != -1)
                return 0;
        }
        return 1;
    }
    return 0;
}

int calcul_distance_liste(LISTE *l, VERTICE *a, VERTICE *b, VERTICE **ban, int n_ban, int d)
{
    // Get a's neigbours
    VERTICE **neighbors = (VERTICE **)malloc(l->n * sizeof(VERTICE *));
    for (int i = 0; i < l->n; i++)
    {
        neighbors[i] = NULL;
    }
    int isBan;
    int noNeighbors = 1;
    for (int i = 0; i < l->sizes[a->id]; i++)
    {
        if (l->graph[a->id][i] != a->id)
        {
            isBan = 0;
            for (int j = 0; j < n_ban; j++)
            {
                if (strcmp(ban[j]->nom, l->vertices[l->graph[a->id][i]].nom) == 0)
                {
                    isBan = 1;
                }
            }

            if (isBan == 0)
            {
                neighbors[l->graph[a->id][i]] = &l->vertices[l->graph[a->id][i]];
                noNeighbors = 0;
            }
        }
    }
    ban[n_ban] = a;
    n_ban++;

    int *all_dists = (int *)calloc((l->n), sizeof(int));
    for (int i = 0; i < l->n; i++)
    {
        if (neighbors[i] != NULL)
        {
            if (strcmp(neighbors[i]->nom, b->nom) == 0)
            {
                free(neighbors);
                return d + 1;
            }
            else
            {
                int r = calcul_distance_matrix(l, neighbors[i], b, ban, n_ban, d + 1);
                if (r > 0)
                {
                    all_dists[i] = r;
                }
            }
        }
    }

    if (noNeighbors == 1)
    {
        return -1;
    }

    int min = l->n + 1; // Distance supposée impossible pour un graphe connexe
    for (int i = 0; i < l->n; i++)
    {
        if (all_dists[i] < min && all_dists[i] > 0)
        {
            min = all_dists[i];
        }
    }
    return min;
}

/**
 * @brief Compute distances between each vertices
 *
 * @param l Graph
 * @param dists Output array of distances
 */
void calculs_distances_liste(LISTE *l, DIST **dists)
{
    VERTICE **ban = (VERTICE **)malloc((l->n - 1) * sizeof(VERTICE *));
    for (int i = 0; i < l->n - 1; i++)
    {
        ban[i] = NULL;
    }

    int n = 0;

    // Parcours de la matrice stritement supérieure
    for (int i = 0; i < l->n; i++)
    {
        for (int j = i + 1; j < l->n; j++)
        {
            DIST *d = (DIST *)malloc(sizeof(DIST));
            d->start = &l->vertices[i];
            d->end = &l->vertices[j];
            d->d = calcul_distance_matrix(l, &l->vertices[i], &l->vertices[j], ban, 0, 0);
            dists[n] = d;
            n++;
        }
    }
}

/**
 * @brief Compute the diameter for the graph l
 *
 * @param l The graph represented in matrix
 * @param dists Array of ((l->n * (l->n - 1)) / 2) length (amount of pairs in the graph)
 * @return int The diameter of the graph
 */
DIST *donne_diametre_liste(LISTE *l, DIST **dists)
{
    DIST *max = dists[0];
    for (int i = 1; i < (l->n) * (l->n - 1) / 2; i++)
    {
        if (dists[i]->d > max->d)
        {
            max = dists[i];
        }
    }
    return max;
}

/**
 * @brief Compute the amount of centres for the graph l and it's radius
 *
 * @param l The graph under list struct
 * @param dists Distances for each pair
 * @param centres_list Output array for centres
 * @param m_radius Output int for graph radius
 * @return int Amount of centres
 */
int donne_centre_liste(LISTE *l, DIST **dists, VERTICE **centres_list, int *m_radius)
{
    int n = 0;

    int n_dists = (l->n * (l->n - 1)) / 2;

    int *eccentricities = (int *)malloc(l->n * sizeof(int));
    eccentricities[0] = excentricite(&l->vertices[0], dists, n_dists);
    int min_eccentricity = eccentricities[0];
    for (int i = 1; i < l->n; i++)
    {
        eccentricities[i] = excentricite(&l->vertices[i], dists, n_dists);
        if (eccentricities[i] < min_eccentricity)
        {
            min_eccentricity = eccentricities[i];
        }
    }

    for (int i = 0; i < l->n; i++)
    {
        if (eccentricities[i] == min_eccentricity)
        {
            centres_list[n] = &l->vertices[i];
            n++;
        }
    }

    *m_radius = min_eccentricity;
    return n;
}

/**
 * @brief Compute the level of each vertice
 *
 * @param l List for the graph
 * @param degs Output array for the levels (must be initialized with zeros)
 */
void calcul_degre_liste(LISTE *l, int *degs)
{
    for (int i = 0; i < l->n; i++)
    {
        degs[i] = l->sizes[i];
    }
}

/**
 * @brief Compute the amount of centres for the graph l (considering the maximum degree as a criterion) and it's radius
 *
 * @param l The graph under list struct
 * @param centres_list Output array for centres
 * @param deg_max Output int for graph max degree
 * @return int Amount of centres
 */
int donne_centre_degre_liste(LISTE *l, VERTICE **centres_list, int *deg_max)
{
    int n = 0;

    int n_dists = (l->n * (l->n - 1)) / 2;

    int *degs = (int *)calloc(l->n, sizeof(int));
    calcul_degre_matrix(l, degs);
    int max_deg = degs[0];
    for (int i = 1; i < l->n; i++)
    {
        if (degs[i] > max_deg)
        {
            max_deg = degs[i];
        }
    }

    for (int i = 0; i < l->n; i++)
    {
        if (degs[i] == max_deg)
        {
            centres_list[n] = &l->vertices[i];
            n++;
        }
    }

    *deg_max = max_deg;
    return n;
}