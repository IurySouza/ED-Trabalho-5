#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry4.h"
#include "tabelaEspalhamento.h"
#include "ponto.h"
#include "lista.h"
#include "quadtree.h"
#include "endereco.h"
#include "pessoa.h"
#include "Estabelecimento.h"
#include "quadra.h"
#include "svg.h"
#include "verificacao.h"
#include "instrumentoUrbano.h"

void moradores(FILE *txt, QuadTree qt[11], HashTable ht[4], char cep[]){
    Quadra q = getValor(ht[3], cep);
    if(q == NULL){
        fprintf(txt,"Quadra não existe\n");
        return;
    }
    double x = getX(getPontoQuad(q));
    double y = getY(getPontoQuad(q));
    Lista l = nosDentroRetanguloQt(qt[10], x, y, x + getWQuad(q), y + getHQuad(q));
    for(No node = getFirst(l); node != NULL; node = getNext(node)){
        Endereco e = getInfoQt(qt[10], getInfo(node));
        Pessoa p = getValor(ht[2], getCpfEndereco(e));
        fprintf(txt,"Informações pessoais:\nCpf : %s, Nome : %s, Sobrenome : %s, sexo : %c, data de nascimento : %s\n", getCpf(p), getNome(p), getSobrenome(p), getSexo(p), getDataNascimento(p));
        fprintf(txt, "Endereço:\nCEP : %s, face : %c, número: %d, complemento: %s\n\n", cep, getFaceEndereco(e), getNumEndereco(e), getComplementoEndereco(e));
    }
    removeList(l, NULL);
}

void dm(FILE *svg, FILE *txt, HashTable ht[4], char pcpf[], Lista extraFig) {
    char cpf[15], nome[30], sobrenome[30], sexo, nasc[11];
    int *tamanho;
    Info info = getValor(ht[2], pcpf), end;
    Ponto p;

    if (info == NULL) {
        fprintf(txt, "Nenhum morador com o cpf %s\n", pcpf);
        printf("Nenhum morador com esse cpf.\n");
        return;
    }

    end = getValor(ht[0], pcpf);
    p = getPontoEndereco(end);

    strcpy(cpf, getCpf(info));
    strcpy(nome, getNome(info));
    strcpy(sobrenome, getSobrenome(info));
    strcpy(nasc, getDataNascimento(info));
    sexo = getSexo(info);
    fprintf(txt, "Nome completo: %s %s; Cpf: %s; Sexo: %c; Data de nascimento: %s\n", nome, sobrenome, cpf, sexo, nasc);

    tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke: black; stroke-width: 1\" />\n", *tamanho, getX(p), getY(p), getX(p));
    
    tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"0\">Nome completo: %s %s; Cpf: %s; Sexo: %c; Data de nascimento: %s</text>\n", *tamanho, getX(p), nome, sobrenome, cpf, sexo, nasc);
}

void de(FILE *txt, QuadTree qt[11], HashTable ht[4], char cnpj[]) {
    char nome[20], cpf[15], cep[20], codt[10], face;
    int num;
    Info info;
    QtNo aux;

    aux = getNodeByIdQt(qt[9], cnpj);
    if (aux == NULL) {
        fprintf(txt, "Nenhum estabelecimento com o cnpj %s\n", cnpj);
        printf("Estabelecimento nao encontrado.\n");
        return;
    }

    info = getInfoQt(qt[9], aux);
    strcpy(nome, getNomeEstabelecimento(info));
    strcpy(cpf, getCpfEstabelecimento(info));
    strcpy(cep, getCepEstabelecimento(info));
    strcpy(codt, getCodtEstabelecimento(info));
    face = getFaceEstabelecimento(info);
    num = getNumEstabelecimento(info);

    fprintf(txt, "Nome: %s; cpf: %s; cnpj: %s; cep: %s; face: %c; num: %d; codt: %s\n", nome, cpf, cnpj, cep, face, num, (char*)getValor(ht[1], codt));
}

