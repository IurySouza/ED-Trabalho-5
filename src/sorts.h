#ifndef __ordenar__
#define __ordenar__
#include "lista.h"
#include "quadtree.h"
#include "ponto.h"

No partition(Lista l, No primeiro, No ultimo, Ponto (*getPonto)(Info), void (*swap)(Info*, Info*));
//organiza a lista de colocando todos os elementos "maiores" fiquem depois do ultimo elemento

void quickSortList(Lista l, No primeiro, No ultimo, Ponto (*getPonto)(Info), void (*swap)(Info*, Info*));
//ordena uma lista pelo algoritmo quicksort

int orientacao(Ponto a, Ponto b, Ponto c);
//verifica se os 3 pontos estao no sentido anti-horario

int comparar(Ponto p0, Ponto a, Ponto b);
//funcao para comparar dois valores de um lista que está sendo ordenada no quicksort

Lista convexHull(Lista list, Ponto (*getPonto)(Info), void (*swap)(Info, Info));
//obtem a envoltoria convexa de uma lista de endereços

void shellSort(Lista list, double x, double y);
//ordena uma lista pelo algoritmo shellsort

Info getIndexInfo(Lista list, int i);
//retorna a informação contida no nó de index i na lista list

void balancearQuadTree(QuadTree qt, Lista l, void* (*getPonto)(void*), void (*swap)(void*, void*));
//adiciona os elementos da lista l na quadtree qt, utilizando o algoritmo da envoltória convexa para gerar uma quadtree balanceada 

#endif