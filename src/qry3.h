#ifndef __qry3__
#define __qry3__
#include <stdio.h>
#include "quadtree.h"
#include "lista.h"
#include "tabelaEspalhamento.h"

void cv(QuadTree qt[11], int n, char cep[], char face, int num);
/*
* Informa um novo caso de covid em um determinado endereço
* Entrada: vetor das quadtrees, número de casos e endereço (cep, face e num)
* Saida: void
*/
void soc(FILE* svg, FILE* txt, QuadTree qt[11], int k, char cep[], char face, int num, Lista extraFig);
/*
* Obtem os k postos de antendimentos mais proximos de um endereço
* Entrada: vetor das quadtrees, arquivos de saida txt e svg, k, lista de figuras geradas no qry e endereço (cep, face e num)
* Saida: void
*/

void ci(FILE* svg, FILE* txt, QuadTree qt[11], HashTable ht[4], double x, double y, double r, Lista extraFig);
/*
* Determina a região de incidência relativa aos casos e a categoria da região
* Entrada: vetor das quadtrees, arquivos de saida txt e svg, k, lista de figuras geradas no qry, vetor de hashtables  e circulo da região
* Saida: void
*/

#endif