#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "texto.h"
#include "ponto.h"

typedef struct texto{
    char id[6];
    Ponto ponto;
    char txt[255];
    char corb[22];
    char corp[22];
} TextoStruct;

Texto criarTexto(char* id, float x, float y, char corp[], char corb[], char txt[]){
    TextoStruct* texto = (TextoStruct*) malloc(sizeof(TextoStruct));
    strcpy(texto->id, id);
    texto->ponto = createPoint(x,y);
    strcpy(texto->corb, corb);
    strcpy(texto->corp, corp);
    strcpy(texto->txt, txt);
    return texto;
}

char* getIdTxt(Texto txt){
    TextoStruct* texto = (TextoStruct*) txt;
    return texto->id;
}

Ponto getPontoTxt(Texto txt){
    TextoStruct* texto = (TextoStruct*) txt;
    return texto->ponto;
}

void setYTxt(Texto txt, Ponto p){
    TextoStruct* texto = (TextoStruct*) txt;
    texto->ponto = p;
}

char* getCorbTxt(Texto txt){
    TextoStruct* texto = (TextoStruct*) txt;
    return texto->corb;
}

void setCorbTxt(Texto txt, char cor[]){
    TextoStruct* texto = (TextoStruct*) txt;
    strcpy(texto->corb, cor);
}

char* getCorpTxt(Texto txt){
    TextoStruct* texto = (TextoStruct*) txt;
    return texto->corp;
}

void setCorpTxt(Texto txt, char cor[]){
    TextoStruct* texto = (TextoStruct*) txt;
    strcpy(texto->corp, cor);
}

char* getTexto(Texto txt){
    TextoStruct* texto = (TextoStruct*) txt;
    return texto->txt;
}

void setTexto(Texto txt, char linha[]){
    TextoStruct* texto = (TextoStruct*) txt;
    strcpy(texto->txt, linha);
}

void swapTxt(Texto t1, Texto t2){
    TextoStruct* a = (TextoStruct*) t1;
    TextoStruct* b = (TextoStruct*) t2;
    TextoStruct temp = *a;
    *a = *b;
    *b = temp;
}

void desenharTexto(Texto txt, FILE* svg){
    TextoStruct* texto = (TextoStruct*) txt;
    fprintf(svg,"\t<text x=\"%lf\" y=\"%lf\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\">%s</text>\n",getX(texto->ponto),getY(texto->ponto),texto->corb,texto->corp,texto->txt);
}

void desalocaTexto(Texto txt){
    TextoStruct* texto = (TextoStruct*) txt;
    free(texto->ponto);
    free(texto);
}