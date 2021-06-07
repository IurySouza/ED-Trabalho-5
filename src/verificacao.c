#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "retangulo.h"
#include "circulo.h"
#include "quadra.h"
#include "lista.h"
#include "regiao.h"
#include "casos.h"
#include "ponto.h"

double maior(double n1, double n2){
    if(n1 > n2){
        return n1;
    }
    return n2;
}

double menor(double n1, double n2){
    if(n1 > n2){
        return n2;
    }
    return n1;
}

double distancia(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1 - x2,2) + pow(y1 - y2,2));
}

int pontoInternoCirc(double x, double y, double xCirc, double yCirc, double r){
    return distancia(x, y, xCirc, yCirc) <= r;
}

int pontoInternoRet(double x, double y, double xRet, double yRet, double w, double h){
    double dx = x - xRet;
    double dy = y - yRet;
    return dx >= 0 && dx <= w && dy >= 0 && dy <= h;
}

int retInternoCirc(double xRet, double yRet, double w, double h, double x, double y, double r){
    if(distancia(xRet,yRet,x,y) <= r && distancia(xRet + w ,yRet + h,x,y) <= r){
        if(distancia(xRet + w, yRet,x,y) <= r && distancia(xRet, yRet + h,x,y) <= r){
            return 1;
        }
    }
    return 0;
}

int retInternoRet(double x1, double y1, double w1, double h1, double x2, double y2, double w2, double h2){
    return x1 >= x2 && y1 >= y2 && x1 + w1 <= x2 + w2 && y1 + h1 <= y2 + h2;
}


double obterArea(Lista l){
    double a = 0;
    Info i, j;
    No node;
    for(node = getFirst(l); getNext(node) != NULL; node = getNext(node)){
        i = getInfo(node);
        j = getInfo(getNext(node));
        a += getX(i) * getY(j) - getY(i) * getX(j);
    }
    i = getInfo(node);
    j = getInfo(getFirst(l));
    a += getX(i) * getY(j) - getY(i) * getX(j);
    return a/2;
}

Ponto centroide(Lista l, double area){
    double x = 0, y = 0;
    Info i, j;
    No node;
    for(node = getFirst(l); getNext(node) != NULL; node = getNext(node)){
        i = getInfo(node);
        j = getInfo(getNext(node));
        x += (getX(i) + getX(j)) * getX(i) * getY(j) - getY(i) * getX(j);
        y += (getY(i) + getY(j)) * getX(i) * getY(j) - getY(i) * getX(j);
    }
    i = getInfo(node);
    j = getInfo(getFirst(l));
    x += (getX(i) + getX(j)) * getX(i) * getY(j) - getY(i) * getX(j);
    y += (getY(i) + getY(j)) * getX(i) * getY(j) - getY(i) * getX(j);
    return createPoint(x/(6 * area), y/(6 * area));
}