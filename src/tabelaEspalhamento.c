#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaEspalhamento.h"
#include "lista.h"

typedef struct {
    Lista *tabela;
    int tamanho;
} HashTableStruct;

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
    Item item = createItem(chave,valor); 
    listInsert(item, h->tabela[hashKey]);
}

void deletaItem(HashTable t, char chave[], int flag) {
    HashTableStruct *h = (HashTableStruct*) t;
    int hashKey = getChave(chave, h->tamanho);
    void (*desaloca[2])(Item) = {desalocaItem, desalocaValorItem};

    for (No aux = getFirst(h->tabela[hashKey]); aux != NULL; aux = getNext(aux)) {
        Item i =  getInfo(aux);
        if (strcmp(getChaveItem(i), chave) == 0) {
            removeNode(h->tabela[hashKey], aux, desaloca[flag]);
            return;
        }
    }
}

Item getValor(HashTable t, char chave[]) {
    HashTableStruct *h = (HashTableStruct*) t;
    int hashKey = getChave(chave, h->tamanho);

    for (No aux = getFirst(h->tabela[hashKey]); aux != NULL; aux = getNext(aux)) {
        Item i = getInfo(aux);
        if (strcmp(getChaveItem(i), chave) == 0) {
            return getValorItem(i);
        }
    }

    return NULL;
}

void deletaTabela(HashTable t, int flag) {
    HashTableStruct *h = (HashTableStruct*) t;
    void (*desaloca[2])(Item) = {desalocaItem, desalocaValorItem};

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
            Item i = getInfo(aux);
            printf("%s: %s\n", getChaveItem(i), (char*)getValorItem(i));
            aux = getNext(aux);
        }
    }
}

void percorrerTabela(HashTable t, void (*f)(void*, void*), Info extraInf){
    HashTableStruct *h = (HashTableStruct*) t;
    for (int i = 0; i < h->tamanho; i++) {
        No aux = getFirst(h->tabela[i]);
        while (aux != NULL) {
            Item i = getInfo(aux);
            f(i,extraInf);
            aux = getNext(aux);
        }
    }
}