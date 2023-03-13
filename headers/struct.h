#ifndef DEF_STRUCT
#define DEF_STRUCT

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

typedef struct
{
    VERTICE *start;
    VERTICE *end;
    int d;
} DIST;

#endif