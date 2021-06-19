#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry5.h"
#include "ponto.h"
#include "tabelaEspalhamento.h"
#include "endereco.h"
#include "quadra.h"
#include "instrumentoUrbano.h"
#include "verificacao.h"
#include "svg.h"

int getIndex(char r[]) {
    char* rAux = malloc((strlen(r) + 1) * sizeof(char));
    rAux = strcpy(rAux, r);
    rAux = rAux + 1;
    int indice = atoi(rAux);
    free(rAux - 1);
    return indice - 1;
}

void m(FILE* svg, char r[], char cpf[], Ponto reg[11], HashTable ht[4], Lista extraFig) {
    int index = getIndex(r);
    Endereco e = getValor(ht[0], cpf);
    Ponto p = getPontoEndereco(e);
    setX(reg[index], getX(p));
    setY(reg[index], getY(p));

    int *tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:black;stroke-width:2\" />\n", *tamanho, getX(p), getY(p), getX(p));
    int *tamanho2 = (int*) malloc(sizeof(int));
    *tamanho2 = getTamanho(extraFig);
    listInsert(tamanho2, extraFig);
    fprintf(svg,"\t<text id=\"%d\" x=\"%lf\" y=\"0\" fill=\"black\">%s</text>\n", *tamanho2, getX(p),r);
}

void e(FILE* svg, char r[], char cep[], char face, int num, Ponto reg[11], HashTable ht[4], Lista extraFig) {
    int index = getIndex(r);
    Quadra q = getValor(ht[3], cep);
    if(q == NULL) {
        return;
    }

    Ponto p = getPontoQuad(q);
    double x = getX(p);
    double y = getY(p);
    double w = getWQuad(q);
    double h = getHQuad(q);

    switch(face) {
    case 'N':
        x += num;
        y += h;
        break;
    
    case 'S':
        x += num;
        break;

    case 'L':
        y += num;
        break;

    case 'O':
        x += w;
        y += num;
        break;
    }

    setX(reg[index], x);
    setY(reg[index], y);

    int *tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:black;stroke-width:2\" />\n", *tamanho, x, y, x);
    int *tamanho2 = (int*) malloc(sizeof(int));
    *tamanho2 = getTamanho(extraFig);
    listInsert(tamanho2, extraFig);
    fprintf(svg,"\t<text id=\"%d\" x=\"%lf\" y=\"0\" fill=\"black\">%s</text>\n", *tamanho2, x,r);
}

void g(FILE* svg, char r[], Ponto reg[11], char id[], QuadTree qt[11], Lista extraFig){
    int index = getIndex(r);
    Info q = NULL;
    for(int i = 1; i < 4; i++){
        No aux = getNodeByIdQt(qt[i], id);
        if(aux != NULL){
            q = getInfoQt(qt[i], aux);
            return;
        }
    }
    if(q == NULL) {
        return;
    }
    Ponto p = getPontoIU(q);
    double x = getX(p);
    double y = getY(p);
    setX(reg[index], x);
    setY(reg[index], y);
    int *tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:black;stroke-width:2\" />\n", *tamanho, x, y, x);
    int *tamanho2 = (int*) malloc(sizeof(int));
    *tamanho2 = getTamanho(extraFig);
    listInsert(tamanho2, extraFig);
    fprintf(svg,"\t<text id=\"%d\" x=\"%lf\" y=\"0\" fill=\"black\">%s</text>\n", *tamanho2, x,r);
}

void xy(FILE* svg, char r[], Ponto reg[11], double x, double y, Lista extraFig) {
    int index = getIndex(r);
    setX(reg[index], x);
    setY(reg[index], y);
    int *tamanho = (int*) malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:black;stroke-width:2\" />\n", *tamanho, x, y, x);
    int *tamanho2 = (int*) malloc(sizeof(int));
    *tamanho2 = getTamanho(extraFig);
    listInsert(tamanho2, extraFig);
    fprintf(svg,"\t<text id=\"%d\" x=\"%lf\" y=\"0\" fill=\"black\">%s</text>\n", *tamanho2, x,r);
}

void ccv(char nomeSaida[], char sufx[], Grafo grafo) {
    Grafo aux = gerarGrafoNaoDirecionado(grafo);
    Grafo arm = prim(aux);
    char *nomeSvg = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    sprintf(nomeSvg, "%s-%s.svg", nomeSaida, sufx);
    FILE* svg = iniciarSvg(nomeSvg);
    desenharGrafo(arm, svg);
    fecharSvg(svg);
    desalocaGrafo(aux);
    desalocaGrafo(arm);
    free(nomeSvg);
}

void descreverPath(FILE* txt, Lista path, Grafo grafo){
   
}

