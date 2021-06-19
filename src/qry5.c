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
#include "casos.h"
#include "sorts.h"

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
    No node = getLast(path);
    AdjList al1 = getAdjList(grafo, getInfo(node));
    for(node = getPrevious(node); node != NULL; node = getPrevious(node)){
        AdjList al2 = getAdjList(grafo, getInfo(node));
        Ponto p1 = getPontoVertice(getVertice(al1));
        Ponto p2 = getPontoVertice(getVertice(al2));
        Aresta a = getArestaByDest(al1, getInfo(node));
        fprintf(txt,"Siga a rua %s", getNomeAresta(a));
        if(getX(p2) > getX(p1) && getY(p1) == getY(p2)){
            fprintf(txt, " na direção oeste\n");
        }
        else if(getX(p1) > getX(p2) && getY(p1) == getY(p2)){
            fprintf(txt, " na direção leste\n");
        }
        else if(getY(p2) > getY(p1) && getX(p1) == getX(p2)){
            fprintf(txt, " na direção norte\n");
        }
        else if(getY(p1) > getY(p2) && getX(p1) == getX(p2)){
            fprintf(txt, " na direção sul\n");
        }
        else{
            fprintf(txt, "\n");
        }
        al1 = al2;
    }
}

void p(FILE* svg, FILE* txt, QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]){
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
    double dmc, dmr;
    Lista pathMC = dijkstra(grafo, idi, idf, &dmc, getCmpAresta);
    Lista pathMR = dijkstra(grafo, idi, idf, &dmr, getTempoAresta);
    if(pathMC != NULL && pathMR != NULL){
        desenharSvg(svg, qt, NULL);
        desenharPath(svg, pathMC, grafo, ++(*idPath), cmc);
        fprintf(txt, "Dijkstra: %s -> %s - Caminho mais curto:\n", idi, idf);
        fprintf(txt,"Distancia total: %lf\n", dmc);
        descreverPath(txt, pathMC, grafo);
        fprintf(txt, "Dijkstra: %s -> %s - Caminho mais rapido:\n", idi, idf);
        fprintf(txt,"Tempo total: %lf\n", dmr);
        desenharPath(svg, pathMR, grafo, ++(*idPath), cmr);
        descreverPath(txt, pathMR, grafo);
        removeList(pathMC,free);
        removeList(pathMR,free);
    }
    else{
        fprintf(txt, "Não existe caminho\n");
    }
}

void pInit(char nomeSaida[], char sufx[], FILE* txt, QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]){
    if(getFirst(grafo) == NULL){
        printf("grafo vazio\n");
        return;
    }
    char *nomeSvg = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    sprintf(nomeSvg,"%s-%s.svg", nomeSaida, sufx);
    FILE* svg = iniciarSvg(nomeSvg);
    p(svg,txt, qt, grafo, inicio, fim, idPath, cmc, cmr);
    fecharSvg(svg);
    free(nomeSvg);
}

void pb(char nomeSaida[], char sufx[], FILE* txt, QuadTree qt[11], Grafo g, Ponto inicio, Ponto fim, int *idPath, char cmc[]){
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
    sprintf(nomeSvg,"%s-%s.svg", nomeSaida, sufx);
    FILE* svg = iniciarSvg(nomeSvg);
    double dmc;
    Lista pathMC = dijkstra(grafo, idi, idf, &dmc, getCmpAresta);
    if(pathMC != NULL){
        desenharSvg(svg, qt, NULL);
        desenharPath(svg, pathMC, grafo, ++(*idPath), cmc);
        fprintf(txt, "Dijkstra: %s -> %s - Caminho mais curto:\n", idi, idf);
        fprintf(txt,"Distancia total: %lf\n", dmc);
        descreverPath(txt, pathMC, grafo);
        removeList(pathMC,free);
    }
    else{
        fprintf(txt, "Não existe caminho\n");
    }
    desalocaGrafo(gnd);
    desalocaGrafo(grafo);
    fecharSvg(svg);
    free(nomeSvg);
}

