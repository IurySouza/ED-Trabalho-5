#ifndef __vertice__
#define __vertice__
#include "ponto.h"

typedef void* Vertice;

Vertice createVertice(char id[], double x, double y);
// "constructor" da estrutura Vertice

char* getIdVertice(Vertice vertice);

Ponto getPontoVertice(Vertice vertice);

void desenharVertice(Vertice vertice, FILE* svg);

void desalocaVertice(Vertice vertice);

Vertice copyVertice(Vertice antigo);

#endif