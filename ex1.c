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
    char *nom;
    int id;
} VERTICE;

typedef struct
{
    int n;
    VERTICE *vertices;
    int **graph;
} MATRIX;

typedef struct
{
    int n;
    VERTICE *vertices;
    int *sizes;
    int **graph;
} LISTE;

void display_graph_matrix(MATRIX *m)
{
    printf("%dx%d matrix\n", m->n, m->n);

    if (m->n == 0)
    {
        printf("No data\n");
        return;
    }

    printf("Sommets:");
    for (int i = 0; i < m->n; i++)
    {
        printf("[%d] %s / ", m->vertices[i].id, m->vertices[i].nom);
    }
    printf("\n");

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
    free(m->vertices);
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
    m->vertices = NULL;
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
        // Vérification de l'absence du sommet
        printf("Sommet a ajouter:%d %s\n", s.id, s.nom);
        for (int i = 0; i < m->n; i++)
        {
            if (m->vertices[i].id == s.id)
            {
                printf("Sommet deja present\n");
                return;
            }
        }

        m->vertices = (VERTICE *)realloc(m->vertices, (m->n + 1) * sizeof(VERTICE));

        m->vertices[m->n] = (VERTICE){s.nom, s.id};
        m->graph = (int **)realloc(m->graph, (m->n + 1) * sizeof(int *));
        m->graph[m->n] = (int *)malloc((m->n + 1) * sizeof(int));

        for (int i = 0; i <= m->n; i++)
        {
            m->graph[m->n][i] = 0;
            m->graph[i][m->n] = 0;
        }
        m->n++;
    }
    // display_graph_matrix(m);
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

    // Ajout des sommets
    for (int i = 0; i < vertices; i++)
    {
        fgets(buff, buff_size, stream);
        buff[strlen(buff) - 1] = '\0'; // Remove \n

        int id = atoi(strtok(buff, " "));
        char *name = strtok(NULL, " ");
        printf("%s, %d\n", name, strlen(name));
    }
    add_sommet_matrix(m, (VERTICE){"A", 0});
    add_sommet_matrix(m, (VERTICE){"B", 1});
    add_sommet_matrix(m, (VERTICE){"C", 2});
    add_sommet_matrix(m, (VERTICE){"D", 3});
    add_sommet_matrix(m, (VERTICE){"E", 4});

    printf("TOUS LES SOMMETS AJOUTES\n");
    display_graph_matrix(m);

    fgets(buff, buff_size, stream);
    buff[strlen(buff) - 1] = '\0';
    while (chars != -1)
    {
        // Récupération des arretes
        char *nameVA = strtok(buff, " ");
        char *nameVB = strtok(NULL, " ");
        nameVB[strlen(nameVB) - 1] = '\0';

        VERTICE *vA = NULL;
        VERTICE *vB = NULL;
        printf("%s-%s(%d)\n", nameVA, nameVB, m->n);
        for (int i = 0; i < m->n; i++)
        {
            printf("n:%s %s %s %d %d\n", m->vertices[i].nom, nameVA, nameVB, m->vertices[i].nom == nameVA, m->vertices[i].nom == nameVB);
            if (m->vertices[i].nom == nameVA)
            {
                printf("Trouve A\n");
                vA = &m->vertices[i];
            }
            else if (m->vertices[i].nom == nameVB)
            {
                printf("Trouve B\n");
                vB = &m->vertices[i];
            }
        }
        printf("recuperation deux sommets\n");

        printf("ajout arrete: %d - %d\n", vA->id, vB->id);
        if (vA != NULL && vB != NULL)
        {
            add_matrix(m, vA, vB);
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

    // Save vertices
    for (int i = 1; i < m->n + 1; i++)
    {
        snprintf(buff, 20, "%d", i);
        fprintf(stream, buff);
        fprintf(stream, "\n");
    }

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
    l->vertices = NULL;
    l->sizes = NULL;
    l->graph = NULL;
    return l;
}

void add_sommet_liste(LISTE *G, VERTICE *v)
{
    if (G->n == 0)
    {
        G->sizes = (int *)calloc(1, sizeof(int));
        G->graph = (int **)malloc(sizeof(int *));
        G->vertices = (VERTICE *)calloc(1, sizeof(VERTICE));
        v->id = G->n;

        G->graph[G->n] = (int *)malloc(sizeof(int));
        G->graph[G->n][0] = -1;
        G->sizes[G->n] = 0;
        G->vertices[G->n] = *v;
        G->n++;
    }
    else
    {
        v->id = G->n;
        G->graph = (int **)realloc(G->graph, (G->n + 1) * sizeof(int *));
        G->sizes = (int *)realloc(G->sizes, (G->n + 1) * sizeof(int));
        G->vertices = (VERTICE *)realloc(G->vertices, (G->n + 1) * sizeof(VERTICE));

        G->graph[G->n] = (int *)malloc(sizeof(int));
        G->graph[G->n][0] = -1;
        G->sizes[G->n] = 0;
        G->vertices[G->n] = *v;
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
                    G->graph[v1->id][m] = G->graph[v1->id - 1][m - 1];
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

LISTE *load_liste(char *nom)
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

    LISTE *G = graphe_vide_liste();

    for (int i = 0; i < vertices; i++)
    {
        chars = getline(&buff, &buff_size, stream);
        int id = atoi(strtok(buff, " "));
        char *name = strtok(NULL, " ");
        VERTICE v = {name, id};
        add_sommet_liste(G, &v);
    }

    chars = getline(&buff, &buff_size, stream);
    while (chars != -1)
    {
        // Récupération des arretes
        VERTICE firstedge = {"", atoi(strtok(buff, " "))};
        VERTICE secondedge = {"", atoi(strtok(NULL, " "))};
        if (firstedge.id >= 0 && secondedge.id >= 0)
        {
            add_liste(G, &firstedge, &secondedge);
        }
        chars = getline(&buff, &buff_size, stream);
    }
    free(buff);

    fclose(stream);
    return G;
}

/*LISTE *matrix_to_liste(MATRIX *m)
{
    LISTE *l = graphe_vide_liste();
    *l->vertices = *m->vertices;
    for (int i=0;i<m->n;i++){
        add_sommet_liste(l,&l->vertices[i]);
    }
    for (int i = 0; i < m->n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (m->graph[j][i] == 1)
            {
                add_liste(l, &l->vertices[i], &l->vertices[j]);
            }
        }
    }
    return l;
}*/

/*MATRIX *liste_to_matrix(LISTE *l)
{
    MATRIX *m = graphe_vide_matrix();
    add_sommet_matrix(m, l->n);
    int size;
    for (int i = 0; i < l->n; i++)
    {
        for (int j = 0; j < l->sizes[i]; j++)
        {
            add_matrix(m, i + 1, l->graph[i][j]);
        }
    }
    return m;
}*/

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

int inclus_aretes_matrix(MATRIX *g1, MATRIX *g2)
{
    int aretescommun = 0, aretesg2 = 0;
    char s1, s2;
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
                s1 = *g1->vertices[i].nom;
                s2 = *g1->vertices[j].nom;
                for (int k = 0; k < g2->n; k++)
                {
                    if (*g2->vertices[k].nom == s1)
                        index1 = k;
                    if (*g2->vertices[k].nom == s2)
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

int inclus_aretes_liste(LISTE *l1, LISTE *l2, int strict)
{
    int aretescommun = 0, aretesl1 = 0;
}

int main()
{
    MATRIX *m = graphe_vide_matrix();
    VERTICE verticeA = {"Valenciennes", 0};
    VERTICE verticeB = {"Lille", 1};

    /*add_sommet_matrix(m, verticeA);
    add_sommet_matrix(m, verticeB);
    display_graph_matrix(m);*/

    /*add_matrix(m, &verticeA, &verticeB);
    display_graph_matrix(m);*/

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

    MATRIX *M1 = graphe_vide_matrix();
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

    add_matrix(M2, &v1, &v2);
    add_matrix(M2, &v2, &v3);
    add_matrix(M2, &v1, &v3);

    if (inclus_aretes_matrix(M1, M2))
    {
        printf("est inclus\n");
    }
    else
        printf("non inclus\n");

    MATRIX *lm = load("d.txt");
    display_graph_matrix(lm);

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

    return 0;
}