void sp(char nomeSaida[], char sufx[], FILE* txt, QuadTree qt[11], Grafo grafo, Ponto inicio, Ponto fim, int *idPath, char cmc[], char cmr[]){
    if(getFirst(grafo) == NULL){
        printf("grafo vazio\n");
        return;
    }
    Lista casos = createList();
    Lista env = NULL;
    percorreLarguraQt(qt[8], listInsert, casos);
    if(getTamanho(casos) > 2){
        env = convexHull(casos, getPontoCaso, swapCasos);
    }
    removeList(casos, NULL);
    if(env == NULL){
        return;
    }
    Lista vDentro = createList();
    for(No node = getFirst(grafo); node != NULL; node = getNext(node)){
        Vertice v = getVertice(getInfo(node));
        if(insidePolygon(env, getPontoVertice(v))){
            listInsert(getIdVertice(v), vDentro);
        }
    }
    Grafo aux = createGrafo();
    for(No i = getFirst(grafo); i != NULL; i = getNext(i)){
        AdjList al = getInfo(i);
        if(!strInList(vDentro, getIdVertice(getVertice(al)))){
            adicionarVertice(aux, copyVertice(getVertice(al)));
            for(No j = getFirst(getListaArestas(al)); j != NULL; j = getNext(j)){
                Aresta a = getInfo(j);
                if(!strInList(vDentro, getDestinoAresta(a))){
                    adicionarAresta(aux, getIdVertice(getVertice(al)), copyAresta(a, getDestinoAresta(a)));
                }
            }
        }
    }
    char *nomeSvg = malloc(sizeof(char) * (strlen(nomeSaida) + strlen(sufx) + 6));
    sprintf(nomeSvg,"%s-%s.svg", nomeSaida, sufx);
    FILE* svg = iniciarSvg(nomeSvg);
    p(svg, txt, qt, aux, inicio, fim, idPath, cmc, cmr);
    fprintf(svg,"\t<polygon  fill=\"yellow\" fill-opacity=\"0.6\" points=\"");
    for(No node = getFirst(env); node != NULL; node = getNext(node)){
        Ponto fig = getInfo(node);
        fprintf(svg," %lf,%lf",getX(fig),getY(fig));
    }
    fprintf(svg," \"/>\n");
    removeList(env, NULL);
    removeList(vDentro,NULL);
    desalocaGrafo(aux);
    fecharSvg(svg);
    free(nomeSvg);
}

