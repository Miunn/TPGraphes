#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/struct.h"
#include "../includes/general.h"

/**
 * @brief Display a graph under the matrix representation
 * 
 * @param m The matrix to display
 * @param stream Output stream to display on, if NULL print to stdout
 */
void display_graph_matrix(MATRIX *m, FILE *stream)
{
    if (stream == NULL) {
        stream = stdout;
    }
    fprintf(stream, "%dx%d matrix\n", m->n, m->n);

    if (m->n == 0)
    {
        fprintf(stream, "No data\n");
        return;
    }

    fprintf(stream, "Sommets:");
    for (int i = 0; i < m->n; i++)
    {
        fprintf(stream, "[%d] %s / ", m->vertices[i].id, m->vertices[i].nom);
    }
    fprintf(stream, "\n");

    fprintf(stream, "    ");
    for (int i = 0; i < m->n; i++)
    {
        fprintf(stream, "%d ", m->vertices[i].id);
    }
    fprintf(stream, "\n");
    for (int i = 0; i < m->n * 2 + 4; i++)
    {
        fprintf(stream, "-");
    }
    fprintf(stream, "\n");
    for (int i = 0; i < m->n; i++)
    {
        fprintf(stream, "%d | ", m->vertices[i].id);
        for (int j = 0; j < m->n; j++)
        {
            fprintf(stream, "%d ", m->graph[i][j]);
        }
        fprintf(stream, "\n");
    }
}

/**
 * @brief Free the memory used by a matrix
 *
 * @param m Matrix structure to free
 */
void free_matrix(MATRIX *m)
{
    /*for (int i = 0; i < m->n+1; i++)
    {
        printf("free graph[%d]\n", i);
        free(m->graph[i]);
    }*/
    free(m->graph);
    free(m->vertices);
}

/**
 * @brief Initialize an empty graph under the matrix representation
 *
 * @return MATRIX* The created matrix
 */
MATRIX *graphe_vide_matrix()
{
    MATRIX *m = (MATRIX *)malloc(sizeof(MATRIX));
    m->n = 0;
    m->vertices = NULL;
    m->graph = NULL;
    return m;
}

/**
 * @brief Add a vertice to the matrix.
 *
 * @param m The graph under the matrix representation
 * @param s The new vertice
 */
void add_sommet_matrix(MATRIX *m, VERTICE s)
{
    if (m->n == 0)
    {
        m->vertices = (VERTICE *)malloc(sizeof(VERTICE));
        m->vertices[0] = s;

        m->graph = (int **)malloc(sizeof(int *));
        m->graph[0] = (int *)malloc(sizeof(int));
        m->graph[0][0] = 0;

        m->n = 1;
    }
    else
    {
        // Check if the vertice isn't already registered
        for (int i = 0; i < m->n; i++)
        {
            if (m->vertices[i].id == s.id)
            {
                return;
            }
        }

        m->vertices = (VERTICE *)realloc(m->vertices, (m->n + 2) * sizeof(VERTICE));
        m->vertices[m->n] = (VERTICE){s.nom, s.id};
        m->graph = (int **)realloc(m->graph, (m->n + 2) * sizeof(int *));   // + 2 because it's one more row with one more column
        m->graph[m->n] = (int *)malloc((m->n + 1) * sizeof(int));
        for (int i = 0; i <= m->n; i++)
        {
            m->graph[m->n][i] = 0;
            m->graph[i][m->n] = 0;
        }
        m->n++;
    }
}

/**
 * @brief Ajoute une arete entre deux sommets du graphe en utilisant la représentation matricielle
 * On passe donc a 1 la case (i, j) ainsi que la case (j, i), le graphe n'étant non orienté.
 * Si l'arete existe déjà, rien n'est modifié
 *
 * @param m La matrice du graphe
 * @param i 1er sommet de l'arete
 * @param j 2eme sommet de l'arete
 */
void add_matrix(MATRIX *m, VERTICE *i, VERTICE *j)
{
    m->graph[i->id][j->id] = 1;
    m->graph[j->id][i->id] = 1;
}

/**
 * @brief Supprime une arete entre deux sommets du graphe en utilisant la représentation matricielle.
 * Si l'arete n'existe déjà pas rien n'est modifié
 *
 * @param m La matrice du graphe
 * @param i 1er sommet de l'arete
 * @param j 2eme sommet de l'arete
 */
void supp_matrix(MATRIX *m, VERTICE *i, VERTICE *j)
{
    m->graph[i->id][j->id] = 0;
    m->graph[j->id][i->id] = 0;
}

/**
 * @brief Indique si deux sommets sont reliés par une arete en utilisant la représentation matricielle
 *
 * @param m La matrice du graphe
 * @param i 1er sommet
 * @param j 2eme sommet
 * @return int 1 si les sommets i et j sont reliés par une arete, 0 sinon
 */
int est_voisin(MATRIX *m, VERTICE *i, VERTICE *j)
{
    return m->graph[i->id][j->id];
}

