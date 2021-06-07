#ifndef __texto__
#define __texto__
#include <stdio.h>
#include "ponto.h"

typedef void* Texto;

Texto criarTexto(char* id, float x, float y, char corp[], char corb[], char txt[]);
//"constructor" da estrutura texto

char* getIdTxt(Texto txt);
//retorna o id do texto

Ponto getPontoTxt(Texto txt);
//retorna o ponto do texto

void setPontoTxt(Texto txt, Ponto p);
// atualiza o ponto do texto

char* getCorbTxt(Texto txt);
// retorna a cor da borda do texto

void setCorbTxt(Texto txt, char cor[]);
// atualiza o valor da cor da borda do texto

char* getCorpTxt(Texto txt);
// retorna a cor de preenchimento do texto

void setCorpTxt(Texto txt, char cor[]);
// atualiza o valor da cor de preenchimento do texto

char* getTexto(Texto txt);
// retorna o texto armazenado na estrutura

void setTexto(Texto txt, char linha[]);
// atualiza o texto armazenado na estrutura

void swapTxt(Texto t1, Texto t2);
//troca o valor de dois ponteiros Texto

void desenharTexto(Texto txt, FILE* svg);
// desenha o texto no arquivo svg

void desalocaTexto(Texto txt);
// desaloca a memoria utilizada para armazenar o texto

#endif