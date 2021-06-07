#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qry2.h"
#include "instrumentoUrbano.h"
#include "quadtree.h"
#include "svg.h"
#include "verificacao.h"
#include "ponto.h"
#include "lista.h"

void dq(FILE *svg, FILE *txt, QuadTree quadtrees[11], int flag, char id[], double r, Lista extraFig) {
    Info info;
    Ponto p;
    Lista l;
    double x, y, w, h;
    int i;

    switch(id[0]) {
    case 'h':
        i = 1;
        fprintf(txt, "Hidrante:\n");
        break;
    
    case 's':
        i = 2;
        fprintf(txt, "Semaforo:\n");
        break;

    case 'r':
        i = 3;
        fprintf(txt, "Torre de radio:\n");
        break;
    }
    info = getNodeByIdQt(quadtrees[i], id);
    if (info == NULL){
        printf("Instrumento urbano não deletado\n");
        return;
    }
    info = getInfoQt(quadtrees[i], info);
    p = getPontoIU(info);
    x = getX(p);
    y = getY(p);
    
    l = nosDentroCirculoQt(quadtrees[0], x, y, r);
    No node = getFirst(l);
    while (node != NULL) {
        info = getInfoQt(quadtrees[0], getInfo(node));
        p = getPontoQuad(info);
        h = getHQuad(info);
        w = getWQuad(info);
        if(retInternoCirc(getX(p),getY(p),w,h,x,y,r)){
            if (flag) {
                fprintf(svg, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"beige\" stroke=\"olive\" stroke-width=\"%s\" rx=\"20\"/>\n", getX(p), getY(p), w, h, getEspessuraQuad(info));
            }
    
            fprintf(txt, "Quadra removida: %s\n", getCEP(info));
            QtNo aux = getInfo(node);
            info = removeNoQt(quadtrees[0], aux);
            desalocaQuadra(info);
        }
        node = getNext(node);
    }
    int *tamanho = (int*)malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg,"\t<circle id=\"%d\" cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"none\" stroke=\"black\"/>\n", *tamanho, x, y, r);
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"6\" fill=\"none\" stroke=\"red\"/>\n", x, y);
    fprintf(svg,"\t<circle cx=\"%lf\" cy=\"%lf\" r=\"7\" fill=\"none\" stroke=\"blue\"/>\n", x, y);
    removeList(l, NULL);
}

void del(FILE *svg, FILE *txt, QuadTree quadtrees[11], char cepid[], Lista extraFig) {
    Info info;
    Ponto p;
    int i = 0;
    int *tamanho;

    switch (cepid[0]) {
    case 'h':
        i = 1;
        fprintf(txt, "Hidrante:\n");
        break;

    case 's':
        i = 2;
        fprintf(txt, "Semaforo:\n");
        break;

    case 'r':
        i = 3;
        fprintf(txt, "Torre de radio:\n");
        break;

    default:
        fprintf(txt, "Quadra:\n");
    }

    QtNo aux = getNodeByIdQt(quadtrees[i], cepid);
    info = getInfoQt(quadtrees[i], aux);

    if (i == 0) {
        p = getPontoQuad(info);
        fprintf(txt, "CEP: %s x: %lf y: %lf w: %lf h: %lf espessura: %s corb: %s corp: %s\n", cepid, getX(p), getY(p), getWQuad(info), getHQuad(info), getEspessuraQuad(info), getCorbQuad(info), getCorpQuad(info));
        tamanho = (int*)malloc(sizeof(int));
        *tamanho = getTamanho(extraFig);
        listInsert(tamanho, extraFig);
        fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke: black; stroke-width: 1\" />\n", *tamanho, getX(p) + getWQuad(info)/2, getY(p) + getHQuad(info)/2, getX(p) + getWQuad(info)/2);
        tamanho = (int*)malloc(sizeof(int));
        *tamanho = getTamanho(extraFig);
        listInsert(tamanho, extraFig);
        fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"0\">CEP: %s</text>\n", *tamanho, (getX(p) + getWQuad(info)/2) + 3, cepid);
        info = removeNoQt(quadtrees[i], aux);
        desalocaQuadra(info);
    } else {
        p = getPontoIU(info);
        fprintf(txt, "ID: %s x: %lf y: %lf espessura: %s corb: %s corp: %s\n", cepid, getX(p), getY(p), getEspessuraIU(info), getCorbIU(info), getCorpIU(info));
        tamanho = (int*)malloc(sizeof(int));
        *tamanho = getTamanho(extraFig);
        listInsert(tamanho, extraFig);
        fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke: black; stroke-width: 1\" />\n", *tamanho, getX(p), getY(p), getX(p));
        tamanho = (int*)malloc(sizeof(int));
        *tamanho = getTamanho(extraFig);
        listInsert(tamanho, extraFig);
        fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"0\">ID: %s</text>\n", *tamanho, getX(p) + 3, cepid);
        info = removeNoQt(quadtrees[i], aux);
        desalocaIU(info);
    }
}

