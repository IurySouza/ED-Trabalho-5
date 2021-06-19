#ifndef __grafo__
#define __grafo__
#include "vertice.h"
#include "aresta.h"
#include "lista.h"

typedef void* Grafo;
typedef void* AdjList;

// "constructor" da estrutura Grafo, que consiste em uma lista de adjLists
Grafo createGrafo();

//retorna o vertice armazenado em uma adjList
Vertice getVertice(AdjList adjList);

//retorna uma lista com as arestas armazenadas na adjList
Lista getListaArestas(AdjList adjList);

//retorna uma adjList do grafo, de acordo com o id do seu vertice
AdjList getAdjList(Grafo grafo, char id[]);

//retorna uma aresta da adjList, de acordo com o id do vertice de destino da aresta
Aresta getArestaByDest(AdjList adjList, char id[]);

//adiciona um vertice no grafo
void adicionarVertice(Grafo grafo, Vertice vertice);

//adiciona uma aresta no grafo
void adicionarAresta(Grafo grafo, char idi[], Aresta aresta);

//desaloca uma adjList, seu vertice e suas arestas
void desalocaAL(AdjList adjList);

//desaloca o grafo e suas adjlists
void desalocaGrafo(Grafo grafo);

//desenha uma aresta em um arquivo svg
void desenharAresta(Grafo grafo, AdjList adjList, Aresta aresta, FILE* svg);

//remove do grafos vertices que não possuem conexão com algum outro vertice
void excluirVerticesIsolados(Grafo g);

//a partir de um grafo direcionado, gera um grafo não direcionado
Grafo gerarGrafoNaoDirecionado(Grafo grafo);

//obtem a arvore geradora minima de um grafo não direcionado
Grafo prim(Grafo grafo);

//calcula o menor caminho entre dois vertices de um grafo, de acordo com o peso fornecido pela função getPeso
Lista dijkstra(Grafo grafo, char idi[], char idf[], double* distTotal, double getPeso(Aresta));

//desenha um grafo em um arquivo svg
void desenharGrafo(Grafo g, FILE* svg);

//desenha um path gerado pela função dijkstra em um arquivo svg
void desenharPath(FILE* fileSvg, Lista path, Grafo g, int id, char cor[]);

#endif