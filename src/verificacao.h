#ifndef __verificacao__
#define __verificacao__
#include <stdio.h>
#include "retangulo.h"
#include "circulo.h"
#include "quadra.h"
#include "regiao.h"
#include "ponto.h"

double maior(double n1, double n2);
//Retorna o maior double entre os parametros

double menor(double n1, double n2);
//Retorna o menor double entre os parametros

double distancia(double x1, double y1, double x2, double y2);
//Retorna a distancia entre dois pontos

int retInternoCirc(double xRet, double yRet, double w, double h, double x, double y, double r);
//Verifica se o retangulo esta inteiramente dentro do circulo de centro (x,y) e raio r;

int retInternoRet(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2);
//Verifica se o retangulo esta inteiramente dentro do retangulo de ponto (x,y), largura w e altura h;

int pontoInternoCirc(double x, double y, double xCirc, double yCirc, double r);
//Verifica se o ponto esta inteiramente dentro do circulo de centro (x,y) e raio r;

int pontoInternoRet(double x, double y, double xRet, double yRet, double w, double h);
//Verifica se o ponto esta inteiramente dentro do retangulo de ponto (x,y), largura w e altura h;

int circIntRegiao(Regiao dd, double x, double y, double r);
//Verifica se o circulo é interno a uma região;

double obterArea(Lista l);
//Calcula a area de um poligono descrito por um lista da estrutura de Casos de covid, onde os vertices estão ordenados no sentido anti-horario;

Ponto centroide(Lista l, double area);
//Calcula a centroide de um poligono descrito por um lista da estrutura de Casos de covid, onde os vertices estão ordenados no sentido anti-horario;

#endif