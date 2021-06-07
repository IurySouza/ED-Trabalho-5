#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instrumentoUrbano.h"
#include "ponto.h"

typedef struct instrumento{
    char id[20];
    Ponto ponto;
    char espessura[10];
    char corb[22];
    char corp[22];
} InstrumentoStruct;

Instrumento criarInstrumento(char id[], double x, double y, char espessura[], char corp[], char corb[]){
    InstrumentoStruct* iu = (InstrumentoStruct*)malloc(sizeof(InstrumentoStruct));
    iu->ponto = createPoint(x,y);
    strcpy(iu->espessura, espessura);
    strcpy(iu->id,id);
    strcpy(iu->corb,corb);
    strcpy(iu->corp,corp);
    return iu;
}

char* getIdIU(Instrumento instrumento){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    return iu->id;
}

Ponto getPontoIU(Instrumento instrumento){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    return iu->ponto;
}

void setPontoIU(Instrumento instrumento, Ponto p){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    iu->ponto = p;
}

char* getEspessuraIU(Instrumento instrumento){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    return iu->espessura;
}

void setEspessuraIU(Instrumento instrumento, char espessura[]){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    strcpy(iu->espessura, espessura);
}

char* getCorbIU(Instrumento instrumento){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    return iu->corb;
}

void setCorbIU(Instrumento instrumento, char corb[]){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    strcpy(iu->corb, corb);
}

char* getCorpIU(Instrumento instrumento){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    return iu->corp;
}

void setCorpIU(Instrumento instrumento, char corp[]){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    strcpy(iu->corp, corp);
}

void swapIU(Instrumento i1, Instrumento i2){
    InstrumentoStruct* a = (InstrumentoStruct*) i1;
    InstrumentoStruct* b = (InstrumentoStruct*) i2;
    InstrumentoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void desenharIU(Instrumento instrumento, FILE* svg){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"%s\" stroke=\"%s\" stroke-width=\"%s\"/>\n",getX(iu->ponto),getY(iu->ponto),iu->corp,iu->corb,iu->espessura);
}

void desalocaIU(Instrumento instrumento){
    InstrumentoStruct* iu = (InstrumentoStruct*) instrumento;
    free(iu->ponto);
    free(iu);
}