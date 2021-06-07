#ifndef __qry1__
#define __qry1__
#include <stdio.h>
#include "quadtree.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "lista.h"

void pnt(FILE* txt, QuadTree quadtrees[11], char id[], char corb[], char corp[]);
//Pinta a borda e o preenchimento da forma/texto de acordo com os parametros passados

void delf(FILE* txt, QuadTree quadtrees[11], char id[]);
//Deleta a forma/texto de identificador id

void pontoInterno(FILE* svg, FILE* txt, QuadTree quadtrees[11], char id[], double xPonto,double yPonto, Lista extraFig);
//Verifica se o ponto é interno a figura e desenha no svg o ponto e a linha

void intersecao(FILE* svg, FILE* txt, QuadTree quadtrees[11], char id1[], char id2[], Lista extraFig);
//Seleciona as figuras para realizar o comando i?

#endif