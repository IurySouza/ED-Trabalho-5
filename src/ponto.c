#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"
#include "verificacao.h"

typedef struct ponto{
    double x;
    double y;
}PontoStruct;

Ponto createPoint(double x, double y){
    PontoStruct* ponto = (PontoStruct*)malloc(sizeof(PontoStruct));
    ponto->x = x;
    ponto->y = y;
    return ponto;
}

void setX(Ponto ponto, double x){
    PontoStruct* p = (PontoStruct*) ponto;
    p->x = x;
}

double getX(Ponto ponto){
    PontoStruct* p = (PontoStruct*) ponto;
    return p->x;
}

void setY(Ponto ponto, double y){
    PontoStruct* p = (PontoStruct*) ponto;
    p->y = y;
}

double getY(Ponto ponto){
    PontoStruct* p = (PontoStruct*) ponto;
    return p->y;
}

void desenharPonto(Ponto pont, FILE* svg) {
    PontoStruct* ponto = (PontoStruct*) pont;
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"black\" />\n", ponto->x, ponto->y);
}

void swapPonto(Ponto p1, Ponto p2){
    PontoStruct* a = (PontoStruct*) p1;
    PontoStruct* b = (PontoStruct*) p2;
    PontoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void atribuirPonto(Ponto p1, Ponto p2){  
    PontoStruct* a = (PontoStruct*) p1;
    PontoStruct* b = (PontoStruct*) p2;
    *a = *b;  
}

double getPontoDist(Ponto pont, double x, double y) {
    PontoStruct* ponto = (PontoStruct*) pont;
    return distancia(ponto->x, ponto->y, x, y);
}