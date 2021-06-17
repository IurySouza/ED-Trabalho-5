#ifndef __qry5__
#define __qry5__

#include "lista.h"
#include "ponto.h"
#include "tabelaEspalhamento.h"
#include "quadtree.h"

int getIndex(char r[]);

void m(FILE* svg, char r[], char cpf[], Ponto reg[11], HashTable ht[4], Lista extraFig);

void e(FILE* svg, char r[], char cep[], char face, int num, Ponto reg[11], HashTable ht[4], Lista extraFig);

void g(FILE* svg, char r[], Ponto reg[11], char id[], QuadTree qt[11], Lista extraFig);

void xy(FILE* svg, char r[], Ponto reg[11], double x, double y, Lista extraFig);

#endif