int inclus_sommet_matrix(MATRIX *G1, MATRIX *G2, int strict)
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

int inclus_aretes_matrix(MATRIX *g1, MATRIX *g2)
{
    int aretescommun = 0, aretesg2 = 0;
    char *s1, *s2;
    int index1, index2;

    for (int i = 0; i < g2->n; i++)
    {
        for (int j = i; j < g2->n; j++)
        {
            if (g2->graph[i][j] == 1)
                aretesg2++;
        }
    }
    for (int i = 0; i < g1->n; i++)
    {
        for (int j = i; j < g1->n; j++)
        {
            if (g1->graph[i][j] == 1)
            {
                s1 = g1->vertices[i].nom;
                s2 = g1->vertices[j].nom;
                for (int k = 0; k < g2->n; k++)
                {
                    if (g2->vertices[k].nom == s1)
                        index1 = k;
                    if (g2->vertices[k].nom == s2)
                        index2 = k;
                }
                if (g2->graph[index1][index2] == 1)
                {
                    aretescommun++;
                    break;
                }
                else
                {
                    printf("arete pas trouvé\n");
                    return 0;
                }
            }
        }
    }
    if (aretescommun == aretesg2)
    {
        printf("même nombre d'aretes\n");
        return 0;
    }
    return 1;
}

int est_partiel_matrix(MATRIX *m1, MATRIX *m2)
{
    int segaux = 0;
    if (inclus_sommet_matrix(m1, m2, 0) && !inclus_sommet_matrix(m1, m2, 1))
        segaux = 1;
    if (segaux && inclus_aretes_matrix(m1, m2))
        return 1;
    return 0;
}

int est_sous_graphe_matrix(MATRIX *m1, MATRIX *m2)
{
    if (inclus_sommet_matrix(m1, m2, 1) && inclus_aretes_matrix(m1, m2))
    {
        return 1;
    }
    return 0;
}

VERTICE *get_vertice_by_name_matrix(MATRIX *m, char *name) {
    for (int i = 0; i < m->n; i++){
        if (strcmp(m->vertices[i].nom, name) == 0) {
            return &m->vertices[i];
        }
    }
    return NULL;
}

/**
 * @brief Renvoi 1 si m1 est un sous graphe partiel de m2
 *
 * @param m1 Premier Graphe
 * @param m2 Second Graphe
 * @return int 1 ou 0 selon le prédicat
 */
int est_sous_graphe_partiel_matrix(MATRIX *m1, MATRIX *m2)
{
    // Inclusion des sommets
    int verticesfound = 0;
    int found = 0;
    for (int i = 0; i < m1->n; i++)
    {
        VERTICE v_curr = m1->vertices[i];
        found = 0;
        for (int j = 0; j < m2->n; j++)
        {
            if (strcmp(m2->vertices[j].nom, v_curr.nom) == 0)
            {
                found = 1;
                verticesfound++;
            }
        }

        if (found == 0)
        {
            // Vertice not found => S isn't include in S'
            return 0;
        }
    }

    // We have S include in S', we now check is A is include in A'
    // We check if each edge of A is include in A
    int n_edges_m1 = 0; // To check strict inclusion
    int n_edges_m2 = 0;
    for (int i = 0; i < m1->n; i++)
    {
        VERTICE *v1 = get_vertice_by_name_matrix(m2, m1->vertices[i].nom);
        for (int j = 0; j < i + 1; j++)
        {    
            VERTICE *v2 = get_vertice_by_name_matrix(m2, m1->vertices[j].nom);
            if (m1->graph[i][j] == 1)
            {
                n_edges_m1++;
                if (m2->graph[v1->id][v2->id] != 1)
                {
                    return 0;
                }
            }
        }
    }

    // Count amount of edges in m2
    for (int i = 0; i < m2->n; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (m2->graph[i][j] == 1) {
                n_edges_m2++;
            }
        }
    }

    // Check the strict inclusion
    if (n_edges_m1 == n_edges_m2)
    {
        return 0;
    }

    return 1;
}

/**
 * return 1 if m1 clique of m2, 0 else
 */
