#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadtree.h"
#include "lista.h"
#include "ponto.h"
#include "fila.h"
#include "verificacao.h"
#define nw 0
#define ne 1
#define sw 2
#define se 3
#define dx 250
#define dy 250

typedef struct node{
    struct node *children[4];
    struct node *parent;
    Ponto ponto;
    QtInfo info;
}NodeStruct;

typedef struct quadtree{
    NodeStruct* root;
    char* (*fun)(QtInfo);
}QuadtreeStruct;



void desalocaNos(NodeStruct* node){
    if(node == NULL){
        return;
    }
    for(int i = 0; i < 4; i++){
        desalocaNos(node->children[i]);
    }
    if(node->ponto != node->info){
        free(node->ponto);
    }
    free(node->info);
    free(node);
}

void insere(QuadtreeStruct* quadtree, NodeStruct* node){
    NodeStruct* aux = quadtree->root;
    node->parent = NULL;
    for(int i = 0; i < 4; i++){
        node->children[i] = NULL;
    }
    if(aux == NULL){
        quadtree->root = node;
        return;
    }
    do{
        Ponto pAux = aux->ponto;
        Ponto p = node->ponto;
        if(getX(p) >= getX(pAux)){
            if(getY(p) >= getY(pAux)){
                if(aux->children[ne] == NULL){
                    aux->children[ne] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[ne];
                }
            }
            else{
                if(aux->children[se] == NULL){
                    aux->children[se] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[se];
                }
            }
        }
        else{
            if(getY(p) >= getY(pAux)){
                if(aux->children[nw] == NULL){
                    aux->children[nw] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[nw];
                }
            }
            else{
                if(aux->children[sw] == NULL){
                    aux->children[sw] = node;
                    node->parent = aux;
                }
                else{
                    aux = aux->children[sw];
                }
            }
        }
    }while(node->parent == NULL);
}

Ponto getPontoQt(QuadTree qt, QtNo pNo){
    NodeStruct* node = (NodeStruct*) pNo;
    qt = qt;
    return node->ponto;
}

QtNo getNodeById(QuadTree qt, QtNo no, char* chave){
    NodeStruct* node = (NodeStruct*) no;
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    if(strcmp(quadtree->fun(getInfoQt(qt, node)), chave) == 0){
        return node;
    }
    QtNo aux;
    for(int i = 0; i < 4; i++){
        if(node->children[i] != NULL){
            aux = getNodeById(qt,node->children[i],chave);
            if(aux != NULL){
                return aux;
            }
        }
    }
    return NULL;
}


void dentroRetanguloQt(QuadTree qt, NodeStruct* node, Lista l, double x1, double y1, double x2, double y2, void* (*fun)(void*, void*)){
    if(node == NULL){
        return;
    }
    if(pontoInternoRet(getX(node->ponto), getY(node->ponto), x1, y1, x2 - x1, y2 - y1)){
        if(fun != NULL){
            listInsert(fun(qt, node),l);
        }
        else{
            listInsert(node,l);
        }
        
    }
    for(int i = 0; i < 4; i++){
        dentroRetanguloQt(qt, node->children[i], l, x1, y1, x2, y2, fun);
    }
}

void dentroCirculoQt(QuadTree qt, NodeStruct* node, Lista l, double x, double y, double r, void* (*fun)(void*, void*)){
    if(node == NULL){
        return;
    }
    if(pontoInternoCirc(getX(node->ponto), getY(node->ponto), x, y, r)){
        if(fun != NULL){
            listInsert(fun(qt, node),l);
        }
        else{
            listInsert(node,l);
        }
        
    }
    for(int i = 0; i < 4; i++){
        dentroCirculoQt(qt, node->children[i], l, x, y, r, fun);
    }
}

char* getChaveQt(QuadTree qt, QtNo pNo){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = (NodeStruct*) pNo;
    return quadtree->fun(getInfoQt(quadtree, node));
}

void percorreProfundidade(QuadTree qt, NodeStruct* node, funcVisita f,ExtraInfo ei){
    if(node == NULL){
        return;
    }
    f(getInfoQt(qt, node),ei);
    for(int i = 0; i < 4; i++){
        percorreProfundidade(qt, node->children[i],f,ei);
    }
}

QuadTree criaQt(funcGetChave f){
    QuadtreeStruct* qt = (QuadtreeStruct*)malloc(sizeof(QuadtreeStruct));
    qt->root = NULL;
    qt->fun = f;
    return qt;
}

Lista chavesDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    Lista l = createList();
    dentroRetanguloQt(qt, node, l, x1, y1, x2, y2, (void*(*)(void*, void*))getChaveQt);
    return l;

}

Lista chavesDentroCirculoQt(QuadTree qt,double x, double y, double r){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    Lista l = createList();
    dentroCirculoQt(qt, node, l, x, y, r, (void*(*)(void*, void*))getChaveQt);
    return l;
}

Lista pontosDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    Lista l = createList();
    dentroRetanguloQt(qt, node, l, x1, y1, x2, y2, getPontoQt);
    return l;

}

Lista pontosDentroCirculoQt(QuadTree qt,double x, double y, double r){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    Lista l = createList();
    dentroCirculoQt(qt, node, l, x, y, r, getPontoQt);
    return l;
}

Lista nosDentroCirculoQt(QuadTree qt,double x, double y, double r){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    Lista l = createList();
    dentroCirculoQt(qt, node, l, x, y, r, NULL);
    return l;
}

