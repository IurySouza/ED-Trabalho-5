#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leituraHash.h"
#include "lista.h"
#include "sorts.h"
#include "ponto.h"
#include "Estabelecimento.h"
#include "pessoa.h"
#include "endereco.h"
#include "item.h"

void listToHashfile(Hashfile hf, Lista l){
    for(No node = getFirst(l); node != NULL; node = getNext(node)){
        fwriteRec(hf, getInfo(node));
    }
}

void listToHashTable(HashTable ht, Lista l){
    for(No node = getFirst(l); node != NULL; node = getNext(node)){
        adicionaItem(ht, getChaveItem(getInfo(node)), getValorItem(getInfo(node)));
    }
}

void ec(QuadTree qt[11], HashTable ht[4], char ecArq[]) {
    char codt[20], auxd[255], cpf[15], cnpj[19], cep[20], face, nome[30], tipo[2], *descricao;
    int num;
    Info info;
    Lista list = createList();
    FILE *ecFile = fopen(ecArq, "r");
    if (ecFile == NULL) {
        printf("\nERRO ao abrir o arquivo .ec\n");
        exit(1);
    }
    while (fscanf(ecFile, "%s", tipo) != EOF) {
        if(strcmp(tipo, "t") == 0) {
            fscanf(ecFile, "%s", codt);
            fgets(auxd, 255, ecFile);
            descricao = (char*) malloc((strlen(auxd) + 1) * sizeof(char));
            strcpy(descricao, auxd);
            adicionaItem(ht[1], codt, descricao);
        } else if(strcmp(tipo, "e") == 0) {
            fscanf(ecFile, "%s %s %s %s %c %d %s", cnpj, cpf, codt, cep, &face, &num, nome);
            info = getValor(ht[3], cep);
            if (info != NULL) {
                listInsert(createEstabelecimento(info, cnpj, cpf, nome, codt, face, num), list);
            }
        }
    }

    balancearQuadTree(qt[9], list, getPontoEstabelecimento, swapEstabelecimento);
    removeList(list, NULL);
    fclose(ecFile);
}

void pm(QuadTree qt[11], HashTable ht[4], char pmArq[]) {
    char cpf[15], nome[20], sobrenome[20], sexo, nasc[11], cep[20], face, compl[10], tipo[2];
    int num;
    Info info;
    Lista list[2];
    list[0] = createList();
    list[1] = createList();
    FILE *pmFile = fopen(pmArq, "r");

    if (pmFile == NULL) {
        printf("ERRO ao abrir o arquivo .pm\n");
        exit(1);
    }

    while (fscanf(pmFile, "%s", tipo) != EOF) {
        if(strcmp(tipo, "p") == 0) {
            fscanf(pmFile, "%s %s %s %c %s", cpf, nome, sobrenome, &sexo, nasc);
            info = criarPessoa(cpf, nome, sobrenome, sexo, nasc);
            adicionaItem(ht[2], cpf, info);
        } else if(strcmp(tipo, "m") == 0) {
            fscanf(pmFile, "%s %s %c %d %s", cpf, cep, &face, &num, compl);
            info = getValor(ht[3], cep);
            if (info != NULL){
                info = createEndereco(info, cpf, face, num, compl);
                listInsert(info, list[0]);
                listInsert(info, list[1]);
            }
        }
    }

    balancearQuadTree(qt[10], list[0], getPontoEndereco, swapEndereco);
    for(No node = getFirst(list[1]); node != NULL; node = getNext(node)) {
        info = getInfo(node);
        adicionaItem(ht[0], getCpfEndereco(info), info);
    }
    removeList(list[0], NULL);
    removeList(list[1], NULL);
    fclose(pmFile);
}

void saveHashfile(HashTable ht[4], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[]){
    char fileEC[80], fileDes[80], fileP[80], fileEnd[80];
    sprintf(fileEC,"%s-ec.dat", nomebase);
    sprintf(fileDes,"%s-des.dat", nomebase);
    sprintf(fileP,"%s-pes.dat", nomebase);
    sprintf(fileEnd,"%s-end.dat", nomebase);
    Hashfile hf[4];
    hf[0] = fcreateHF(fileEC,107,10,getSizeEstabelecimento(),20);
    hf[1] = fcreateHF(fileEnd,107,10,getSizeEndereco(),20);
    hf[2] = fcreateHF(fileDes,107,10,255,20);
    hf[3] = fcreateHF(fileP,107,10,getSizePessoa(),20);
    Lista lAux[4], lEst = createList(), lEnd = createList();
    for(int i = 0; i < 4; i++){
        lAux[i] = createList();
    }
    percorreLarguraQt(estabelecimentos, listInsert, lEst);
    for(No node = getFirst(lEst); node != NULL; node = getNext(node)) {
        listInsert(createItem(getCnpjEstabelecimento(getInfo(node)), getInfo(node)), lAux[0]);
    }
    percorreLarguraQt(enderecos, listInsert, lEnd);
    for(No node = getFirst(lEnd); node != NULL; node = getNext(node)) {
        listInsert(createItem(getCpfEndereco(getInfo(node)), getInfo(node)), lAux[1]);
    }
    for(int i = 2; i < 4; i++){
        percorrerTabela(ht[i - 1], listInsert, lAux[i]);
    }
    for(int i = 0; i < 4; i++){
        if (i != 0) listToHashfile(hf[i], lAux[i]);
        fcloseHF(hf[i]);
    }
    removeList(lEst, NULL);
    removeList(lEnd, NULL);
    removeList(lAux[0], desalocaItem);
    removeList(lAux[1], desalocaItem);
    removeList(lAux[2], NULL);
    removeList(lAux[3], NULL);
}

void readHashfile(HashTable ht[4], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[]){
    char fileEC[80], fileDes[80], fileP[80], fileEnd[80];
    sprintf(fileEC,"%s-ec.dat", nomebase);
    sprintf(fileDes,"%s-des.dat", nomebase);
    sprintf(fileP,"%s-pes.dat", nomebase);
    sprintf(fileEnd,"%s-end.dat", nomebase);
    Hashfile hf[4];
    hf[0] = fopenHF(fileEC);
    hf[1] = fopenHF(fileEnd);
    hf[2] = fopenHF(fileDes);
    hf[3] = fopenHF(fileP);
    Lista lAux[4];
    for(int i = 0; i < 4; i++){
        lAux[i] = createList();
    }
    for(int i = 0; i < 4; i++){
        dumpFileHF(hf[i], lAux[i], listInsert);
        fcloseHF(hf[i]);
    }
    Lista end = createList(), est = createList();
    for(No node = getFirst(lAux[1]); node != NULL; node = getNext(node)){
        Endereco e = getValorItem(getInfo(node));
        setPontoEndereco(e,getXEndereco(e),getYEndereco(e));
        listInsert(e,end);
    }
    for(No node = getFirst(lAux[0]); node != NULL; node = getNext(node)){
        Estabelecimento e = getValorItem(getInfo(node));
        setPontoEstabelecimento(e,getXEstabelecimento(e), getYEstabelecimento(e));
        listInsert(e,est);
    }
    balancearQuadTree(estabelecimentos, est, getPontoEstabelecimento, swapEstabelecimento);
    balancearQuadTree(enderecos, end, getPontoEndereco, swapEndereco);
    for(int i = 1; i < 4; i++){
        listToHashTable(ht[i - 1], lAux[i]);
        removeList(lAux[i], desalocaItem);
    }
    removeList(est, NULL);
    removeList(end, NULL);
    removeList(lAux[0], desalocaItem);
}