void bf(FILE* txt, FILE* svg, int max, Grafo grafo, QuadTree qt, HashTable ht, Lista extraFig){
    HashTable norte = iniciaTabela(107);
    HashTable sul = iniciaTabela(107);
    HashTable leste = iniciaTabela(107);
    HashTable oeste = iniciaTabela(107);
    Lista casos = createList();
    percorreLarguraQt(qt, listInsert, casos);
    for(No node = getFirst(casos); node != NULL; node = getNext(node)){
        char *cep = getCEPCaso(getInfo(node));
        char face = getFaceCaso(getInfo(node));
        HashTable aux;
        switch (face){
            case 'N':
                aux = norte;
                break;
            case 'S':
                aux = sul;
                break;
            case 'O':
                aux = oeste;
                break;
            case 'L':
                aux = leste;
                break;
            default:
                break;
        }
        int *total = getValor(aux, cep); 
        if(total == NULL){
            total = malloc(sizeof(int));
            *total = getNCasos(getInfo(node));
            adicionaItem(aux, cep, total);
        }
        else{
            *total += getNCasos(getInfo(node));
        }
    }
    for(No i = getFirst(grafo); i != NULL; i = getNext(i)){
        AdjList al = getInfo(i);
        Ponto p1 = getPontoVertice(getVertice(al));
        HashTable esq;
        HashTable dir;
        char faceE, faceD;
        No j = getFirst(getListaArestas(al));
        while(j != NULL){
            Aresta a = getInfo(j);
            Ponto p2 = getPontoVertice(getVertice(getAdjList(grafo, getDestinoAresta(a))));
            if(getX(p2) > getX(p1) && getY(p1) == getY(p2)){
                dir = sul;
                faceD = 'S';
                esq = norte;
                faceE = 'N';
            }
            else if(getX(p1) > getX(p2) && getY(p1) == getY(p2)){
                dir = norte;
                faceD = 'N';
                esq = sul;
                faceE = 'S';
            }
            else if(getY(p2) > getY(p1) && getX(p1) == getX(p2)){
                dir = oeste;
                faceD = 'O';
                esq = leste;
                faceE = 'L';
            }
            else if(getY(p1) > getY(p2) && getX(p1) == getX(p2)){
                dir = leste;
                faceD = 'L';
                esq = oeste;
                faceE = 'O';
            }
            else{
                j = getNext(j);
                continue;
            }
            int* tEsq = getValor(esq, getLesqAresta(a));
            int* tDir = getValor(dir, getLdirAresta(a));
            if(tEsq != NULL && *tEsq > max){
                No removido = j;
                fprintf(txt, "CEP: %s Face: %c Numero de casos: %d\n", getLesqAresta(a), faceE, *tEsq);
                QuadTree q = getValor(ht, getLesqAresta(a));
                double x1, x2, y1, y2;
                switch (faceE){
                    case 'N':
                        x1 = getX(getPontoQuad(q));
                        x2 = getX(getPontoQuad(q)) + getWQuad(q);
                        y1 = getY(getPontoQuad(q)) + getHQuad(q) + 2;
                        y2 = getY(getPontoQuad(q)) + getHQuad(q) + 2;
                        break;
                    case 'S':
                        x1 = getX(getPontoQuad(q));
                        x2 = getX(getPontoQuad(q)) + getWQuad(q);
                        y1 = getY(getPontoQuad(q)) - 2;
                        y2 = getY(getPontoQuad(q)) - 2;
                        break;
                    case 'O':
                        x1 = getX(getPontoQuad(q)) + getWQuad(q) + 2;
                        x2 = getX(getPontoQuad(q)) + getWQuad(q) + 2;
                        y1 = getY(getPontoQuad(q));
                        y2 = getY(getPontoQuad(q)) + getHQuad(q);
                        break;
                    case 'L':
                        x1 = getX(getPontoQuad(q)) - 2;
                        x2 = getX(getPontoQuad(q)) - 2;
                        y1 = getY(getPontoQuad(q));
                        y2 = getY(getPontoQuad(q)) + getHQuad(q);
                        break;
                    default:
                        break;
                }
                int *tamanho = (int*)malloc(sizeof(int));
                *tamanho = getTamanho(extraFig);
                fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"4\"/>\n",*tamanho, x1, y1, x2, y2);
                listInsert(tamanho, extraFig);
                j = getNext(j);
                removeNode(getListaArestas(al), removido, free);
                continue;
            }
            if(tDir != NULL && *tDir > max){
                No removido = j;
                fprintf(txt, "CEP: %s Face: %c Numero de casos: %d\n", getLdirAresta(a), faceD, *tDir);
                QuadTree q = getValor(ht, getLdirAresta(a));
                double x1, x2, y1, y2;
                switch (faceD){
                    case 'N':
                        x1 = getX(getPontoQuad(q));
                        x2 = getX(getPontoQuad(q)) + getWQuad(q);
                        y1 = getY(getPontoQuad(q)) + getHQuad(q) + 2;
                        y2 = getY(getPontoQuad(q)) + getHQuad(q) + 2;
                        break;
                    case 'S':
                        x1 = getX(getPontoQuad(q));
                        x2 = getX(getPontoQuad(q)) + getWQuad(q);
                        y1 = getY(getPontoQuad(q)) - 2;
                        y2 = getY(getPontoQuad(q)) - 2;
                        break;
                    case 'O':
                        x1 = getX(getPontoQuad(q)) + getWQuad(q) + 2;
                        x2 = getX(getPontoQuad(q)) + getWQuad(q) + 2;
                        y1 = getY(getPontoQuad(q));
                        y2 = getY(getPontoQuad(q)) + getHQuad(q);
                        break;
                    case 'L':
                        x1 = getX(getPontoQuad(q)) - 2;
                        x2 = getX(getPontoQuad(q)) - 2;
                        y1 = getY(getPontoQuad(q));
                        y2 = getY(getPontoQuad(q)) + getHQuad(q);
                        break;
                    default:
                        break;
                }
                int *tamanho = (int*)malloc(sizeof(int));
                *tamanho = getTamanho(extraFig);
                fprintf(svg, "\t<line id=\"%d\" x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"red\" stroke-width=\"4\"/>\n",*tamanho, x1, y1, x2, y2);
                listInsert(tamanho, extraFig);
                j = getNext(j);
                removeNode(getListaArestas(al), removido, free);
                continue;
            }
            j = getNext(j);
        }
    }
    excluirVerticesIsolados(grafo);
    removeList(casos, NULL);
    deletaTabela(norte, 1);
    deletaTabela(sul,1);
    deletaTabela(leste,1);
    deletaTabela(oeste,1);
}