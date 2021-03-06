#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "lista.h"
#include "vertice.h"
#include "aresta.h"
#include "ponto.h"
#include "tabelaEspalhamento.h"
#include "verificacao.h"

typedef struct adjList{
    Vertice inicio;
    Lista arestas;
}AdjListStruct;

Grafo createGrafo(){
    return createList();
}

Vertice getVertice(AdjList adjList){
    AdjListStruct* al = (AdjListStruct*) adjList;
    return al->inicio;
}

Lista getListaArestas(AdjList adjList){
    AdjListStruct* al = (AdjListStruct*) adjList;
    return al->arestas;
}

AdjList getAdjList(Grafo grafo, char id[]){
    for(No node = getFirst(grafo); node != NULL; node = getNext(node)){
        AdjListStruct* al = getInfo(node);
        if(strcmp(id, getIdVertice(al->inicio)) == 0){
            return al;
        }
    }
    return NULL;
}

Aresta getArestaByDest(AdjList adjList, char id[]){
    AdjListStruct* al = (AdjListStruct*) adjList;
    for(No node = getFirst(al->arestas); node != NULL; node = getNext(node)){
        Aresta a = getInfo(node);
        if(strcmp(id, getDestinoAresta(a)) == 0){
            return a;
        }
    }
    return NULL;
}

void adicionarVertice(Grafo grafo, Vertice vertice){
    AdjListStruct* al = (AdjListStruct*)malloc(sizeof(AdjListStruct));
    al->inicio = vertice;
    al->arestas = createList();
    listInsert(al,grafo);
}

void adicionarAresta(Grafo grafo, char idi[], Aresta aresta){
    AdjListStruct* al = getAdjList(grafo, idi);
    if(al == NULL){
        printf("Vertice não encontrado\n");
        return;
    }
    listInsert(aresta,al->arestas);
}

void desalocaAL(AdjList adjList){
    AdjListStruct* al = (AdjListStruct*) adjList;
    removeList(al->arestas,free);
    desalocaVertice(al->inicio);
    free(adjList);
}

void desalocaGrafo(Grafo grafo){
    removeList(grafo,desalocaAL);
}

void desenharAresta(Grafo grafo, AdjList adjList, Aresta aresta, FILE* svg){
    AdjListStruct* al = (AdjListStruct*) adjList;
    AdjListStruct* aux = getAdjList(grafo,getDestinoAresta(aresta));
    double x1 = getX(getPontoVertice(al->inicio));
    double y1 = getY(getPontoVertice(al->inicio));
    double x2 = getX(getPontoVertice(aux->inicio));
    double y2 = getY(getPontoVertice(aux->inicio));
    fprintf(svg, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:red;stroke-width:2\" />\n", x1,y1,x2,y2);
}

Grafo gerarGrafoNaoDirecionado(Grafo grafo){
    Grafo gnd = createGrafo();
    char *idi, *idf;
    for(No i = getFirst(grafo); i != NULL; i = getNext(i)){
        AdjList al = getInfo(i);
        adicionarVertice(gnd, copyVertice(getVertice(al)));
    }
    for(No i = getFirst(grafo); i != NULL; i = getNext(i)){
        AdjList al = getInfo(i);
        idi = getIdVertice(getVertice(al)); 
        for(No j = getFirst(getListaArestas(al)); j != NULL; j = getNext(j)){
            Aresta aresta = getInfo(j);
            idf = getDestinoAresta(aresta);
            adicionarAresta(gnd, idi, copyAresta(aresta, idf));
            adicionarAresta(gnd, idf, copyAresta(aresta, idi));
        }
    }
    return gnd; 
}

