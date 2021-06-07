#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

typedef struct node{
    FilaInfo info;
    struct node *prox;
}NodeStruct;

typedef struct fila{
    NodeStruct *first;
    NodeStruct *last;
}FilaStruct;

Fila createQueue(){
    FilaStruct* fila = (FilaStruct*)malloc(sizeof(FilaStruct));
    fila->first = NULL;
    fila->last = NULL;
    return fila;
}

int queueIsEmpty(Fila Fila){
    FilaStruct* f = (FilaStruct*) Fila;
    return f->first == NULL;
}

void enqueue(FilaInfo info, Fila fila){
    FilaStruct* f = (FilaStruct*) fila;
    NodeStruct* node = (NodeStruct*)malloc(sizeof(NodeStruct));
    node->info = info;
    node->prox = NULL;
    if(f->first == NULL){
        f->first = node;
        f->last = node;
    }
    else{
        f->last->prox = node;
    }
    f->last = node;
}

FilaInfo dequeue(Fila fila){
    FilaStruct* f = (FilaStruct*) fila;
    NodeStruct* node = f->first;
    FilaInfo info = node->info;
    f->first = node->prox;
    if(f->last == node){
        f->last = NULL;
    }
    free(node);
    return info;
}