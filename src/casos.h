#ifndef __casos__
#define __casos__
#include "lista.h"
#include "ponto.h"

typedef void* CasosCovid; 

CasosCovid createCasos(double x, double y, char cep[], char face, int numero, int n);
//Retorna um void pointer para uma struct armazenando informacoes sobre casos de covid

Ponto getPontoCaso(CasosCovid caso);
//Retorna o ponto da struct

char* getCEPCaso(CasosCovid caso);
//Retorna o valor do cep da struct

char getFaceCaso(CasosCovid caso);
//Retorna a face da struct

int getNumeroCaso(CasosCovid caso);
//Retorna o valor numero da struct

int getNCasos(CasosCovid caso);
//Retorna o numero de casos de covid da struct

void swapCasos(CasosCovid c1, CasosCovid c2);
//troca o valor de dois ponteiros CasosCovid

void desenharCasos(CasosCovid caso, FILE* svg);
//Adiciona uma representação da struct em um arquivo svg

void desalocarCaso(CasosCovid caso);
//Desaloca a memoria utilizada
#endif