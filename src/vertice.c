#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "vertice.h"

typedef struct vertice{
    char id[50];
    Ponto ponto;
}VerticeStruct;

Vertice createVertice(char id[], double x, double y){
    VerticeStruct* vertice = (VerticeStruct*)malloc(sizeof(VerticeStruct));
    strcpy(vertice->id,id);
    vertice->ponto = createPoint(x,y);
    return vertice;
}

char* getIdVertice(Vertice vertice){
    VerticeStruct* v = (VerticeStruct*) vertice;
    return v->id;
}

Ponto getPontoVertice(Vertice vertice){
    VerticeStruct* v = (VerticeStruct*) vertice;
    return v->ponto;
}

void desenharVertice(Vertice vertice, FILE* svg){
    VerticeStruct* v = (VerticeStruct*) vertice;
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"10\" fill=\"blue\" stroke=\"blue\" />\n",getX(v->ponto),getY(v->ponto));
    fprintf(svg,"\t<text x=\"%lf\" y=\"%lf\" stroke=\"black\" text-anchor=\"middle\" stroke-width=\"0.3\" fill=\"black\">%s</text>\n",getX(v->ponto),getY(v->ponto),v->id);
}

void desalocaVertice(Vertice vertice){
    VerticeStruct* v = (VerticeStruct*) vertice;
    free(v->ponto);
    free(v);
}

Vertice copyVertice(Vertice antigo){
    VerticeStruct* vertice = (VerticeStruct*)malloc(sizeof(VerticeStruct));
    VerticeStruct* v = (VerticeStruct*) antigo;
    strcpy(vertice->id,v->id);
    vertice->ponto = createPoint(getX(v->ponto),getY(v->ponto));
    return vertice;
}