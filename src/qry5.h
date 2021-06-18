#ifndef __qry5__
#define __qry5__

#include "lista.h"
#include "ponto.h"
#include "tabelaEspalhamento.h"
#include "quadtree.h"
#include "grafo.h"

int getIndex(char r[]);

void m(FILE* svg, char r[], char cpf[], Ponto reg[11], HashTable ht[4], Lista extraFig);

void e(FILE* svg, char r[], char cep[], char face, int num, Ponto reg[11], HashTable ht[4], Lista extraFig);

void g(FILE* svg, char r[], Ponto reg[11], char id[], QuadTree qt[11], Lista extraFig);

void xy(FILE* svg, char r[], Ponto reg[11], double x, double y, Lista extraFig);

void p(char nomeSaida[], char sufx[], QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]);

void pb(char nomeSaida[], char sufx[], QuadTree qt[11], Grafo g, Ponto inicio, Ponto fim, int *idPath, char cmc[]);

#endif