#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "casos.h"
#include "ponto.h"

typedef struct Endereco{
    Ponto ponto;
    char cep[20];
    char face;
    int numero;
    int n;
}EnderecoStruct;

CasosCovid createCasos(double x, double y, char cep[], char face, int numero, int n){
    EnderecoStruct* caso = (EnderecoStruct*) malloc(sizeof(EnderecoStruct));
    caso->ponto = createPoint(x,y);
    caso->numero = numero;
    caso->n = n;
    caso->face = face;
    strcpy(caso->cep,cep);
    return caso;
}

Ponto getPontoCaso(CasosCovid caso){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    return c->ponto;
}

char* getCEPCaso(CasosCovid caso){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    return c->cep;
}

char getFaceCaso(CasosCovid caso){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    return c->face;
}

int getNumeroCaso(CasosCovid caso){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    return c->numero;
}

int getNCasos(CasosCovid caso){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    return c->n;
}

void swapCasos(CasosCovid c1, CasosCovid c2){  
    EnderecoStruct* a = (EnderecoStruct*) c1;
    EnderecoStruct* b = (EnderecoStruct*) c2;
    EnderecoStruct temp = *a;  
    *a = *b;  
    *b = temp;  
}

void desenharCasos(CasosCovid caso, FILE* svg){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    double h = 40, w = 25;
    double x = getX(getPontoCaso(c));
    double y = getY(getPontoCaso(c));
    switch (getFaceCaso(c)){
    case 'n':
        y -= h;
        break;
    case 'o':
        x -= w;
        break;
    }
    fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" />\n",x,y,w,h,"orange");
    fprintf(svg,"\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" >%d</text>\n",x + w/2,y + h/2,getNCasos(c));
}

void desalocarCaso(CasosCovid caso){
    EnderecoStruct* c = (EnderecoStruct*) caso;
    free(c->ponto);
    free(c);
}