int est_clique_matrix(MATRIX *m1, MATRIX *m2)
{
    if (est_sous_graphe_matrix(m1, m2))
    {
        for (int i = 0; i < m1->n; i++)
        {
            for (int j = i + 1; j < m1->n; j++)
            {
                if (m1->graph[i][j] != 1)
                {
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}

/**
 * return 1 if m1 stable of m2, 0 else
 */
int est_stable_matrix(MATRIX *m1, MATRIX *m2)
{
    if (est_sous_graphe_matrix(m1, m2))
    {
        for (int i = 0; i < m1->n; i++)
        {
            for (int j = i; j < m1->n; j++)
            {
                if (m1->graph[i][j] == 1)
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}

int calcul_distance_matrix(MATRIX *m, VERTICE *a, VERTICE *b, VERTICE **ban, int n_ban, int d)
{
    // Get a's neigbours
    VERTICE **neighbors = (VERTICE **)malloc(m->n * sizeof(VERTICE *));
    for (int i = 0; i < m->n; i++)
    {
        neighbors[i] = NULL;
    }
    int isBan;
    int noNeighbors = 1;
    for (int i = 0; i < m->n; i++)
    {
        if (m->graph[a->id][i] == 1 && i != a->id)
        {
            isBan = 0;
            for (int j = 0; j < n_ban; j++)
            {
                if (strcmp(ban[j]->nom, m->vertices[i].nom) == 0)
                {
                    isBan = 1;
                }
            }

            if (isBan == 0)
            {
                neighbors[i] = &m->vertices[i];
                noNeighbors = 0;
            }
        }
    }
    ban[n_ban] = a;
    n_ban++;

    int *all_dists = (int *)calloc((m->n), sizeof(int));
    for (int i = 0; i < m->n; i++)
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
                int r = calcul_distance_matrix(m, neighbors[i], b, ban, n_ban, d + 1);
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

    int min = m->n + 1; // Distance supposée impossible pour un graphe connexe
    for (int i = 0; i < m->n; i++)
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
 * @param m Graph
 * @param dists Output array of distances
 */
void calculs_distances_matrix(MATRIX *m, DIST **dists)
{
    VERTICE **ban = (VERTICE **)malloc((m->n - 1) * sizeof(VERTICE *));
    for (int i = 0; i < m->n - 1; i++)
    {
        ban[i] = NULL;
    }

    int n = 0;

    // Parcours de la matrice stritement supérieure
    for (int i = 0; i < m->n; i++)
    {
        for (int j = i + 1; j < m->n; j++)
        {
            DIST *d = (DIST *)malloc(sizeof(DIST));
            d->start = &m->vertices[i];
            d->end = &m->vertices[j];
            d->d = calcul_distance_matrix(m, &m->vertices[i], &m->vertices[j], ban, 0, 0);
            dists[n] = d;
            n++;
        }
    }
}

/**
 * @brief Compute the diameter for the graph m
 *
 * @param m The graph represented in matrix
 * @param dists Array of ((m->n * (m->n - 1)) / 2) length (amount of pairs in the graph)
 * @return int The diameter of the graph
 */
DIST *donne_diametre_matrix(MATRIX *m, DIST **dists)
{
    DIST *max = dists[0];
    for (int i = 1; i < (m->n) * (m->n - 1) / 2; i++)
    {
        if (dists[i]->d > max->d)
        {
            max = dists[i];
        }
    }
    return max;
}

/**
 * @brief Compute the amount of centres for the graph m and it's radius
 *
 * @param m The graph under matrix struct
 * @param dists Distances for each pair
 * @param centres_list Output array for centres
 * @param m_radius Output int for graph radius
 * @return int Amount of centres
 */
int donne_centre_matrix(MATRIX *m, DIST **dists, VERTICE **centres_list, int *m_radius)
{
    int n = 0;

    int n_dists = (m->n * (m->n - 1)) / 2;

    int *eccentricities = (int *)malloc(m->n * sizeof(int));
    eccentricities[0] = excentricite(&m->vertices[0], dists, n_dists);
    int min_eccentricity = eccentricities[0];
    for (int i = 1; i < m->n; i++)
    {
        eccentricities[i] = excentricite(&m->vertices[i], dists, n_dists);
        if (eccentricities[i] < min_eccentricity)
        {
            min_eccentricity = eccentricities[i];
        }
    }

    for (int i = 0; i < m->n; i++)
    {
        if (eccentricities[i] == min_eccentricity)
        {
            centres_list[n] = &m->vertices[i];
            n++;
        }
    }

    *m_radius = min_eccentricity;
    return n;
}

/**
 * @brief Compute the level of each vertice
 *
 * @param m Matrix for the graph
 * @param degs Output array for the levels (must be initialized with zeros)
 */
void calcul_degre_matrix(MATRIX *m, int *degs)
{
    for (int i = 0; i < m->n; i++)
    {
        for (int j = 0; j < m->n; j++)
        {
            if (m->graph[i][j] == 1)
            {
                degs[i]++;
            }
        }
    }
}

int donne_centre_degre_matrix(MATRIX *m, VERTICE **centres_list, int *deg_max)
{
    int n = 0;

    int n_dists = (m->n * (m->n - 1)) / 2;

    int *degs = (int *)calloc(m->n, sizeof(int));
    calcul_degre_matrix(m, degs);
    int max_deg = degs[0];
    for (int i = 1; i < m->n; i++)
    {
        if (degs[i] > max_deg)
        {
            max_deg = degs[i];
        }
    }

    for (int i = 0; i < m->n; i++)
    {
        if (degs[i] == max_deg)
        {
            centres_list[n] = &m->vertices[i];
            n++;
        }
    }

    *deg_max = max_deg;
    return n;
}