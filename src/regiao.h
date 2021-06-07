#ifndef __regiao__
#define __regiao__
#include "ponto.h"
#include "quadra.h"
#include "quadtree.h"

typedef void* Regiao;

Regiao criarRegiao(double x, double y, double w, double h, double d);
//"constructor" da estrutura regiao

Ponto getPontoRegiao(Regiao reg);
//retorna o X da regiao

void setPontoRegiao(Regiao reg, Ponto p);
//define o ponto da regiao

double getWRegiao(Regiao reg);
//retorna a largura da regiao

void setWRegiao(Regiao reg, double w);
//define a largura da regiao

double getHRegiao(Regiao reg);
//retorna a altura da regiao

void setHRegiao(Regiao reg, double h);
//define a altura da regiao

double getDRegiao(Regiao reg);
//retorna a densidade da regiao

void setDRegiao(Regiao reg, double d);
//define a densidade da regiao

void desalocarRegiao(Regiao reg);
//desaloca a memoria utilizada para armazenar a regiao

void densidadeQuadras(Regiao reg, QuadTree quadras);
//Define a densidade das quadras da região

#endif