void excluirVerticesIsolados(Grafo g){
    Lista visitados = createList();
    for(No i = getFirst(g); i != NULL; i = getNext(i)){
        AdjListStruct* al = getInfo(i);
        if(getTamanho(al->arestas) && !strInList(visitados, getIdVertice(al->inicio))){
            char* id = malloc(sizeof(char) * (strlen(getIdVertice(al->inicio)) + 1));
            strcpy(id, getIdVertice(al->inicio));
            listInsert(id, visitados);
        }
        for(No j = getFirst(al->arestas); j != NULL; j = getNext(j)){
            char *aux = getDestinoAresta(getInfo(j));
            if(!strInList(visitados, aux)){
                char* id = malloc(sizeof(char) * (strlen(aux) + 1));
                strcpy(id, aux);
                listInsert(id, visitados);
            }
        }
    }
    No node = getFirst(g);
    while (node != NULL){
        AdjListStruct* al = getInfo(node);
        if(!strInList(visitados, getIdVertice(al->inicio))){
            No aux = node;
            node = getNext(node);
            removeNode(g, aux, desalocaAL);
            continue;
        }
        node = getNext(node);
    }
    removeList(visitados, free);
}

Grafo prim(Grafo grafo){
    HashTable visitado = iniciaTabela(1117);
    Grafo agm = createGrafo();
    Vertice vertice;
    int primeiro;
    double menor;
    char flag[9] = "visitado";
    char *idi, *idf;
    Aresta aresta;
    for(No node = getFirst(grafo); node != NULL; node = getNext(node)){
        adicionarVertice(agm, copyVertice(getVertice(getInfo(node))));
    }
    vertice = getVertice(getInfo(getFirst(grafo)));
    adicionaItem(visitado, getIdVertice(vertice), flag);
    while (1){
        primeiro = 1;
        for(No i = getFirst(grafo); i != NULL; i = getNext(i)){
            AdjListStruct* al = getInfo(i);
            vertice = al->inicio;
            if(getValor(visitado, getIdVertice(vertice)) != NULL){
                for(No j = getFirst(al->arestas); j != NULL; j = getNext(j)){
                    if(getValor(visitado, getDestinoAresta(getInfo(j))) == NULL){
                        if(primeiro){
                            idi = getIdVertice(vertice);
                            aresta = getInfo(j);
                            idf = getDestinoAresta(aresta);
                            menor = getCmpAresta(aresta);
                            primeiro = 0;
                        }
                        else if(menor > getCmpAresta(getInfo(j))){
                            idi = getIdVertice(vertice);
                            aresta = getInfo(j);
                            idf = getDestinoAresta(aresta);
                            menor = getCmpAresta(aresta);
                        }
                    }
                }
            }
        }
        if(primeiro){
            break;
        }
        adicionarAresta(agm, idi, copyAresta(aresta, idf));
        adicionarAresta(agm, idf, copyAresta(aresta, idi));
        adicionaItem(visitado, idf, flag);
    }
    deletaTabela(visitado,0);
    return agm;
}

