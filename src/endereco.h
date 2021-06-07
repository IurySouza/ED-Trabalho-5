#ifndef __endereco__
#define __endereco__
#include "ponto.h"
#include "quadra.h"

typedef void* Endereco; 

Endereco createEndereco(Quadra quad, char cpf[], char face, int num, char compl[]);
// "constructor" da estrutura Endereco

void setCepEndereco(Endereco endereco, char cep[]);
// atualiza o valor cep

char* getCepEndereco(Endereco endereco);
// retorna o valor de cep

void setCpfEndereco(Endereco endereco, char cpf[]);
// atualiza o valor de cpf

char* getCpfEndereco(Endereco endereco);
// retorna o valor de cpf

void setPontoEndereco(Endereco endereco, Ponto p);
// atualiza ponto

Ponto getPontoEndereco(Endereco endereco);
// retorna ponto

void setFaceEndereco(Endereco endereco, char face);
// atualiza o valor de face

char getFaceEndereco(Endereco endereco);
// retorna o valor de face

void setNumEndereco(Endereco endereco, int num);
// atualiza o valor de num

int getNumEndereco(Endereco endereco);
// retorna o valor de num

void setComplementoEndereco(Endereco endereco, char compl[]);
// atualiza o valor de compl

char* getComplementoEndereco(Endereco endereco);
// retorna o valor de compl

void swapEndereco(Endereco e1, Endereco e2);
// troca o valor de dois ponteiros Endereco

void desalocarEndereco(Endereco endereco);
// desaloca a memória utilizada para armazenar endereço

#endif