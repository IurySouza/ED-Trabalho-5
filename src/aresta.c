#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"
#include "aresta.h"

typedef struct aresta{
    char nome[50];
    char ldir[25];
    char lesq[25];
    double cmp;
    double vm;
    char destino[50];
}StructAresta;

Aresta createAresta(char nome[], char ldir[], char lesq[], double cmp, double vm, char destino[]){
    StructAresta* aresta = (StructAresta*)malloc(sizeof(StructAresta));
    strcpy(aresta->nome,nome);
    strcpy(aresta->ldir,ldir);
    strcpy(aresta->lesq,lesq);
    aresta->cmp = cmp;
    aresta->vm = vm;
    strcpy(aresta->destino, destino);
    return aresta;
}

char* getNomeAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    return a->nome;
}

char* getLdirAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    return a->ldir;
}

char* getLesqAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    return a->lesq;
}

double getCmpAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    return a->cmp;
}

double getVmAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    return a->vm;
}

double getTempoAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    if(a->vm == 0){
        return a->cmp;
    }
    return a->cmp/a->vm;
}

char* getDestinoAresta(Aresta aresta){
    StructAresta* a = (StructAresta*) aresta;
    return a->destino;
}

Aresta copyAresta(Aresta antiga, char destino[]){
    StructAresta* aresta = (StructAresta*)malloc(sizeof(StructAresta));
    StructAresta* a = (StructAresta*) antiga;
    strcpy(aresta->nome,a->nome);
    strcpy(aresta->ldir,a->ldir);
    strcpy(aresta->lesq,a->lesq);
    aresta->cmp = a->cmp;
    aresta->vm = a->vm;
    strcpy(aresta->destino,destino);
    return aresta;
}