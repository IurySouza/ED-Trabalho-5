#ifndef __InstrumentoUrbano__
#define __InstrumentoUrbano__
#include <stdio.h>
#include "ponto.h"

typedef void* Instrumento;

Instrumento criarInstrumento(char id[], double x, double y, char espessura[], char corp[], char corb[]);
//"constructor" da estrutura instrumento urbano

char* getIdIU(Instrumento instrumento);
// retorna o id do instrumento urbano

Ponto getPontoIU(Instrumento instrumento);
// retorna o ponto do instrumento urbano

void setPontoIU(Instrumento instrumento, Ponto p);
// atualiza o ponto do instrumento urbano

char* getEspessuraIU(Instrumento instrumento);
// retorna o valor da espessura da borda do instrumento urbano

void setEspessuraIU(Instrumento instrumento, char espessura[]);
// atualiza o valor da espessura da borda do instrumento urbano

char* getCorbIU(Instrumento instrumento);
// retorna a cor da borda do instrumento urbano

void setCorbIU(Instrumento instrumento, char corb[]);
// atualiza o valor da cor da borda do instrumento urbano

char* getCorpIU(Instrumento instrumento);
// retorna a cor de preenchimento do instrumento urbano

void setCorpIU(Instrumento instrumento, char corp[]);
// atualiza o valor da cor de preenchimento do instrumento urbano

void swapIU(Instrumento i1, Instrumento i2);
//troca o valor de dois ponteiros Instrumento

void desenharIU(Instrumento instrumento, FILE* svg);
// desenha o instrumento urbano no arquivo svg

void desalocaIU(Instrumento instrumento);
// desaloca a memoria utilizada para armazenar o instrumento
#endif