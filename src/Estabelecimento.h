#ifndef __Estabelecimento__
#define __Estabelecimento__
#include "ponto.h"
#include "quadra.h"

typedef void* Estabelecimento; 

Estabelecimento createEstabelecimento(Quadra quad, char cnpj[], char cpf[], char nome[], char codt[], char face, int num);
// "constructor" da estrutura Estabelecimento

char* getCepEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de cep

char* getCpfEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de cpf

char* getCnpjEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de cnpj

char* getNomeEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de nome

char* getCodtEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de codt

Ponto getPontoEstabelecimento(Estabelecimento estabelecimento);
// retorna o ponto

char getFaceEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de face

int getNumEstabelecimento(Estabelecimento estabelecimento);
// retorna o valor de num

void swapEstabelecimento(Estabelecimento e1, Estabelecimento e2);
// troca o valor de dois ponteiros Estabelecimento

void desalocarEstabelecimento(Estabelecimento estabelecimento);
// desaloca a memória utilizada para armazenar Estabelecimento

#endif