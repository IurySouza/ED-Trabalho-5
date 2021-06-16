#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leituraHash.h"
#include "quadra.h"
#include "regiao.h"
#include "lista.h"
#include "sorts.h"
#include "ponto.h"
#include "casos.h"
#include "Estabelecimento.h"
#include "pessoa.h"
#include "endereco.h"

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