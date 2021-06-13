#ifndef __aresta__
#define __aresta__
#include "ponto.h"

typedef void* Aresta;

Aresta createAresta(char nome[], char ldir[], char lesq[], double cmp, double vm, char destino[]);
// "constructor" da estrutura Aresta

char* getNomeAresta(Aresta aresta);

char* getLdirAresta(Aresta aresta);

char* getLesqAresta(Aresta aresta);

double getCmpAresta(Aresta aresta);

double getVmAresta(Aresta aresta);

char* getIdfAresta(Aresta aresta);

double getTempoAresta(Aresta aresta);

char* getDestinoAresta(Aresta aresta);

Aresta copyAresta(Aresta antiga, char destino[]);

#endif