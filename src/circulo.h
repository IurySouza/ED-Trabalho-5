#ifndef __circulo__
#define __circulo__
#include <stdio.h>
#include "ponto.h"

typedef void* Circulo;

Circulo criarCirculo(char* id, double x, double y, double r, char espessura[], char corp[], char corb[]);
//"constructor" da estrutura circulo

char* getIdCirc(Circulo circ);
// retorna o valor de id do circulo

Ponto getPontoCirc(Circulo circ);
// retorna o ponto do circulo

void setPontoCirc(Circulo circ, Ponto p);
// atualiza o ponto do circulo

double getRCirc(Circulo circ);
// retorna o valor do raio do circulo

void setRCirc(Circulo circ, double r);
// atualiza o valor do raio do circulo

char* getEspessuraCirc(Circulo circ);
// retorna o valor da espessura da borda do circulo

void setEspessuraCirc(Circulo circ, char espessura[]);
// atualiza o valor da espessura da borda do circulo

char* getCorbCirc(Circulo circ);
// retorna a cor da borda do circulo

void setCorbCirc(Circulo circ, char cor[]);
// atualiza a cor da borda do circulo

char* getCorpCirc(Circulo circ);
// retorna a cor de preenchimento do circulo

void setCorpCirc(Circulo circ, char cor[]);
// atualiza a cor de preenchimento do circulo

void swapCirc(Circulo c1, Circulo c2);
//troca o valor de dois ponteiros Circulo

void desenharCirculo(Circulo circulo, FILE* svg);
// desenha o circulo no arquivo svg

void desalocaCirc(Circulo circulo);
// desaloca a memoria utilizada para armazenar o circulo

#endif