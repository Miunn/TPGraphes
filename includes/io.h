#ifndef DEF_IO
#define DEF_IO

#include "../includes/struct.h"

MATRIX *load(char *nom);
void save(MATRIX *m, char *nom);

LISTE *load_liste(char *nom);

#endif