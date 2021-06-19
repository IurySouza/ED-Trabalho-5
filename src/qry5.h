#ifndef __qry5__
#define __qry5__

#include "lista.h"
#include "ponto.h"
#include "tabelaEspalhamento.h"
#include "quadtree.h"
#include "grafo.h"

//retorna o indice do resgistrador de acordo com o char* fornecido
int getIndex(char r[]);

//armazena no registrador o ponto do endereço relacionado ao cpf fornecido
void m(FILE* svg, char r[], char cpf[], Ponto reg[11], HashTable ht[4], Lista extraFig);

//armazena no registrador o ponto obtido de acordo com o endereço fornecido
void e(FILE* svg, char r[], char cep[], char face, int num, Ponto reg[11], HashTable ht[4], Lista extraFig);

//armazena no resgistrador o ponto obtido do instrumento urbano fornecido
void g(FILE* svg, char r[], Ponto reg[11], char id[], QuadTree qt[11], Lista extraFig);

//armazena no registrador o ponto fornecido
void xy(FILE* svg, char r[], Ponto reg[11], double x, double y, Lista extraFig);

//desenha a arvore geradora minima de um grafo no arquivo svg
void ccv(char nomeSaida[], char sufx[], Grafo grafo);

//Calcula os caminhos mais curto e mais rapido entre dois pontos, considerando o grafo fornecido, descrenvendo o caminho em um arquivo txt e fazendo uma animação em um arquivo txt
void pInit(char nomeSaida[], char sufx[], FILE* txt, QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]);

//Calcula os caminho mais curto entre dois pontos, considerando a arvore geradora minima do grafo, descrenvendo o caminho em um arquivo txt e fazendo uma animação em um arquivo txt
void pb(char nomeSaida[], char sufx[], FILE* txt, QuadTree qt[11], Grafo g, Ponto inicio, Ponto fim, int *idPath, char cmc[]);

//Faz o mesmo que pInit, porem desconsiderando do grafo vertices dentro da envotoria convexa formada pelos casos de covid
void sp(char nomeSaida[], char sufx[], FILE* txt, QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]);

//Deleta arestas pertos de quadras com mais que max casos de covid
void bf(FILE* txt, FILE* svg, int max, Grafo grafo, QuadTree qt, HashTable ht, Lista extraFig);

#endif