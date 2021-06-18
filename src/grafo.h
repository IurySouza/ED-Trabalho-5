#ifndef __grafo__
#define __grafo__
#include "vertice.h"
#include "aresta.h"
#include "lista.h"

typedef void* Grafo;
typedef void* AdjList;

Grafo createGrafo();
// "constructor" da estrutura Grafo

Vertice getVertice(AdjList adjList);

Lista getListaArestas(AdjList adjList);

AdjList getAdjList(Grafo grafo, char id[]);

Aresta getArestaByDest(AdjList adjList, char id[]);

void adicionarVertice(Grafo grafo, Vertice vertice);

void adicionarAresta(Grafo grafo, char idi[], Aresta aresta);

void desalocaAL(AdjList adjList);

void desalocaGrafo(Grafo grafo);

void desenharAresta(Grafo grafo, AdjList adjList, Aresta aresta, FILE* svg);

void excluirVerticesIsolados(Grafo g);

Grafo gerarGrafoNaoDirecionado(Grafo grafo);

Grafo prim(Grafo grafo);

Lista dijkstra(Grafo grafo, char idi[], char idf[], double* distTotal, double getPeso(Aresta aresta));

void desenharGrafo(Grafo g, FILE* svg);

void desenharPath(FILE* fileSvg, Lista path, Grafo g, int id, char cor[]);

#endif