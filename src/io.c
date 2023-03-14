#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/struct.h"
#include "../includes/matrix.h"
#include "../includes/list.h"

/**
 * @brief Load a data file representing a graph based on this structure:
 * NV
 * id0 V0
 * id1 V1
 * .
 * .
 * idN VN
 *
 * V1 V2
 * .
 * .
 * VN VM
 * 
 * On the first line the number of vertices
 * On N lines the id followed by the vertice's name
 * On M lines the edges described by the name of the two vertices
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

    // Get number of vertices
    chars = getline(&buff, &buff_size, stream);
    int vertices = atoi(buff);
    if (vertices <= 0)
    {
        fprintf(stderr, "[ERROR] Invalid data file. Number of vertices isn't a valid number.");
        return NULL;
    }

    MATRIX *m = graphe_vide_matrix();
    int id;
    // Build and add vertices to the matrix
    for (int i = 0; i < vertices; i++)
    {
        getline(&buff, &buff_size, stream); // Get the line

        // Retreive the id length from char 0 to the next space (' ') char
        int idLen = 0;
        for (int i = 0; i < 100; i++)
        {
            if (buff[i] == ' ')
            {
                break;
            }
            else
            {
                idLen++;
            }
        }

        // Read the id based on the length compute above
        char *strId = (char *)malloc((idLen + 1) * sizeof(char));
        for (int i = 0; i < idLen; i++)
        {
            strId[i] = buff[i];
        }
        strId[idLen] = '\0';    // Add the EOT char

        // Retreive the vertice's name length from space to the next new line feed ('\n')
        int nameLen = 0;
        for (int i = idLen + 1; i < 100; i++)
        {
            if (buff[i] == '\n')
            {
                break;
            }
            else
            {
                nameLen++;
            }
        }

        // Read the name based on the length compute above
        char *name = (char *)malloc((nameLen + 1) * sizeof(char));
        for (int i = 0; i < nameLen; i++)
        {
            name[i] = buff[idLen + i + 1];
        }
        name[nameLen] = '\0';   // Add the end of text char
        id = atoi(strId);       // Convert id in integer
        add_sommet_matrix(m, (VERTICE){name, id});  // Create the vertice read and add it to the matrix
    }

    // Read edges
    fgets(buff, buff_size, stream);     // Read the line
    while (chars != -1)
    {
        // Get the first name's length
        int nameALen = 0;
        for (int i = 0; i < 100; i++)
        {
            if (buff[i] == ' ')
            {
                break;
            }
            else
            {
                nameALen++;
            }
        }

        // Read the first name based on the length read above
        char *nameVA = malloc((nameALen + 1) * sizeof(char));
        for (int i = 0; i < nameALen; i++)
        {
            nameVA[i] = buff[i];
        }
        nameVA[nameALen] = '\0';

        // Get the second name's length
        int nameBLen = 0;
        for (int i = nameALen + 1; i < 100; i++)
        {
            if (buff[i] == '\n')
            {
                break;
            }
            else
            {
                nameBLen++;
            }
        }

        // Read the second name based on the length read above
        char *nameVB = malloc((nameBLen + 1) * sizeof(char));
        for (int i = 0; i < nameBLen; i++)
        {
            nameVB[i] = buff[nameALen + i + 1];
        }
        nameVB[nameBLen] = '\0';

        // Fetch matrix vertices' for the current edge
        VERTICE *vA = NULL;
        VERTICE *vB = NULL;
        for (int i = 0; i < m->n; i++)
        {
            // Names comparison
            if (strcmp(m->vertices[i].nom, nameVA) == 0)
            {
                vA = &m->vertices[i];       // Found it, save in vertice A
            }
            else if (strcmp(m->vertices[i].nom, nameVB) == 0)
            {
                vB = &m->vertices[i];       // Found it, save in vertice B
            }
        }
        if (vA != NULL && vB != NULL)
        {
            add_matrix(m, vA, vB);  // Add the edge
        }
        chars = getline(&buff, &buff_size, stream);     // Get the new line
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
    fprintf(stream, "%d\n", m->n);

    // Save vertices
    for (int i = 0; i < m->n; i++)
    {
        fprintf(stream, "%d %s\n", m->vertices[i].id, m->vertices[i].nom);
    }

    // Save edges (only once by going though the superior part of the matrix)
    for (int i = 0; i < m->n; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            // If an edge is present, write it in the file
            if (m->graph[j][i] == 1)
            {
                fprintf(stream, "%s %s\n", m->vertices[i].nom, m->vertices[j].nom);
            }
        }
    }

    fclose(stream);
}

/**
 * @brief Load a date file representing a graph (cf load function for the exact file format)
 * 
 * @param nom Path to the file to load
 * @return LISTE* List representation for the graph
 */