Lista dijkstra(Grafo grafo, char idi[], char idf[], double* distTotal, double getPeso(Aresta aresta)){
    Lista restantes = createList();
    HashTable distancia = iniciaTabela(1117);
    HashTable anterior = iniciaTabela(1117);
    double *aux = malloc(sizeof(double));
    *aux = 0;
    adicionaItem(distancia,idi,aux);
    for(No node = getFirst(grafo); node != NULL; node = getNext(node)){
        listInsert(getIdVertice(getVertice(getInfo(node))), restantes);
    }
    while (1){
        AdjList al = getAdjList(grafo, idi);
        double *dAnt = (double*)getValor(distancia, idi);
        for(No node = getFirst(getListaArestas(al)); node != NULL; node = getNext(node)){
            Aresta aresta = getInfo(node);
            char* idaux = getDestinoAresta(aresta);
            double *dist = getValor(distancia, idaux);
            if(strInList(restantes, idaux)){
                if(dist == NULL){
                    double* distTemp = malloc(sizeof(double)); 
                    *distTemp = getPeso(aresta) + *dAnt;
                    adicionaItem(distancia, idaux, distTemp);
                    char* tempId = malloc(sizeof(char) * (strlen(idi) + 1));
                    strcpy(tempId, idi);
                    adicionaItem(anterior, idaux, tempId);
                }
                else if(*dist > getPeso(aresta) + *dAnt){
                    *dist = getPeso(aresta) + *dAnt;
                    free(getValor(anterior, idaux));
                    char* tempId = malloc(sizeof(char) * (strlen(idi) + 1));
                    strcpy(tempId,idi);
                    mudarValor(anterior, idaux, tempId);
                }
            }
        }
        if(strcmp(idi, idf) == 0){
            *distTotal = *(double*)getValor(distancia, idf);
            break;
        }
        double menor;
        int flag = 1;
        char idAnt[50];
        strcpy(idAnt,idi);
        No node = getFirst(restantes);
        while(node != NULL){
            if(strcmp(getInfo(node), idAnt) == 0){
                No visitado = node;
                node = getNext(node);
                removeNode(restantes, visitado, NULL);
                continue;
            }
            double *valor = getValor(distancia, getInfo(node));
            if(valor != NULL && (flag || menor > *valor)){
                menor = *valor;
                idi = getInfo(node);
                flag = 0;
            }
            node = getNext(node);
        }
        if(flag){
            *distTotal = 0;
            deletaTabela(distancia, 1);
            deletaTabela(anterior, 1);
            removeList(restantes, NULL);
            printf("Não existe caminho\n");
            return NULL;
        }
    }
    Lista path = createList();
    while (idf != NULL){
        char *pathAux = malloc(sizeof(char) * (strlen(idf) + 1));
        strcpy(pathAux, idf);
        listInsert(pathAux, path);
        idf = getValor(anterior, idf);
    }
    deletaTabela(distancia, 1);
    deletaTabela(anterior, 1);
    removeList(restantes, NULL);
    return path;
}

void desenharGrafo(Grafo g, FILE* svg){
    for(No i = getFirst(g); i != NULL; i = getNext(i)){
        AdjList aux = getInfo(i);
        for(No j = getFirst(getListaArestas(aux)); j != NULL; j = getNext(j)){
            desenharAresta(g,aux,getInfo(j),svg);
        }
        desenharVertice(getVertice(aux), svg);
    }
}

void desenharPath(FILE* fileSvg, Lista path, Grafo g, int id, char cor[]){
    Ponto inicial = getPontoVertice(getVertice(getAdjList(g, getInfo(getFirst(path)))));
    Ponto final = getPontoVertice(getVertice(getAdjList(g, getInfo(getFirst(path)))));
    fprintf(fileSvg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"10\" style=\"stroke:magenta;fill:purple;stroke-width:1\"/>", getX(inicial), getY(inicial));
    fprintf(fileSvg, "\n\t<circle cx=\"%lf\" cy=\"%lf\" r=\"10\" style=\"stroke:magenta;fill:purple;stroke-width:1\"/>", getX(final), getY(final));
    fprintf(fileSvg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" >I</text>", getX(inicial), getY(inicial));
    fprintf(fileSvg, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"white\" text-anchor=\"middle\" >F</text>", getX(final), getY(final));
    int primeiro = 1;
    fprintf(fileSvg, "\n\t<path style=\"fill:none;stroke:%s;stroke-width:2px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n\t d=\" M", cor);
    for(No node = getLast(path); node != NULL; node = getPrevious(node)){
        inicial = getPontoVertice(getVertice(getAdjList(g, getInfo(node))));
        if(primeiro == 1){
            fprintf(fileSvg, " %lf %lf", getX(inicial), getY(inicial));
            primeiro = 0;
        }
        else{
            fprintf(fileSvg, "L %lf %lf", getX(inicial), getY(inicial));
        }
    }
    fprintf(fileSvg, "\" id=\"%d\" />", id);
    fprintf(fileSvg, "\n\t<circle cx=\"\" cy=\"\" r=\"5\" fill=\"red\"><animateMotion dur=\"6s\" repeatCount=\"indefinite\"><mpath xlink:href=\"#%d\"/></animateMotion></circle>", id);
}