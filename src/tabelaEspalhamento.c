#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaEspalhamento.h"
#include "lista.h"

typedef struct {
    Lista *tabela;
    int tamanho;
} HashTableStruct;

typedef struct {
    char chave[25];
    Item valor;
} ItemStruct;

void desalocaValor(Item item){
    ItemStruct *i = (ItemStruct*) item;
    free(i->valor);
    free(i);
}


HashTable iniciaTabela(int tamanho) {
    HashTableStruct *h = (HashTableStruct*) malloc(sizeof(HashTableStruct));

    h->tamanho = tamanho;
    h->tabela = (Lista*) malloc(sizeof(Lista) * tamanho);

    for (int i = 0; i < tamanho; i++) {
        h->tabela[i] = createList();
    }

    return h;
}

int getChave(char chave[], int tamanhoHash) {
    int aux = 0, res;
    int tamanho = strlen(chave);

    for (int i = 0; i < tamanho; i++) {
        aux += chave[i];
    }

    res = aux % tamanhoHash;
    return res;
}

void adicionaItem(HashTable t, char chave[], Item valor) {
    HashTableStruct *h = (HashTableStruct*) t;
    int hashKey = getChave(chave, h->tamanho);

    ItemStruct *item = (ItemStruct*) malloc(sizeof(ItemStruct));
    strcpy(item->chave, chave);
    item->valor = valor;

    listInsert(item, h->tabela[hashKey]);
}

void deletaItem(HashTable t, char chave[], int flag) {
    HashTableStruct *h = (HashTableStruct*) t;
    int hashKey = getChave(chave, h->tamanho);
    void (*desaloca[2])(Item) = {free, desalocaValor};

    for (No aux = getFirst(h->tabela[hashKey]); aux != NULL; aux = getNext(aux)) {
        ItemStruct *i = (ItemStruct*) getInfo(aux);
        if (strcmp(i->chave, chave) == 0) {
            removeNode(h->tabela[hashKey], aux, desaloca[flag]);
            return;
        }
    }
}

Item getValor(HashTable t, char chave[]) {
    HashTableStruct *h = (HashTableStruct*) t;
    int hashKey = getChave(chave, h->tamanho);

    for (No aux = getFirst(h->tabela[hashKey]); aux != NULL; aux = getNext(aux)) {
        ItemStruct *i = (ItemStruct*) getInfo(aux);
        if (strcmp(i->chave, chave) == 0) {
            return i->valor;
        }
    }

    return NULL;
}

void deletaTabela(HashTable t, int flag) {
    HashTableStruct *h = (HashTableStruct*) t;
    void (*desaloca[2])(Item) = {free, desalocaValor};

    for (int i = 0; i < h->tamanho; i++) {
        removeList(h->tabela[i], desaloca[flag]);
    }

    if (h->tabela != NULL) {
        free(h->tabela);
    }

    free(h);

    printf("HashTable deletada.\n");
}

void imprimeTabela(HashTable t) {
    HashTableStruct *h = (HashTableStruct*) t;

    for (int i = 0; i < h->tamanho; i++) {
        No aux = getFirst(h->tabela[i]);
        while (aux != NULL) {
            ItemStruct *i = (ItemStruct*) getInfo(aux);
            printf("%s: %s\n", i->chave, (char*)getValor(h, i->chave));
            aux = getNext(aux);
        }
    }
}