void cbq(FILE *txt, QuadTree quadtrees[11], double x, double y, double r, char cstrk[]) {
    Info info;
    No node;
    Lista l;

    l = nosDentroCirculoQt(quadtrees[0], x, y, r);
    node = getFirst(l);

    while (node != NULL) {
        info = getInfoQt(quadtrees[0], getInfo(node));
        if(retInternoCirc(getX(getPontoQuad(info)),getY(getPontoQuad(info)),getWQuad(info),getHQuad(info),x,y,r)){
            setCorbQuad(info, cstrk);
            fprintf(txt, "Quadra %s teve a cor da borda alterada\n", getCEP(info));
        }
        node = getNext(node);
    }

    removeList(l, NULL);
}

void crd(FILE *txt, QuadTree quadtrees[11], char cepid[]) {
    Info info;
    Ponto p;
    int i = 0;
    char tipo[15] = "Quadra", id[4] = "CEP";

    switch(cepid[0]) {
    case 'h':
        i = 1;
        strcpy(tipo, "Hidrante");
        strcpy(id, "ID");
        break;
    
    case 's':
        i = 2;
        strcpy(tipo, "Semaforo");
        strcpy(id, "ID");
        break;

    case 'r':
        i = 3;
        strcpy(tipo, "Torre de radio");
        strcpy(id, "ID");
        break;
    }

    info = getNodeByIdQt(quadtrees[i], cepid);
    if(info != NULL){
        info = getInfoQt(quadtrees[i], info);
        if (i == 0) {
            p = getPontoQuad(info);
        } else {
            p = getPontoIU(info);
        }

        fprintf(txt, "%s:\n\t%s: %s  x: %lf y: %lf\n", tipo, id, cepid, getX(p), getY(p));
    }
    else{
        fprintf(txt, "%s %s não encontrado(a)\n", tipo, cepid);
    }
}

void car(FILE *svg, FILE *txt, QuadTree quadtrees[11], double px, double py, double pw, double ph, Lista extraFig) {
    Info info;
    Ponto p;
    No node;
    Lista l;
    double area = 0, a, x, y, w, h;
    int *tamanho;

    l = nosDentroRetanguloQt(quadtrees[0], px, py, px + pw, py + ph);
    node = getFirst(l);

    while (node != NULL) {
        info = getInfoQt(quadtrees[0], getInfo(node));
        p = getPontoQuad(info);
        x = getX(p);
        y = getY(p);
        w = getWQuad(info);
        h = getHQuad(info);
        if(retInternoRet(x,y,w,h,px,py,pw,ph)){
            a = w * h;
            area += a;
            tamanho = (int*)malloc(sizeof(int));
            *tamanho = getTamanho(extraFig);
            listInsert(tamanho, extraFig);
            fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\">Area=%lf</text>\n", *tamanho, x + w/2, y + h/2, a);
            fprintf(txt, "CEP: %s Area: %lf\n", getCEP(info), a);
        }
        node = getNext(node);
    }
    tamanho = (int*)malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<rect id=\"%d\" x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"black\" fill=\"none\"/>\n", *tamanho, px, py, pw, ph);
    tamanho = (int*)malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"0\" style=\"stroke:black;stroke-width:1\"/>\n", *tamanho, px, py, px);
    tamanho = (int*)malloc(sizeof(int));
    *tamanho = getTamanho(extraFig);
    listInsert(tamanho, extraFig);
    fprintf(svg, "\t<text id=\"%d\" x=\"%lf\" y=\"%lf\">Area total= %lf </text>\n", *tamanho, px + 3.0, 0.0,area);
    fprintf(txt, "Area total: %lf\n", area);
    removeList(l, NULL);
}