#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "item.h"

typedef struct item{
    char* chave;
    Info valor;
}ItemStruct;


Item createItem(char chave[], Info valor){
    ItemStruct* i = malloc(sizeof(ItemStruct));
    i->chave = malloc(sizeof(char) * (strlen(chave) + 1));
    strcpy(i->chave,chave);
    i->valor = valor;
    return i;
}

Item alocarItem(int tamCh, int tamRec){
    ItemStruct* i = malloc(sizeof(ItemStruct));
    i->chave = malloc(sizeof(char) * tamCh);
    i->valor = malloc(tamRec);
    return i;
}

char* getChaveItem(Item item){
    ItemStruct* i = (ItemStruct*) item;
    return i->chave;
}

Info getValorItem(Item item){
    ItemStruct* i = (ItemStruct*) item;
    return i->valor;
}

void desalocaValorItem(Item item){
    ItemStruct* i = (ItemStruct*) item;
    free(i->chave);
    free(i->valor);
    free(i);
}

void desalocaItem(Item item){
    ItemStruct* i = (ItemStruct*) item;
    free(i->chave);
    free(i);
}