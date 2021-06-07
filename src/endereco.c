#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "endereco.h"
#include "ponto.h"
#include "quadra.h"

typedef struct{
    Ponto ponto;
    char cpf[20];
    char cep[20];
    char compl[20];
    char face;
    int numero;
}EnderecoStruct;

Endereco createEndereco(Quadra quad, char cpf[], char face, int num, char compl[]){
    EnderecoStruct* endereco = (EnderecoStruct*) malloc(sizeof(EnderecoStruct));
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
    strcpy(endereco->cpf, cpf);
    strcpy(endereco->cep, getCEP(quad));
    strcpy(endereco->compl, compl);
    endereco->ponto = createPoint(x,y);
    endereco->face = face;
    endereco->numero = num;
    return endereco;
}

void setCepEndereco(Endereco endereco, char cep[]) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    strcpy(e->cep, cep);
}

char* getCepEndereco(Endereco endereco){
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    return e->cep;
}

void setCpfEndereco(Endereco endereco, char cpf[]) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    strcpy(e->cpf, cpf);
}

char* getCpfEndereco(Endereco endereco){
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    return e->cpf;
}

void setPontoEndereco(Endereco endereco, Ponto p) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    e->ponto = p;
}

Ponto getPontoEndereco(Endereco endereco){
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    return e->ponto;
}

void setFaceEndereco(Endereco endereco, char face) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    e->face = face;
}

char getFaceEndereco(Endereco endereco){
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    return e->face;
}

void setNumEndereco(Endereco endereco, int num) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    e->numero = num;
}

int getNumEndereco(Endereco endereco){
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    return e->numero;
}

void setComplementoEndereco(Endereco endereco, char compl[]) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    strcpy(e->compl, compl);
}

char* getComplementoEndereco(Endereco endereco) {
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    return e->compl;
}

void swapEndereco(Endereco e1, Endereco e2){  
    EnderecoStruct* a = (EnderecoStruct*) e1;
    EnderecoStruct* b = (EnderecoStruct*) e2;
    EnderecoStruct temp = *a;  
    *a = *b;  
    *b = temp;  
}

void desalocarEndereco(Endereco endereco){
    EnderecoStruct* e = (EnderecoStruct*) endereco;
    free(e->ponto);
    free(e);
}