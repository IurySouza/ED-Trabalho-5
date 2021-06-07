#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lista.h"
#include "casos.h"
#include "verificacao.h"
#include "ponto.h"
#include "quadtree.h"
#include "pilha.h"
#include "quadra.h"

int orientacao(Ponto a, Ponto b, Ponto c){
    double area = (getX(b) - getX(a)) * (getY(c) - getY(a)) - (getY(b) - getY(a)) * (getX(c) - getX(a));
    if(area < 0){
        return -1; //horario
    }
    if(area > 0){
        return 1; //anti-horario
    }
    return 0; //colinear
}

int comparar(Ponto p0, Ponto a, Ponto b){
    int aux = orientacao(p0,a,b);
    if(aux == 0){
        return distancia(getX(p0),getY(p0),getX(b),getY(b)) < distancia(getX(p0),getY(p0),getX(a),getY(a));
    }
    return aux == 1;
}

No partition(Lista l, No primeiro, No ultimo, Ponto (*getPonto)(Info), void (*swap)(Info, Info)){
    No i = getPrevious(primeiro);
    for(No j = primeiro; j != ultimo; j = getNext(j)){
        if(comparar(getPonto(getInfo(getFirst(l))), getPonto(getInfo(j)), getPonto(getInfo(ultimo)))){ 
            i = (i == NULL) ? primeiro : getNext(i); 
            swap(getInfo(i), getInfo(j));
        }
    }
    i = (i == NULL) ? primeiro : getNext(i); 
    swap(getInfo(i), getInfo(ultimo));
    return i; 
}

void quickSortList(Lista l, No primeiro, No ultimo, Ponto (*getPonto)(Info), void (*swap)(Info, Info)){
    if(ultimo != NULL && primeiro != ultimo && getNext(ultimo) != primeiro){ 
        No p = partition(l, primeiro, ultimo, getPonto, swap);
        quickSortList(l, primeiro,getPrevious(p), getPonto, swap);
        quickSortList(l, getNext(p),ultimo, getPonto, swap);
    }
}


Ponto defaultGetPonto(Ponto info){
    return info;
}

Lista convexHull(Lista list, Ponto (*getPonto)(Info), void (*swap)(Info, Info)){
    if (getPonto == NULL) {
        getPonto = defaultGetPonto;
    }
    if(getTamanho(list) < 3){
        return NULL;
    }
    No primeiro = getFirst(list), i;
    Info aux = getInfo(primeiro);
    Ponto p2, p1;

    for(i = getNext(primeiro); i != NULL; i = getNext(i)){
        p2 = getPonto(getInfo(i));
        p1 = getPonto(aux);
        if(getY(p2) < getY(p1) || (getY(p2) == getY(p1) && getX(p2) < getX(p1))){
            aux = getInfo(i);
        }
    }
    swap(getInfo(primeiro),aux);
    quickSortList(list,getNext(primeiro),getLast(list), getPonto, swap);
    Lista lAux = createList();
    listInsert(getInfo(primeiro),lAux);
    for(i = getNext(getNext(primeiro)); i != NULL; i = getNext(i)){
        p1 = getPonto(getInfo(i));
        p2 = getPonto(getInfo(getPrevious(i)));
        if(orientacao(getPonto(getInfo(primeiro)),p2,p1) != 0){
            listInsert(getInfo(getPrevious(i)), lAux);
        }
    }
    listInsert(getInfo(getLast(list)), lAux);
    int j = getTamanho(lAux);
    if (j < 3){
        removeList(lAux, NULL);
        return NULL;
    }
    Lista envConv = createList();
    for(i = getFirst(lAux), j = 0; j < 3; j++, i = getNext(i)){
        listInsert(getPonto(getInfo(i)), envConv);
    }
    while(i != NULL){
        while (getTamanho(envConv) > 1 && orientacao(getInfo(getPrevious(getLast(envConv))), getInfo(getLast(envConv)), getPonto(getInfo(i))) != 1){
            removeNode(envConv,getLast(envConv), NULL);
        }
        listInsert(getPonto(getInfo(i)), envConv);
        i = getNext(i);
    }
    removeList(lAux, NULL);
    return envConv;
}

Info getIndexInfo(Lista list, int i) {
    Info info;
    No node;
    int j = 0;
    node = getFirst(list);
    while (j < i) {
        node = getNext(node);
        j++;
    }
    info = getInfo(node);
    return info;
}

void shellSort(Lista list, double x, double y) {
    Info info1, info2;
    int i, j, h, tamanho = getTamanho(list);

    for (h = 1; h < tamanho; h = 3 * h + 1);

    while (h > 0) {
        h = (h - 1)/3;
        for (i = h; i < tamanho; i++) {
            info1 = getIndexInfo(list, i);
            Info aux = createPoint(getX(info1), getY(info1));
            j = i;
            while (getPontoDist(getIndexInfo(list, j - h), x, y) > getPontoDist(aux, x, y)) {
                info1 = getIndexInfo(list, j);
                info2 = getIndexInfo(list, j - h);
                atribuirPonto(info1, info2);
                j -= h;
                if (j < h) {
                    break;
                }
            }
            atribuirPonto(getIndexInfo(list, j), aux);
            free(aux);
        }
    }
}

void balancearQuadTree(QuadTree qt, Lista l, Ponto (*getPonto)(void*), void (*swap)(void*, void*)){
    if (getPonto == NULL) {
        getPonto = defaultGetPonto;
    }
    No i,j;
    Lista envCov;
    Pilha pilha = createStack();
    do{
        envCov = convexHull(l,getPonto,swap);
        if(envCov != NULL){
            for(i = getFirst(envCov); i != NULL; i = getNext(i)){
                for(j = getFirst(l); j != NULL; j = getNext(j)){
                    if(getPonto(getInfo(j)) == getInfo(i)){
                        pushStack(pilha, getInfo(j));
                        removeNode(l,j,NULL);
                        break;
                    }
                }
            }
            removeList(envCov,NULL);
        }
        else{
            break;
        }
    }while (getTamanho(l) > 3);
    for(i = getFirst(l); i != NULL; i = getNext(i)){
        pushStack(pilha, getInfo(i));
    }
    while(!stackIsEmpty(pilha)){
        j = popStack(pilha);
        insereQt(qt,getPonto(j),j);
    }
    free(pilha);
}