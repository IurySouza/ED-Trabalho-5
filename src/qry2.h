#ifndef __qry2__
#define __qry2__

#include "quadtree.h"
#include "lista.h"

void dq(FILE *svg, FILE *txt, QuadTree quadtrees[11], int flag, char id[], double r, Lista extraFig);
// deleta todas as quadras dentro do circulo de raio r e centro no IU identificado por id

void del(FILE *svg, FILE *txt, QuadTree quadtrees[11], char cepid[], Lista extraFig);
// remove a quadra ou instrumento urbano identificado por cepid

void cbq(FILE *txt, QuadTree quadtrees[11], double x, double y, double r, char cstrk[]);
//Muda a cor da borda de todas as quadras dentro do circulo

void crd(FILE *txt, QuadTree quadtrees[11], char cepid[]);
//imprime no arquivo txt as informações da quadra ou instrumento urbano identificado por cepid

void car(FILE *svg, FILE *txt, QuadTree quadtrees[11], double x, double y, double w, double h, Lista extraFig);
//Calcula a área das quadras dentro de um retangulo e informa o resultado nos arquivos de saida

#endif