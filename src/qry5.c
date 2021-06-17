#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry5.h"
#include "ponto.h"
#include "tabelaEspalhamento.h"
#include "endereco.h"
#include "quadra.h"
#include "instrumentoUrbano.h"

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