#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "ponto.h"

typedef struct circulo{
    char id[6];
    Ponto ponto;
    double r;
    char espessura[10];
    char corb[22];
    char corp[22];
} CirculoStruct;

Circulo criarCirculo(char* id, double x, double y, double r, char espessura[], char corp[], char corb[]){
    CirculoStruct* circulo = (CirculoStruct*) malloc(sizeof(CirculoStruct));
    strcpy(circulo->id, id);
    circulo->ponto = createPoint(x,y);
    circulo->r = r;
    strcpy(circulo->espessura, espessura);
    strcpy(circulo->corb, corb);
    strcpy(circulo->corp, corp);
    return circulo;
}

char* getIdCirc(Circulo circ){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    return circulo->id;
}

Ponto getPontoCirc(Circulo circ){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    return circulo->ponto;
}

void setPontoCirc(Circulo circ, Ponto p){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    circulo->ponto = p;
}

double getRCirc(Circulo circ){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    return circulo->r;
}

void setRCirc(Circulo circ, double r){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    circulo->r = r;
}

char* getEspessuraCirc(Circulo circ){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    return circulo->espessura;
}

void setEspessuraCirc(Circulo circ, char espessura[]){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    strcpy(circulo->espessura, espessura);
}


char* getCorbCirc(Circulo circ){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    return circulo->corb;
}

void setCorbCirc(Circulo circ, char cor[]){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    strcpy(circulo->corb, cor);
}

char* getCorpCirc(Circulo circ){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    return circulo->corp;
}

void setCorpCirc(Circulo circ, char cor[]){
    CirculoStruct* circulo = (CirculoStruct*) circ;
    strcpy(circulo->corp, cor);
}

void swapCirc(Circulo c1, Circulo c2){
    CirculoStruct* a = (CirculoStruct*) c1;
    CirculoStruct* b = (CirculoStruct*) c2;
    CirculoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void desenharCirculo(Circulo circulo, FILE* svg){
    CirculoStruct* circ = (CirculoStruct*) circulo;
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",getX(circ->ponto),getY(circ->ponto),circ->r,circ->corp,circ->corb,circ->espessura);
}

void desalocaCirc(Circulo circulo){
    CirculoStruct* circ = (CirculoStruct*) circulo;
    free(circ->ponto);
    free(circ);
}