void mud(FILE *svg, FILE *txt, QuadTree qt[11], HashTable ht[4], char cpf[], char cep[], char face, int num, char compl[], Lista extraFig) {
    double x, y;
    int *tamanho;
    Info pes, end;
    Ponto p;
    QtNo aux;
    end = getValor(ht[0], cpf);
    pes = getValor(ht[2], cpf);
    p = getPontoEndereco(end);
    x = getX(p);
    y = getY(p);
    fprintf(txt, "Dados da pessoa:\nNome completo: %s %s; Cpf: %s; Sexo: %c; Data de nascimento: %s\n", getNome(pes), getSobrenome(pes), getCpf(pes), getSexo(pes), getDataNascimento(pes));
    fprintf(txt, "Endereço antigo:\nCep: %s; Face: %c; Num: %d; Complemento: %s\n", getCepEndereco(end), getFaceEndereco(end), getNumEndereco(end), getComplementoEndereco(end));
    fprintf(txt, "Endereço novo:\nCep: %s; Face: %c; Num: %d; Complemento: %s\n", cep, face, num, compl);

    aux = getNodeByIdQt(qt[10], cpf);
    deletaItem(ht[0], cpf, 0);
    end = removeNoQt(qt[10], aux);
    desalocarEndereco(end);
    end = createEndereco(getValor(ht[3], cep), cpf, face, num, compl);
    adicionaItem(ht[0], cpf, end);
    p = getPontoEndereco(end);
    aux = insereQt(qt[10], p, end);

    tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:red; stroke-width: 3\" />\n", *tamanho, x, y, getX(p), getY(p));

    tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"red\" stroke=\"white\" stroke-width=\"3\" />\n", *tamanho, x, y);

    tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"5\" fill=\"blue\" stroke=\"white\" stroke-width=\"3\" />\n", *tamanho, getX(p), getY(p));
}

void dmprbt(QuadTree qt[11], char t, char saida[], char sfx[]){
    int i;
    switch(t) {
    case 'q':
        i = 0;
        break;
    case 'h':
        i = 1;
        break;
    case 's':
        i = 2;
        break;
    case 't':
        i = 3;
        break;
    default:
        printf("Valor inválido (%c)\n", t);
        return;
    }
    char* pathSvg = malloc((6 + strlen(sfx) + strlen(saida))*sizeof(char));
    sprintf(pathSvg,"%s-%s.svg",saida,sfx);
    FILE* svg = iniciarSvg(pathSvg);
    desenharQt(qt[i], svg);
    fecharSvg(svg);
    free(pathSvg);
}

void eplg(FILE *svg, FILE *txt, QuadTree qt[11], HashTable ht[4], char tipo[], double x, double y, double w, double h, Lista extraFig) {
    Info est, pes;
    Ponto p;
    No node;
    QtNo info;
    Lista l;
    int *tamanho;

    l = nosDentroRetanguloQt(qt[9], x, y, x + w, y + h);

    if (tipo != NULL) {
        for (node = getFirst(l); node != NULL; node = getNext(node)) {
            est = getInfo(node);
            info = getInfoQt(qt[9], est);
            p = getPontoEstabelecimento(info);
            if (strcmp(tipo, getCodtEstabelecimento(info)) == 0) {
                pes = getValor(ht[2], getCpfEstabelecimento(info));
                tamanho = (int*) malloc(sizeof(int));
                *tamanho = getTamanho(extraFig);
                listInsert(tamanho, extraFig);
                fprintf(txt, "Nome completo: %s %s; Nome estabelecimento: %s; Cnpj: %s; Cep: %s; Codt: %s; Face: %c; Numero: %d\n", getNome(pes), getSobrenome(pes), getNomeEstabelecimento(info), getCnpjEstabelecimento(info), getCepEstabelecimento(info), getCodtEstabelecimento(info), getFaceEstabelecimento(info), getNumEstabelecimento(info));
                fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"green\" />\n", *tamanho, getX(p), getY(p));
            }
        }
    } else {
        for (node = getFirst(l); node != NULL; node = getNext(node)) {
            est = getInfo(node);
            info = getInfoQt(qt[9], est);
            p = getPontoEstabelecimento(info);
            pes = getValor(ht[2], getCpfEstabelecimento(info));

            tamanho = (int*) malloc(sizeof(int));
            *tamanho = getTamanho(extraFig);
            listInsert(tamanho, extraFig);

            fprintf(txt, "Nome completo: %s %s; Nome estabelecimento: %s; Cnpj: %s; Cep: %s; Codt: %s; Face: %c; Numero: %d\n", getNome(pes), getSobrenome(pes), getNomeEstabelecimento(info), getCnpjEstabelecimento(info), getCepEstabelecimento(info), getCodtEstabelecimento(info), getFaceEstabelecimento(info), getNumEstabelecimento(info));
            fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"5\" stroke=\"black\" stroke-width=\"2\" fill=\"green\" />\n", *tamanho, getX(p), getY(p));
        }
    }

    removeList(l, NULL);
}