LISTE *load_liste(char *nom)
{
    // Documentation is the same as load()

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

    LISTE *m = graphe_vide_liste();
    int id;
    // Ajout des sommets
    for (int i = 0; i < vertices; i++)
    {
        getline(&buff, &buff_size, stream);

        int idLen = 0;
        for (int i = 0; i < 100; i++)
        {
            if (buff[i] == ' ')
            {
                break;
            }
            else
            {
                idLen++;
            }
        }

        char *strId = (char *)malloc((idLen + 1) * sizeof(char));
        for (int i = 0; i < idLen; i++)
        {
            strId[i] = buff[i];
        }
        strId[idLen] = '\0';
        int nameLen = 0;
        for (int i = idLen + 1; i < 100; i++)
        {
            if (buff[i] == '\n')
            {
                break;
            }
            else
            {
                nameLen++;
            }
        }

        char *name = (char *)malloc((nameLen + 1) * sizeof(char));
        for (int i = 0; i < nameLen; i++)
        {
            name[i] = buff[idLen + i + 1];
        }
        name[nameLen] = '\0'; // getline leaves a carriage return
        id = atoi(strId);
        add_sommet_liste(m, (VERTICE){name, id});
    }

    fgets(buff, buff_size, stream);
    while (chars != -1)
    {
        // Récupération des arretes
        int nameALen = 0;
        for (int i = 0; i < 100; i++)
        {
            if (buff[i] == ' ')
            {
                break;
            }
            else
            {
                nameALen++;
            }
        }

        char *nameVA = malloc((nameALen + 1) * sizeof(char));
        for (int i = 0; i < nameALen; i++)
        {
            nameVA[i] = buff[i];
        }
        nameVA[nameALen] = '\0';

        int nameBLen = 0;
        for (int i = nameALen + 1; i < 100; i++)
        {
            if (buff[i] == '\n')
            {
                break;
            }
            else
            {
                nameBLen++;
            }
        }

        char *nameVB = malloc((nameBLen + 1) * sizeof(char));
        for (int i = 0; i < nameBLen; i++)
        {
            nameVB[i] = buff[nameALen + i + 1];
        }
        nameVB[nameBLen] = '\0';

        VERTICE *vA = NULL;
        VERTICE *vB = NULL;
        for (int i = 0; i < m->n; i++)
        {
            if (strcmp(m->vertices[i].nom, nameVA) == 0)
            {
                vA = &m->vertices[i];
            }
            else if (strcmp(m->vertices[i].nom, nameVB) == 0)
            {
                vB = &m->vertices[i];
            }
        }
        if (vA != NULL && vB != NULL)
        {
            add_liste(m, vA, vB);
        }
        chars = getline(&buff, &buff_size, stream);
    }
    free(buff);

    fclose(stream);
    return m;
}

/**
 * @brief Save the graph represented by a list in a file following the same structure as load() function
 * 
 * @param l The list to save
 * @param nom Path to the file
 */
void save_list(LISTE *l, char *nom)
{
    // Le graphe étant non orienté la matrice de représentation est symétrique
    // Ainsi pour connaitre les aretes un parcours de la partie supérieure ou inférieure de la matrice est suffisant

    FILE *stream = fopen(nom, "w");
    char buff[20];
    fprintf(stream, "%d\n", l->n);

    // Save vertices
    for (int i = 0; i < l->n; i++)
    {
        fprintf(stream, "%d %s\n", l->vertices[i].id, l->vertices[i].nom);
    }

    int e;
    char line[40] = "";
    for (int i = 0; i < l->n; i++)
    {
        for (int j = 0; j < l->sizes[i]; j++)
        {
            if (l->graph[i][j] > i) {
                fprintf(stream, "%s %s\n", l->vertices[i].nom, l->vertices[l->graph[i][j]].nom);
            }
        }
    }

    fclose(stream);
}