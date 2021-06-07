#ifndef __retangulo__
#define __retangulo__
#include <stdio.h>
#include "ponto.h"

typedef void* Retangulo;

Retangulo criarRetangulo(char* id, double x, double y, double w, double h, char espessura[], char corp[], char corb[]);
// "constructor da estrutura retangulo"

char* getIdRet(Retangulo ret);
// retorna o id do retangulo

Ponto getPontoRet(Retangulo ret);
// retorno o ponto do retangulo

void setPontoRet(Retangulo ret, Ponto p);
// atualiza o ponto do retangulo

char* getEspessuraRet(Retangulo ret);
// retorna o valor da espessura da borda do retangulo

void setEspessuraRet(Retangulo ret, char espessura[]);
// atualiza o valor da espessura da borda do retangulo

double getWRet(Retangulo ret);
// retorna o valor de w do retangulo

void setWRet(Retangulo ret, double w);
// atualiza o valor de w do retangulo

double getHRet(Retangulo ret);
// retorna o valor de h do retangulo

void setHRet(Retangulo ret, double h);
// atualiza o valor de h do retangulo

char* getCorbRet(Retangulo ret);
// retona a cor de borda do retangulo

void setCorbRet(Retangulo ret, char cor[]);
// atualiza o valor da cor de preenchimento do retangulo

char* getCorpRet(Retangulo ret);
// retorna a cor de preenchimento do retangulo

void setCorpRet(Retangulo ret, char cor[]);
// atualiza a cor de preenchimento do retangulo

void swapRet(Retangulo r1, Retangulo r2);
//troca o valor de dois ponteiros REtangulo

void desenharRetangulo(Retangulo retangulo, FILE* svg);
//desenha o retangulo no arquivo svg

void desalocaRet(Retangulo ret);
// desaloca a memoria utilizada para armazenar o retangulo

#endif