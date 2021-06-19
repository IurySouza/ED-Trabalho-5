#ifndef __aresta__
#define __aresta__
#include "ponto.h"

typedef void* Aresta;

// "constructor" da estrutura Aresta
Aresta createAresta(char nome[], char ldir[], char lesq[], double cmp, double vm, char destino[]);

//retorna o nome da rua
char* getNomeAresta(Aresta aresta);

//retora o cep da quadra a esquerda da rua
char* getLdirAresta(Aresta aresta);

//retorna o cep da quadra a direitra da rua
char* getLesqAresta(Aresta aresta);

//retorna o comprimento da aresta
double getCmpAresta(Aresta aresta);

//retorna a velocidade media para percorrer a rua
double getVmAresta(Aresta aresta);

//retorna o tempo para percorrer a aresta de acordo com o cmp e a vm
double getTempoAresta(Aresta aresta);

//retorna o id do vertice de destino da aresta
char* getDestinoAresta(Aresta aresta);

//gera um copia da aresta
Aresta copyAresta(Aresta antiga, char destino[]);

#endif