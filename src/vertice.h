#ifndef __vertice__
#define __vertice__
#include "ponto.h"

typedef void* Vertice;

// "constructor" da estrutura Vertice
Vertice createVertice(char id[], double x, double y);

//retorna o id do vertice
char* getIdVertice(Vertice vertice);

//retorna o ponto do vertice
Ponto getPontoVertice(Vertice vertice);

//desenha o vertice em um arquivo svg
void desenharVertice(Vertice vertice, FILE* svg);

//desaloca o vertice e seu ponto
void desalocaVertice(Vertice vertice);

//retorna uma copia do vertice
Vertice copyVertice(Vertice antigo);

#endif