void p(char nomeSaida[], char sufx[], QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]){
    if(getFirst(grafo) == NULL){
        printf("grafo vazio\n");
        return;
    }
    Vertice vi = getVertice(getInfo(getFirst(grafo)));
    Vertice vf = getVertice(getInfo(getFirst(grafo)));
    char idi[50], idf[50];
    strcpy(idi, getIdVertice(vi));
    strcpy(idf, getIdVertice(vf));
    double di = distancia(getX(getPontoVertice(vi)),getY(getPontoVertice(vi)), getX(inicio), getY(inicio));
    double df = distancia(getX(getPontoVertice(vf)),getY(getPontoVertice(vf)), getX(fim), getY(fim));
    for(No node = getNext(getFirst(grafo)); node != NULL; node = getNext(node)){
        Vertice vAux = getVertice(getInfo(node));
        double dAux = distancia(getX(getPontoVertice(vAux)),getY(getPontoVertice(vAux)), getX(inicio), getY(inicio));
        if(di > dAux){
            strcpy(idi, getIdVertice(vAux));
            di = dAux;
        }
        dAux = distancia(getX(getPontoVertice(vAux)),getY(getPontoVertice(vAux)), getX(fim), getY(fim));
        if(df > dAux){
            strcpy(idf, getIdVertice(vAux));
            df = dAux;
        }
    }
    char *nomeSvg = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    char *nomeTxt = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    sprintf(nomeSvg,"%s-%s.svg", nomeSaida, sufx);
    sprintf(nomeTxt,"%s-%s.txt", nomeSaida, sufx);
    FILE* svg = iniciarSvg(nomeSvg);
    FILE* txt = fopen(nomeTxt, "w");
    double dmc, dmr;
    Lista pathMC = dijkstra(grafo, idi, idf, &dmc, getCmpAresta);
    Lista pathMR = dijkstra(grafo, idi, idf, &dmr, getTempoAresta);
    if(pathMC != NULL && pathMR != NULL){
        desenharSvg(svg, qt, NULL);
        desenharPath(svg, pathMC, grafo, ++(*idPath), cmc);
        desenharPath(svg, pathMR, grafo, ++(*idPath), cmr);
        removeList(pathMC,free);
        removeList(pathMR,free);
    }
    else{
        fprintf(txt, "Não existe caminho\n");
    }
    fecharSvg(svg);
    fclose(txt);
    free(nomeSvg);
    free(nomeTxt);
}

void pb(char nomeSaida[], char sufx[], QuadTree qt[11], Grafo g, Ponto inicio, Ponto fim, int *idPath, char cmc[]){
    Grafo gnd = gerarGrafoNaoDirecionado(g);
    Grafo grafo = prim(gnd);    
    Vertice vi = getFirst(getVertice(getFirst(grafo)));
    Vertice vf = getFirst(getVertice(getFirst(grafo)));
    char idi[50], idf[50];
    strcpy(idi, getIdVertice(vi));
    strcpy(idf, getIdVertice(vf));
    double di = distancia(getX(getPontoVertice(vi)),getY(getPontoVertice(vi)), getX(inicio), getY(inicio));
    double df = distancia(getX(getPontoVertice(vf)),getY(getPontoVertice(vf)), getX(fim), getY(fim));
    for(No node = getNext(getFirst(grafo)); node != NULL; node = getNext(node)){
        Vertice vAux = getVertice(getInfo(node));
        double dAux = distancia(getX(getPontoVertice(vAux)),getY(getPontoVertice(vAux)), getX(inicio), getY(inicio));
        if(di > dAux){
            strcpy(idi, getIdVertice(vAux));
            di = dAux;
        }
        dAux = distancia(getX(getPontoVertice(vAux)),getY(getPontoVertice(vAux)), getX(fim), getY(fim));
        if(df > dAux){
            strcpy(idf, getIdVertice(vAux));
            df = dAux;
        }
    }
    char *nomeSvg = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    char *nomeTxt = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    sprintf(nomeSvg,"%s-%s.svg", nomeSaida, sufx);
    sprintf(nomeTxt,"%s-%s.txt", nomeSaida, sufx);
    FILE* svg = iniciarSvg(nomeSvg);
    FILE* txt = fopen(nomeTxt, "w");
    double dmc;
    Lista pathMC = dijkstra(grafo, idi, idf, &dmc, getCmpAresta);
    if(pathMC != NULL){
        desenharSvg(svg, qt, NULL);
        desenharPath(svg, pathMC, grafo, ++(*idPath), cmc);
        //descrever
        removeList(pathMC,NULL);
    }
    else{
        fprintf(txt, "Não existe caminho\n");
    }
    desalocaGrafo(gnd);
    desalocaGrafo(grafo);
    fecharSvg(svg);
    fclose(txt);
    free(nomeSvg);
    free(nomeTxt);
}