Lista nosDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    Lista l = createList();
    dentroRetanguloQt(qt, node, l, x1, y1, x2, y2, NULL);
    return l;

}

void percorreProfundidadeQt(QuadTree qt,funcVisita f,ExtraInfo ei){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = quadtree->root;
    percorreProfundidade(qt, node, f, ei);
}

void percorreLarguraQt(QuadTree qt,funcVisita f,ExtraInfo ei){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* aux;
    if(quadtree->root == NULL){
        return;
    }
    Fila fila = createQueue();
    enqueue(quadtree->root, fila);
    do{
        aux = dequeue(fila);
        for(int i = 0; i < 4; i++){
            if(aux->children[i] != NULL){
                enqueue(aux->children[i], fila);
            }
        }
        f(getInfoQt(quadtree, aux),ei);
    }while(!queueIsEmpty(fila));
    free(fila);
}

QtNo insereQt(QuadTree qt,Ponto p, QtInfo pInfo){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = (NodeStruct*)malloc(sizeof(NodeStruct));
    node->ponto = p;
    node->info = pInfo;
    insere(quadtree,node);
    return node;
}

QtInfo removeNoQt(QuadTree qt,QtNo pNo){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* node = (NodeStruct*) pNo;
    NodeStruct* aux;
    int i;
    QtInfo info;
    Fila fila = createQueue();
    if(node->parent == NULL){
        for(i = 0; i < 4; i++){
            if(node->children[i] != NULL){
                enqueue(node->children[i], fila);
            }
        }
        quadtree->root = NULL;
    }
    else{
        for(i = 0; i < 4; i++){
            if(node->parent->children[i] == node){
                node->parent->children[i] = NULL;
                break;
            }
        }
        for(i = 0; i < 4; i++){
            if(node->children[i] != NULL){
                if(node->parent->children[i] == NULL){
                    node->parent->children[i] = node->children[i];
                    node->children[i]->parent = node->parent;
                }
                else{
                    enqueue(node->children[i], fila);
                }
            }
        }
    }
    while(!queueIsEmpty(fila)){
        aux = dequeue(fila);
        for(i = 0; i < 4; i++){
            if(aux->children[i] != NULL){
                enqueue(aux->children[i], fila);
            }
        }
        insere(quadtree,aux);
    }
    info = getInfoQt(quadtree, node);
    free(node);
    free(fila);
    return info;
}

QtNo getNoQt(QuadTree qt, double x, double y){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    NodeStruct* aux = quadtree->root;
    Ponto p;
    while (aux != NULL){
        p = aux->ponto;
        if(x == getX(p) && y == getY(p)){
            return aux;
        }
        if(x > getX(p)){
            if(y > getY(p)){
                aux = aux->children[ne];
            }
            else{
                aux = aux->children[se];
            }
        }
        else{
            if(y > getY(p)){
                aux = aux->children[nw];
            }
            else{
                aux = aux->children[sw];
            }
        }
    }
    return NULL;
}

QtInfo getInfoQt(QuadTree qt, QtNo pNo){
    NodeStruct* node = (NodeStruct*) pNo;
    qt = qt;
    return node->info;
}

QtNo getNodeByIdQt(QuadTree qt, char* chave){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    if(quadtree->root == NULL){
        return NULL;
    }
    return getNodeById(qt, quadtree->root, chave);
}

void desalocaQt(QuadTree qt){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    desalocaNos(quadtree->root);
    free(qt);
}

void desenhaNoQt(QuadtreeStruct* qt, NodeStruct* no, FILE* svg, double *x, double y, Lista ant){
    if(no == NULL){
        double aux = *x;
        if(ant != NULL){
            listInsert(createPoint(aux,y - 10), ant);
        }
        fprintf(svg, "<circle cx='%lf' cy='%lf' r='10' fill='black' stroke='black' />\n",aux, y - 10);
        *x += dx;
        return;
    }
    Lista atual = createList();
    for(int i = 0; i < 2; i++){
        desenhaNoQt(qt, no->children[i], svg, x, y + dy, atual);
    }
    double aux = *x;
    char cor[5];
    if(ant != NULL){
        listInsert(createPoint(aux,y - 10), ant);
        strcpy(cor,"blue");
    }
    else{
        strcpy(cor,"red");
    }
    fprintf(svg, "<rect x='%lf' y='%lf' width='240' height='12' fill='none' stroke='%s' />\n",aux, y - 10, cor);
    fprintf(svg, "\t<text x=\"%lf\" y=\"%lf\">%s: %lf,%lf</text>\n",aux, y, qt->fun(getInfoQt(qt, no)), getX(no->ponto), getY(no->ponto));
    *x += dx;
    for(int i = 2; i < 4; i++){
        desenhaNoQt(qt, no->children[i], svg, x, y + dy, atual);
    }
    for(No node = getFirst(atual); node != NULL; node = getNext(node)){
        fprintf(svg, "\t<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke: blue; stroke-width: 1\" />\n", aux, y + 2, getX(getInfo(node)), getY(getInfo(node)));
    }
    removeList(atual,free);
}

void desenharQt(QuadTree qt, FILE* svg){
    QuadtreeStruct* quadtree = (QuadtreeStruct*) qt;
    double *x = (double*)malloc(sizeof(double));
    *x = 0;
    desenhaNoQt(quadtree, quadtree->root, svg, x, dy, NULL);
    free(x);
}