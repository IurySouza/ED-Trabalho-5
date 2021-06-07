#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estabelecimento.h"
#include "ponto.h"
#include "quadra.h"

typedef struct{
    Ponto ponto;
    char cnpj[20];
    char nome[20];
    char cpf[20];
    char cep[20];
    char codt[10];
    char face;
    int numero;
}EstabelecimentoStruct;

Estabelecimento createEstabelecimento(Quadra quad, char cnpj[], char cpf[], char nome[], char codt[], char face, int num){
    EstabelecimentoStruct* estabelecimento = (EstabelecimentoStruct*) malloc(sizeof(EstabelecimentoStruct));
    double x = getX(getPontoQuad(quad));
    double y = getY(getPontoQuad(quad));
    double h = getHQuad(quad);
    double w = getWQuad(quad);
    switch (face){
    case 'n':
        x += num;
        y += h;
        break;
    case 's':
        x += num;
        break;
    case 'l':
        y += num;
        break;
    case 'o':
        x += w;
        y += num;
        break;
    }
    strcpy(estabelecimento->cnpj, cnpj);
    strcpy(estabelecimento->cpf, cpf);
    strcpy(estabelecimento->cep, getCEP(quad));
    strcpy(estabelecimento->nome, nome);
    strcpy(estabelecimento->codt, codt);
    estabelecimento->ponto = createPoint(x,y);
    estabelecimento->face = face;
    estabelecimento->numero = num;
    return estabelecimento;
}

char* getCepEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->cep;
}

char* getCpfEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->cpf;
}

char* getCnpjEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->cnpj;
}

char* getNomeEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->nome;
}
char* getCodtEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->codt;
}

Ponto getPontoEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->ponto;
}

char getFaceEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->face;
}

int getNumEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    return e->numero;
}

void swapEstabelecimento(Estabelecimento e1, Estabelecimento e2){  
    EstabelecimentoStruct* a = (EstabelecimentoStruct*) e1;
    EstabelecimentoStruct* b = (EstabelecimentoStruct*) e2;
    EstabelecimentoStruct temp = *a;  
    *a = *b;  
    *b = temp;  
}

void desalocarEstabelecimento(Estabelecimento estabelecimento){
    EstabelecimentoStruct* e = (EstabelecimentoStruct*) estabelecimento;
    free(e->ponto);
    free(e);
}