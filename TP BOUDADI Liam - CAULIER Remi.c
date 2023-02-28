/**
 * @file TP - Graphes BOUDADI Liam - CAULIER Remi.c
 * @author BOUDADI Liam & CAULIER Rémi
 * @brief 1er fichier de l'avancement du TP
 * @version 1.0
 * @date 2023-02-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int n;
    int **graph;
} MATRIX;

typedef struct
{
    int n;
    int *sizes;
    int **graph;
} LISTE;

/**
 * @brief Libère la mémoire occupée par la structure de matrice représentant un graphe
 *
 * @param m La structure de matrice à libérer
 */
void free_matrix(MATRIX *m)
{
    for (int i = 0; i < m->n; i++)
    {
        free(m->graph[i]);
    }
    free(m->graph);
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

/**
 * @brief Initialise un graphe vide sans sommet ni arete
 *
 * @return MATRIX* La matrice créée
 */
MATRIX *graphe_vide_matrix()
{
    MATRIX *m = (MATRIX *)malloc(sizeof(MATRIX));
    m->n = 0;

    m->graph = NULL;
    return m;
}

/**
 * @brief Ajoute un sommet à la matrice. Si le sommet est discontinu pr rapport à la taille de la matrice
 * (si on essaye d'ajouter le sommet 5 alors que la matrice contient les sommets 1, 2 et 3) on ajoute le(s) sommet(s) manquant(s)
 *
 * @param m La matrice à modifer
 * @param s L'identifiant du sommet à ajouter
 */
void add_sommet_matrix(MATRIX *m, int s)
{
    if (m->n == 0)
    {
        m->graph = (int **)malloc(s * sizeof(int *));

        for (int i = 0; i < s; i++)
        {
            m->graph[i] = (int *)malloc(s * sizeof(int));
            for (int j = 0; j < s; j++)
            {
                m->graph[i][j] = 0;
            }
        }
        m->n = s;
    }
    else if (s > m->n)
    {
        m->graph = (int **)realloc(m->graph, s * sizeof(int *));
        m->n = s;
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
void add_matrix(MATRIX *m, int i, int j)
{
    m->graph[i - 1][j - 1] = 1;
    m->graph[j - 1][i - 1] = 1;
}

/**
 * @brief Supprime une arete entre deux sommets du graphe en utilisant la représentation matricielle.
 * Si l'arete n'existe déjà pas rien n'est modifié
 *
 * @param m La matrice du graphe
 * @param i 1er sommet de l'arete
 * @param j 2eme sommet de l'arete
 */
void supp_matrix(MATRIX *m, int i, int j)
{
    m->graph[i - 1][j - 1] = 0;
    m->graph[j - 1][i - 1] = 0;
}

/**
 * @brief Indique si deux sommets sont reliés par une arete en utilisant la représentation matricielle
 *
 * @param m La matrice du graphe
 * @param i 1er sommet
 * @param j 2eme sommet
 * @return int 1 si les sommets i et j sont reliés par une arete, 0 sinon
 */
int est_voisin(MATRIX *m, int i, int j)
{
    return m->graph[i][j];
}

/**
 * @brief Load a data file representing a graph based on this structure:
 * NV
 * V00 V01 ... V0n
 * V10 V11 ... V1n
 * .
 * .
 * Vn0 Vn1 ... Vnn
 *
 * On the first line the number of vertices
 * On NV/2 lines the edges for the current vertex (0 if no edges)
 *
 * @param nom The path for the file
 * @return MATRIX*
 */
MATRIX *load(char *nom)
{
    FILE *stream = fopen(nom, "r");

    if (stream == NULL)
    {
        fprintf(stderr, "[ERROR] Can't open %s. Returned error:%s", nom, ferror(stream));
        return NULL;
    }

    char *buff = NULL;
    size_t buff_size = 255;
    size_t chars;

    chars = getline(&buff, &buff_size, stream);
    int vertices = atoi(buff);
    if (vertices <= 0)
    {
        fprintf(stderr, "[ERROR] Invalid data file. Number of vertices isn't a valid number.");
        return NULL;
    }

    MATRIX *m = graphe_vide_matrix();
    add_sommet_matrix(m, vertices);
    for (int i = 0; i < vertices; i++)
    {
        // Ignoring n lines
        getline(&buff, &buff_size, stream);
    }

    chars = getline(&buff, &buff_size, stream);
    while(chars != -1)
    {
        // Récupération des arretes
        int firstedge = atoi(strtok(buff, " "));
        int secondedge = atoi(strtok(NULL, " "));
        if (firstedge > 0 && secondedge > 0)
        {
            add_matrix(m, firstedge, secondedge);
        }
        chars = getline(&buff, &buff_size, stream);
    }
    free(buff);

    fclose(stream);
    return m;
}

/**
 * @brief Sauvegarde le graphe représenté par la matrice dans un fichier en suivant la même structure de données que la fonction load
 *
 * @param m La matrice représentant le graphe à sauvegarder
 */
void save(MATRIX *m, char *nom)
{
    // Le graphe étant non orienté la matrice de représentation est symétrique
    // Ainsi pour connaitre les aretes un parcours de la partie supérieure ou inférieure de la matrice est suffisant

    FILE *stream = fopen(nom, "w");
    char buff[20];
    snprintf(buff, 20, "%d", m->n);
    fprintf(stream, buff);
    fprintf(stream, "\n");

    int e;
    char line[40] = "";
    for (int i = 0; i < m->n; i++)
    {
        e = 0;
        for (int j = 0; j < i + 1; j++)
        {
            if (m->graph[j][i] == 1)
            {
                snprintf(line, 40, "%d", j + 1);
                strcat(line, " ");
                snprintf(buff, 20, "%d", i + 1);
                strcat(line, buff);
                fprintf(stream, line);
                fprintf(stream, "\n");
            }
        }
    }

    fclose(stream);
}

LISTE *graphe_vide_liste()
{
    LISTE *l = (LISTE *)malloc(sizeof(LISTE));
    l->n = 0;
    l->sizes = NULL;
    l->graph = NULL;
    return l;
}

void add_sommet_liste(LISTE *G, int i)
{
    if (G->n == 0)
    {
        G->sizes = (int *)calloc(i, sizeof(int));
        G->graph = (int **)malloc(i * sizeof(int *));

        for (int j = 0; j < i; j++)
        {
            G->graph[j] = (int *)malloc(sizeof(int));
        }
        G->n = i;
    }
    if (i > G->n)
    {
        G->n = i;
        G->graph = (int **)realloc(G->graph, i * sizeof(int *));
        G->sizes = (int *)realloc(G->sizes, i * sizeof(int));
        // G->graph[i-1] = (int *) malloc(sizeof(int));
    }
}

void add_liste(LISTE *G, int i, int j)
{
    int taillei = G->sizes[i - 1];
    int taillej = G->sizes[j - 1];

    for (int k = 0; k < taillei; k++)
    {
        if (G->graph[i - 1][k] == j)
        {
            return;
        }
    }

    G->graph[i - 1] = (int *)realloc(G->graph[i - 1], (taillei + 1) * sizeof(int));
    G->graph[i - 1][taillei] = j;
    G->sizes[i - 1] = taillei + 1;

    G->graph[j - 1] = (int *)realloc(G->graph[j - 1], (taillej + 1) * sizeof(int));
    G->graph[j - 1][taillej] = i;
    G->sizes[j - 1] = taillej + 1;
}

void supp_liste(LISTE *G, int i, int j)
{
    int taillei = G->sizes[i - 1];
    int taillej = G->sizes[j - 1];

    for (int k = 0; k < taillei; k++)
    {
        if (G->graph[i - 1][k] == j)
        {
            for (int l = k; l < taillei - 1; l++)
            {
                G->graph[i - 1][k] = G->graph[i - 1][k + 1];
            }
            G->graph[i - 1] = (int *)realloc(G->graph[i - 1], (taillei - 1) * sizeof(int));
            G->sizes[i - 1]--;
            break;
        }
    }

    for (int k = 0; k < taillej; k++)
    {
        if (G->graph[j - 1][k] == i)
        {
            for (int l = k; l < taillej - 1; l++)
            {
                G->graph[j - 1][k] = G->graph[j - 1][k + 1];
            }
            G->graph[j - 1] = (int *)realloc(G->graph[j - 1], (taillej - 1) * sizeof(int));
            G->sizes[j - 1]--;
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

void display_graph_matrix(MATRIX *m)
{
    printf("%dx%d matrix\n", m->n, m->n);
    printf("    ");
    for (int i = 0; i < m->n; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < m->n * 2 + 4; i++)
    {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < m->n; i++)
    {
        printf("%d | ", i + 1);
        for (int j = 0; j < m->n; j++)
        {
            printf("%d ", m->graph[i][j]);
        }
        printf("\n");
    }
}

void display_graph_liste(LISTE *l)
{
    for (int i = 0; i < l->n; i++)
    {
        printf("%d -> [", i + 1);
        for (int j = 0; j < l->sizes[i]; j++)
        {
            if (l->graph[i][j] != 0)
            {
                printf("%d ", l->graph[i][j]);
            }
        }
        printf("]\n");
    }
    printf("\n");
}

LISTE *load_liste(char *nom)
{
    FILE *stream = fopen(nom, "r");

    if (stream == NULL)
    {
        fprintf(stderr, "[ERROR] Can't open %s. Returned error:%s", nom, ferror(stream));
        return NULL;
    }

    char buff[255];
    char *line = fgets(buff, 255, stream);
    char *v = strtok(line, " ");
    char *e = strtok(NULL, " ");
    if (v == NULL || e == NULL)
    {
        fprintf(stderr, "[ERROR] Invalid data file. The data isn't structured correctly in the file (Can't read number of vertices and edges).");
        return NULL;
    }

    int vertices = atoi(v);
    int edges = atoi(e);

    int buffsize = vertices * vertices - 2 * strlen(v);

    LISTE *G = graphe_vide_liste();
    add_sommet_liste(G, vertices);
    for (int i = 0; i < edges; i++)
    {
        char buff[buffsize];
        line = fgets(buff, buffsize, stream);

        // Récupération des arretes
        char *edgechar = strtok(line, " ");
        while (edgechar != NULL)
        {
            int edge = atoi(edgechar);
            add_liste(G, i, edge);
            edgechar = strtok(NULL, " ");
        }
    }
    return G;
}

int main()
{
    /*MATRIX *m = graphe_vide_matrix();
    add_sommet_matrix(m, 4);
    add_matrix(m, 1, 2);
    display_graph_matrix(m);
    save(m, "d2.txt");*/
    /*LISTE *l = graphe_vide_liste();
    add_sommet_liste(l, 2);
    add_liste(l,1,2);
    add_liste(l, 1, 1);
    display_graph_liste(l);
    supp_liste(l,1,2);
    display_graph_liste(l);*/

    MATRIX *lm = load("d3.txt");
    display_graph_matrix(lm);
    //save(lm, "d3.txt");

    /*MATRIX *verif = load("d3.txt");
    display_graph_matrix(verif);*/

    // free_matrix(m);
    free_matrix(lm);
    // free_liste(l);
    return 0;
}