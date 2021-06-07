#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "svg.h"
#include "verificacao.h"
#include "quadtree.h"
#include "quadra.h"
#include "casos.h"
#include "sorts.h"
#include "ponto.h"
#include "circulo.h"
#include "tabelaEspalhamento.h"

void cv(QuadTree qt[11], int n, char cep[], char face, int num){
    Info fig;
    double x, y, h, w;
    fig = getNodeByIdQt(qt[0],cep);
    if(fig == NULL){
        printf("Quadra nao encontrada\n");
        return;
    }
    else{
        fig = getInfoQt(qt[0], fig);
        x = getX(getPontoQuad(fig));
        y = getY(getPontoQuad(fig));
        h = getHQuad(fig);
        w = getWQuad(fig);
    }
    switch (face){
    case 'n':
        x += num;
        y += h;
        break;
    case 's':
        x += num;
        break;
    case 'l':
        y += num;
        break;
    case 'o':
        x += w;
        y += num;
        break;
    }
    CasosCovid caso = createCasos(x,y,cep,face,num,n);
    insereQt(qt[8], getPontoCaso(caso),caso);
}

void soc(FILE* svg, FILE* txt, QuadTree qt[11], int k, char cep[], char face, int num, Lista extraFig) {
    No node;
    Info fig;
    double x, y, w, h;
    fig = getNodeByIdQt(qt[0],cep);
    if(fig == NULL) {
        printf("Quadra não encontrada.\n");
        return;
    }
    else{
        fig = getInfoQt(qt[0], fig);
        x = getX(getPontoQuad(fig));
        y = getY(getPontoQuad(fig));
        h = getHQuad(fig);
        w = getWQuad(fig);
    }
    switch(face) {
    case 'n':
        x += num;
        y += h;
        break;
    case 's':
        x += num;
        break;
    case 'l':
        y += num;
        break;
    case 'o':
        x += w;
        y += num;
        break;
    }
    Lista l = createList();
    percorreLarguraQt(qt[7],listInsert,l);
    shellSort(l, x, y);
    int* tamanho = (int*)malloc(sizeof(int));;
    *tamanho = getTamanho(extraFig);
    fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"10\" height=\"4\" style=\"fill:blue;stroke-width:2;stroke:white\" />\n",*tamanho, x, y);
    listInsert(tamanho, extraFig);
    int i = 0;
    node = getFirst(l);
    while (i < k && node != NULL) {
        fig = getInfo(node);
        tamanho = (int*)malloc(sizeof(int));
        *tamanho = getTamanho(extraFig);
        fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n",*tamanho, getX(fig), getY(fig), x, y);
        listInsert(tamanho, extraFig);
        fprintf(txt, "x: %lf y: %lf\n", getX(fig), getY(fig));
        node = getNext(node);
        i++;
    }
    removeList(l,NULL);
}

void ci(FILE* svg, FILE* txt, QuadTree qt[11], HashTable ht[4], double x, double y, double r, Lista extraFig){
    No node;
    Info fig;
    int n = 0;
    double d, inc, area;
    char cor[22];
    Ponto ponto;
    Info c;
    c = criarCirculo("0",x,y,r,"5px","none","green");
    insereQt(qt[4],getPontoCirc(c),c);
    Lista aux;
    Lista casos = NULL;
    aux = nosDentroCirculoQt(qt[8],x,y,r);
    if(getFirst(aux) == NULL){
        removeList(aux,NULL);
        printf("Não foi encontrado casos na região\n");
        return;
    }
    c = getValor(ht[3],getCEPCaso(getInfoQt(qt[8],getInfo(getFirst(aux)))));
    if (c == NULL){
        removeList(aux,NULL);
        printf("Densidade não informada na região\n");
        return;
    }
    d = getDensidade(c);
    Lista l = createList();
    for(node = getFirst(aux); node != NULL; node = getNext(node)){
        fig = getInfoQt(qt[8], getInfo(node));
        ponto = getPontoCaso(fig);
        listInsert(ponto,l);
        fprintf(txt,"X : %lf y : %lf\n", getX(ponto),getY(ponto));
        n += getNCasos(fig);
    }
    removeList(aux,NULL);
    if(getTamanho(l) > 2){
        casos = convexHull(l,NULL,swapPonto);
    }
    else{
        printf("Não é possivel formar o poligono, apenas %d endereco(s)\n",getTamanho(l));
    }
    if(casos == NULL){
        casos = l;
    }
    else{
        removeList(l,NULL);
    }
    area = obterArea(casos);
    fprintf(txt,"Numero de casos : %d\nArea : %lf\n",n,area);
    if(area != 0){
        inc = 10 * n/(d * area);
        if(inc < 0.1){
            strcpy(cor, "00FFFF");
            fprintf(txt,"Categoria : A - Livre de Covid\n");
        }
        else if(inc < 5){
            strcpy(cor, "008080");
            fprintf(txt,"Categoria : B - Baixa incidencia\n");
        }
        else if(inc < 10){
            strcpy(cor, "FFFF00");
            fprintf(txt,"Categoria : C - Media incidencia\n");
        }
        else if(inc < 20){
            strcpy(cor, "FF0000");
            fprintf(txt,"Categoria : D - Alta incidencia\n");
        }
        else{
            strcpy(cor, "800080");
            fprintf(txt,"Categoria : E - Catastrofico\n");
            aux = pontosDentroCirculoQt(qt[7], x, y, r);
            if(getFirst(aux) == NULL){
                ponto = centroide(casos,area);
                fprintf(txt,"Necessário novo posto em (%lf,%lf)\n",getX(ponto),getY(ponto));
            }
            removeList(aux, NULL);
        }
    }
    else{
        fprintf(txt,"Não é possivel obter a categoria da região\n");
        removeList(casos,NULL);
        return;
    }
    int* tamanho = (int*)malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    fprintf(svg,"\t<polygon id=\"%d\" fill=\"%s\" fill-opacity=\"0.2\" stroke=\"red\" stroke-width=\"5px\" points=\"",*tamanho, cor);
    listInsert(tamanho, extraFig);
    for(node = getFirst(casos); node != NULL; node = getNext(node)){
        fig = getInfo(node);
        fprintf(svg," %lf,%lf",getX(fig),getY(fig));
    }
    fprintf(svg," \"/>\n");
    removeList(casos,NULL);
}