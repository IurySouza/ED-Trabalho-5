#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct node{
    PilhaInfo info;
    struct node *anterior;
}NodeStruct;

typedef struct pilha{
    NodeStruct *top;
}PilhaStruct;

Pilha createStack(){
    PilhaStruct* pilha = (PilhaStruct*)malloc(sizeof(PilhaStruct));
    pilha->top = NULL;
    return pilha;
}

int stackIsEmpty(Pilha pilha){
    PilhaStruct* p = (PilhaStruct*) pilha;
    return p->top == NULL;
}

void pushStack(Pilha pilha, PilhaInfo info){
    PilhaStruct* p = (PilhaStruct*) pilha;
    NodeStruct* node = (NodeStruct*)malloc(sizeof(NodeStruct));
    node->info = info;
    node->anterior = p->top;
    p->top = node;
}

PilhaInfo popStack(Pilha pilha){
    PilhaStruct* p = (PilhaStruct*) pilha;
    NodeStruct* node = p->top;
    PilhaInfo info = node->info;
    p->top = node->anterior;
    free(node);
    return info;
}