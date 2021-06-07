#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct node{
    Info info;
    struct node *anterior;
    struct node *proximo;
}NodeStruct;

typedef struct lista{
    NodeStruct *primeiro;
    NodeStruct *ultimo;
    int tamanho;
}ListaStruct;

Lista createList() {
    ListaStruct* lista = (ListaStruct*) malloc(sizeof(ListaStruct));
    lista->primeiro = NULL;
    lista->ultimo = NULL;
    lista->tamanho = 0;
    return lista;
}

void listInsert(Info info, Lista l) {
    ListaStruct* lista = (ListaStruct*) l;
    NodeStruct* node = (NodeStruct*) malloc(sizeof(NodeStruct));
    node->info = info;
    if(lista->primeiro == NULL) {
        node->anterior = NULL;
        lista->primeiro = node;
    } else {
        lista->ultimo->proximo = node;
        node->anterior = lista->ultimo;
    }
    node->proximo = NULL;
    lista->ultimo = node;
    lista->tamanho++;
}


int getTamanho(Lista lista){
    ListaStruct* l = (ListaStruct*) lista;
    return l->tamanho;
}

No getFirst(Lista lista){
    ListaStruct* l = (ListaStruct*) lista;
    return l->primeiro;
}

No getNext(No elemento){
    NodeStruct* node = (NodeStruct*) elemento;
    return node->proximo;
}

Info getInfo(No elemento){
    NodeStruct* node = (NodeStruct*) elemento;
    return node->info;
}

No getLast(Lista lista){
    ListaStruct* l = (ListaStruct*) lista;
    return l->ultimo;
}

No getPrevious(No elemento){
    NodeStruct* node = (NodeStruct*) elemento;
    return node->anterior;
}

void insertAfter(Lista l, No elemento, Info info){
    ListaStruct* lista = (ListaStruct*) l;
    NodeStruct* node = (NodeStruct*) elemento;
    NodeStruct* novo = (NodeStruct*) malloc(sizeof(NodeStruct));
    novo->info = info;
    if(node->proximo != NULL){
        NodeStruct* aux = node->proximo;
        node->proximo = novo;
        novo->anterior = node;
        novo->proximo = aux;
        aux->anterior = novo;
    }else{
        node->proximo = novo;
        novo->proximo = NULL;
        novo->anterior = node;
        lista->ultimo = novo;
    }
    lista->tamanho++;
}

void insertBefore(Lista l, No elemento, Info info){
    ListaStruct* lista = (ListaStruct*) l;
    NodeStruct* node = (NodeStruct*) elemento;
    NodeStruct* novo = (NodeStruct*) malloc(sizeof(NodeStruct));
    novo->info = info;
    if(node->anterior != NULL){
        NodeStruct* aux = node->proximo;
        node->anterior = novo;
        novo->proximo = node;
        novo->anterior = aux;
        aux->proximo = novo;
    }else{
        node->anterior = novo;
        novo->anterior = NULL;
        novo->proximo = node;
        lista->primeiro = novo;
    }
    lista->tamanho++;
}

void removeNode(Lista l, No elemento, void (*desalocar)(void*)){
    ListaStruct* lista = (ListaStruct*) l;
    NodeStruct* node = (NodeStruct*) elemento;
    if(node->anterior == NULL){
        lista->primeiro = node->proximo;
    }else{
        node->anterior->proximo = node->proximo;
    }
    if(node->proximo == NULL){
        lista->ultimo = node->anterior;
    }else{
        node->proximo->anterior = node->anterior;
    }
    if (desalocar != NULL) desalocar(getInfo(node));
    free(node);
    lista->tamanho--;
}

void removeList(Lista l, void (*desalocar)(void*)){
    ListaStruct* lista = (ListaStruct*) l;
    NodeStruct* node = lista->primeiro;
    NodeStruct* aux;
    while(node != NULL){
        aux = node;
        node = node->proximo;
        if(desalocar != NULL){
            desalocar(getInfo(aux));
        }
        free(aux);
    }
    free(lista);
}