#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry5.h"
#include "ponto.h"

int getIndex(char r[]) {
    char* rAux = malloc((strlen(r) + 1) * sizeof(char));
    rAux = strcpy(rAux, r);
    rAux = rAux + 1;
    int indice = atoi(rAux);
    free(rAux - 1);
    return indice - 1;
}

void m(FILE* svg, char r[], char cpf[], Ponto reg[11], Lista extraFig) {

}