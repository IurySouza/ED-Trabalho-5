#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"
#include "ponto.h"

typedef struct quadra{
    char cep[20];
    Ponto ponto;
    double w;
    double h;
    char espessura[10];
    char corb[22];
    char corp[22];
    double densidade;
}QuadraStruct;

Quadra criarQuadra(char cep[], double x, double y, char espessura[], double w, double h, char corp[], char corb[]){
    QuadraStruct* quadra = (QuadraStruct*) malloc(sizeof(QuadraStruct));
    quadra->ponto = createPoint(x,y);
    quadra->h = h;
    quadra->w = w;
    strcpy(quadra->espessura, espessura);
    strcpy(quadra->cep,cep);
    strcpy(quadra->corb,corb);
    strcpy(quadra->corp,corp);
    quadra->densidade = 0;
    return quadra;
}

char* getCEP(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->cep;
}

Ponto getPontoQuad(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->ponto;
}

void setPontoQuad(Quadra quadra, Ponto p){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->ponto = p;
}

double getWQuad(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->w;
}

void setWQuad(Quadra quadra, double w){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->w = w;
}

double getHQuad(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->h;
}

void setHQuad(Quadra quadra, double h){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->h = h;
}

char* getEspessuraQuad(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->espessura;
}

void setEspessuraQuad(Quadra quadra, char espessura[]){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->espessura, espessura);
}

char* getCorbQuad(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->corb;
}

void setCorbQuad(Quadra quadra, char corb[]){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->corb,corb);
}

char* getCorpQuad(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->corp;
}

void setCorpQuad(Quadra quadra, char corp[]){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    strcpy(quad->corp,corp);
}

double getDensidade(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    return quad->densidade;
}

void setDensidade(Quadra quadra, double densidade){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    quad->densidade = densidade;
}

void swapQuad(Quadra q1, Quadra q2){
    QuadraStruct* a = (QuadraStruct*) q1;
    QuadraStruct* b = (QuadraStruct*) q2;
    QuadraStruct temp = *a;
    *a = *b;
    *b = temp;
}

void desenharQuadra(Quadra quadra, FILE* svg){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    int aux;
    if(quad->densidade <= 500){
        aux = 0;
    }
    else if(quad->densidade <= 1500){
        aux = 1;
    }
    else if(quad->densidade <= 3000){
        aux = 2;
    }
    else if(quad->densidade <= 4500){
        aux = 3;
    }
    else if(quad->densidade <= 6000){
        aux = 4;
    }
    else{
        aux = 5;
    }
    fprintf(svg,"\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\"  stroke-width=\"%s\" filter=\"url(#shadow%d)\"/>\n",getX(quad->ponto),getY(quad->ponto),quad->w,quad->h,quad->corp,quad->corb,quad->espessura,aux);
    fprintf(svg,"\t<text x=\"%lf\" y=\"%lf\" >%s</text>\n", getX(quad->ponto) + quad->w/2, getY(quad->ponto) + quad->h/2, quad->cep);
}

void desalocaQuadra(Quadra quadra){
    QuadraStruct* quad = (QuadraStruct*) quadra;
    free(quad->ponto);
    free(quad);
}