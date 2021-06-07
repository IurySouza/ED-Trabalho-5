#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"
#include "ponto.h"

typedef struct retangulo{
    char id[6];
    Ponto ponto;
    double w;
    double h;
    char espessura[10];
    char corb[22];
    char corp[22];
} RetanguloStruct;

Retangulo criarRetangulo(char* id, double x, double y, double w, double h, char espessura[], char corp[], char corb[]){
    RetanguloStruct* retangulo = (RetanguloStruct*) malloc(sizeof(RetanguloStruct));
    strcpy(retangulo->id, id);
    retangulo->ponto = createPoint(x,y);
    retangulo->w = w;
    retangulo->h = h;
    strcpy(retangulo->espessura, espessura);
    strcpy(retangulo->corb, corb);
    strcpy(retangulo->corp, corp);
    return retangulo;
}

char* getIdRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->id;
}

Ponto getPontoRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->ponto;
}

void setPontoRet(Retangulo ret, Ponto p){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    retangulo->ponto = p;
}

char* getEspessuraRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->espessura;
}

void setEspessuraRet(Retangulo ret, char espessura[]){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    strcpy(retangulo->espessura, espessura);
}

double getWRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->w;
}

void setWRet(Retangulo ret, double w){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    retangulo->w = w;
}

double getHRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->h;
}

void setHRet(Retangulo ret, double h){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    retangulo->h = h;
}

char* getCorbRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->corb;
}

void setCorbRet(Retangulo ret, char cor[]){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    strcpy(retangulo->corb, cor);
}

char* getCorpRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    return retangulo->corp;
}

void setCorpRet(Retangulo ret, char cor[]){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    strcpy(retangulo->corp, cor);
}

void swapRet(Retangulo r1, Retangulo r2){
    RetanguloStruct* a = (RetanguloStruct*) r1;
    RetanguloStruct* b = (RetanguloStruct*) r2;
    RetanguloStruct temp = *a;
    *a = *b;
    *b = temp;
}

void desenharRetangulo(Retangulo retangulo, FILE* svg){
    RetanguloStruct* ret = (RetanguloStruct*) retangulo;
    fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\"  stroke-width=\"%s\"/>\n",getX(ret->ponto),getY(ret->ponto),ret->w,ret->h,ret->corp,ret->corb,ret->espessura);
}

void desalocaRet(Retangulo ret){
    RetanguloStruct* retangulo = (RetanguloStruct*) ret;
    free(retangulo->ponto);
    free(retangulo);
}