void catac(FILE *svg, FILE *txt, QuadTree qt[11], HashTable ht[4], double x, double y, double r, Lista extraFig) {
    Info aux;
    QtNo info;
    No node;
    Ponto p;
    Lista l;

    l = nosDentroCirculoQt(qt[0], x, y, r);
    fprintf(txt, "Quadras:\n");
    for (node = getFirst(l); node != NULL; node = getNext(node)) {
        aux = getInfo(node);
        info = getInfoQt(qt[0], aux);
        p = getPontoQuad(info);
        if (retInternoCirc(getX(p), getY(p), getWQuad(info), getHQuad(info), x, y, r)) {
            fprintf(txt, "Cep: %s; x=%lf; y=%lf; w=%lf; h=%lf; espessura: %s; corb: %s; corp: %s; densidade: %lf\n", getCEP(info), getX(p), getY(p), getWQuad(info), getHQuad(info), getEspessuraQuad(info), getCorbQuad(info), getCorpQuad(info), getDensidade(info));
            deletaItem(ht[3], getCEP(info), 0);
            info = removeNoQt(qt[0], aux);
            desalocaQuadra(info);
        }
    }

    removeList(l, NULL);
    for (int i = 1; i < 4; i++) {
        l = nosDentroCirculoQt(qt[i], x, y, r);
        if (i == 1)
            fprintf(txt, "Hidrantes:\n");
        else if (i == 2)
            fprintf(txt, "Semáforo:\n");
        else
            fprintf(txt, "Torre de rádio:\n");

        for (node = getFirst(l); node != NULL; node = getNext(node)) {
            aux = getInfo(node);
            info = getInfoQt(qt[i], aux);
            p = getPontoIU(info);
            fprintf(txt, "Id: %s; x=%lf; y=%lf; Espessura: %s; corb: %s; corp: %s\n", getIdIU(info), getX(p), getY(p), getEspessuraIU(info), getCorbIU(info), getCorpIU(info));
            info = removeNoQt(qt[i], aux);
            desalocaIU(info);
        }

        removeList(l, NULL);
    }

    l = nosDentroCirculoQt(qt[10], x, y, r);
    fprintf(txt, "Moradores:\n");
    for (node = getFirst(l); node != NULL; node = getNext(node)) {
        aux = getInfo(node);
        info = getInfoQt(qt[10], aux);
        p = getPontoEndereco(info);
        fprintf(txt, "Cpf: %s; Cep: %s; x=%lf; y=%lf; Complemento: %s; Face: %c; Numero: %d\n", getCpfEndereco(info), getCepEndereco(info), getX(p), getY(p), getComplementoEndereco(info), getFaceEndereco(info), getNumEndereco(info));
        deletaItem(ht[2], getCpfEndereco(info), 1);
        info = removeNoQt(qt[10], aux);
        desalocarEndereco(info);
    }

    removeList(l, NULL);
    l = nosDentroCirculoQt(qt[9], x, y, r);
    fprintf(txt, "Estabelecimentos:\n");
    for (node = getFirst(l); node != NULL; node = getNext(node)) {
        aux = getInfo(node);
        info = getInfoQt(qt[9], aux);
        p = getPontoEstabelecimento(info);
        fprintf(txt, "Nome: %s; Cpf: %s; Cnpj: %s; Cep: %s; x=%lf; y=%lf; Face: %c; Numero: %d\n", getNomeEstabelecimento(info), getCpfEstabelecimento(info), getCnpjEstabelecimento(info), getCepEstabelecimento(info), getX(p), getY(p), getFaceEstabelecimento(info), getNumEstabelecimento(info));
        info = removeNoQt(qt[9], aux);
        desalocarEstabelecimento(info);
    }

    removeList(l, NULL);
    int *tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" opacity=\"0.5\" stroke=\"#6C6753\" fill=\"#CCFF00\" />\n", *tamanho, x, y, r);
}