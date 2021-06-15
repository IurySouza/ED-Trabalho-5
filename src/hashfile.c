#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashfile.h"
#include "lista.h"

typedef struct {
    char chave[25];
    Item valor;
} ItemStruct;

typedef struct {
    int nRec;
    long int posContinuacao;
    ItemStruct *itens;
} BucketStruct;

typedef struct {
    char filename[70];
    int nbuckets, numRecPerBkt, tamRec, tamCh;
    BucketStruct *buckets;
} HashfileStruct;

Hashfile fcreateHF(char *nome, int nbuckets, int numRecPerBkt, int tamRec, int tamCh) {
    BucketStruct b;
    b.nRec = 0;
    b.posContinuacao = -1;

    FILE* hf = fopen(nome, "wb");

    for(int i = 0; i < nbuckets; i++) {
        fwrite(&b, sizeof(BucketStruct), 1, hf);
    }

    BucketStruct aux;
    fread(&aux, sizeof(BucketStruct), 1, hf);
    printf("%d\n", aux.nRec);
    fclose(hf);

    /*HashfileStruct *h = (HashfileStruct*) malloc(sizeof(HashfileStruct));
    h->buckets = (BucketStruct*) malloc(nbuckets * sizeof(BucketStruct));
    strcpy(h->filename, nome);
    h->nbuckets = nbuckets;
    h->numRecPerBkt = numRecPerBkt;
    h->tamRec = tamRec;
    h->tamCh = tamCh;

    for(int i = 0; i < nbuckets; i++) {
        h->buckets[i].nRec = 0;
        h->buckets[i].posContinuacao = -1;
    }

    FILE* f = fopen(nome, "wb");

    if(f == NULL) {
        printf("Erro ao criar o arquivo hash.\n");
        return NULL;
    }

    fwrite(h, sizeof(*h), 1, f);
    HashfileStruct aux;
    fread(&aux, sizeof(HashfileStruct), 1, f);
    printf("%s\n", aux.filename);
    fclose(f);
    return h;*/
}

/*int getKey(char *chave, int nbuckets) {
    int aux = 0, res;
    int tamanho = strlen(chave);

    for (int i = 0; i < tamanho; i++) {
        aux += chave[i];
    }

    res = aux % nbuckets;
    return res;
}

Hashfile fcreateHF(char *nome, int nbuckets, int numRecPerBkt, int tamRec, int tamCh) {
    FILE* hf = fopen(nome, "wb");

    if(hf == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return NULL;
    }

    Bucket *b = (Bucket*) malloc(sizeof(Bucket));
    b->nbuckets = nbuckets;
    b->numRecPerBkt = numRecPerBkt;
    b->itens = (ItemStruct*) malloc(numRecPerBkt * sizeof(int));
    b->tamRec = tamRec;
    b->tamCh = tamCh;
    b->nRec = 0;
    b->posContinuacao = -1;

    for(int i = 0; i < nbuckets; i++) {
        fwrite(b, sizeof(Bucket), 1, hf);
    }

    fclose(hf);
    return b;
}

Hashfile fopenHF(char *nome) {
    FILE* hf = fopen(nome, "rb+");
    if (hf == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return NULL;
    }
    return hf;
}

int fwriteRec(Hashfile fl, void *buf) {
    FILE* hf = (FILE*) fl;
    ItemStruct *item = (ItemStruct*) buf;

    int chave = getKey()
}

void fcloseHF(Hashfile hf) {
    FILE* f = (FILE*) hf;
    fclose(f);
}*/