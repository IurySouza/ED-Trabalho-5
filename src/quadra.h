#ifndef __quadra__
#define __quadra__
#include <stdio.h>
#include "ponto.h"

typedef void* Quadra;

Quadra criarQuadra(char cep[], double x, double y, char espessura[], double w, double h, char corp[], char corb[]);
// "constructor" da estrutura quadra

char* getCEP(Quadra quadra);
// retorna o cep da quadra

Ponto getPontoQuad(Quadra quadra);
// retorna o ponto da quadra

void setPontoQuad(Quadra quadra, Ponto p);
// atualiza o ponto da quadra

double getWQuad(Quadra quadra);
// retorna o valor de w da quadra

void setWQuad(Quadra quadra, double w);
// atualiza o valor de w da quadra

double getHQuad(Quadra quadra);
// retorna o valor de h da quadra

void setHQuad(Quadra quadra, double h);
// atualiza o valor de h da quadra

char* getEspessuraQuad(Quadra quadra);
// retorna o valor da espessura da borda da quadra

void setEspessuraQuad(Quadra quadra, char espessura[]);
// atualiza o valor da espessura da borda da quadra

char* getCorbQuad(Quadra quadra);
// retorna a cor da borda da quadra

void setCorbQuad(Quadra quadra, char corb[]);
// atualiza o valor da cor da borda da quadra

char* getCorpQuad(Quadra quadra);
// retorna o valor da cor de preenchimento da quadra

void setCorpQuad(Quadra quadra, char corp[]);
// atualiza o valor da cor de preenchimento da quadra

double getDensidade(Quadra quadra);
// retorna o valor da densidade da quadra

void setDensidade(Quadra quadra, double densidade);
// atualiza o valor da densidade da quadra

void swapQuad(Quadra q1, Quadra q2);
//troca o valor de dois ponteiros Quadra

void desenharQuadra(Quadra quadra, FILE* svg);
// desenha a quadra no arquivo svg

void desalocaQuadra(Quadra quadra);
// desaloca a memoria utilizada para armazenar a quadra

#endif