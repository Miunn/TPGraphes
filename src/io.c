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

    chars = getline(&buff, &buff_size, stream);
    int vertices = atoi(buff);
    if (vertices <= 0)
    {
        fprintf(stderr, "[ERROR] Invalid data file. Number of vertices isn't a valid number.");
        return NULL;
    }

    MATRIX *m = graphe_vide_matrix();
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
        add_sommet_matrix(m, (VERTICE){name, id});
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
    fprintf(stream, "%d\n", m->n);

    // Save vertices
    for (int i = 0; i < m->n; i++)
    {
        fprintf(stream, "%d %s\n", m->vertices[i].id, m->vertices[i].nom);
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
                fprintf(stream, "%s %s\n", m->vertices[i].nom, m->vertices[j].nom);
            }
        }
    }

    fclose(stream);
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