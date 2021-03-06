#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "quadra.h"
#include "instrumentoUrbano.h"
#include "regiao.h"
#include "lista.h"
#include "sorts.h"
#include "ponto.h"
#include "qry1.h"
#include "qry2.h"
#include "qry3.h"
#include "qry4.h"
#include "qry5.h"
#include "svg.h"
#include "casos.h"
#include "tabelaEspalhamento.h"
#include "Estabelecimento.h"
#include "pessoa.h"
#include "endereco.h"
#include "hashfile.h"
#include "leituraHash.h"
#include "grafo.h"

char *obterNomeArquivo(char path[]){
    char *aux = strrchr(path,'/');
    if(aux == NULL){
        return strtok(path,".");
    }
	return strtok(&aux[1],".");
}

void geo(QuadTree quadtrees[11], HashTable ht[4], char geoArq[], char saida[]){
    char tipo[4] ,corb[22] ,corp[22], cepid[20], texto[255];
    int i;
    double x, y, w, h, d;
    char cw[10] = "1";
    char rw[10] = "1";
    char eq[10] = "1";
    char eh[10] = "1";
    char es[10] = "1";
    char er[10] = "1";
	char corQP[22] = "blue";
	char corQB[22] = "blue";
	char corHP[22] = "blue";
	char corHB[22] = "blue";
	char corSP[22] = "blue";
	char corSB[22] = "blue";
	char corRP[22] = "blue";
	char corRB[22] = "blue";
    Info info;
    Lista list[10];
    for(i = 0; i < 10; i++){
        list[i] = createList();
    }
    FILE* geo = fopen(geoArq,"r");
    if(geo == NULL){
        printf("erro ao abrir o arquivo\n");
        exit(1);
    }
    while(fscanf(geo,"%s", tipo) != EOF){
        if (strcmp(tipo,"nx") == 0){
            fscanf(geo,"%lf", &x);
            if(fgetc(geo) != '\n'){
                fscanf(geo,"%lf %lf %lf %lf", &x, &y, &h, &w);
            }
        }
        else if(strcmp(tipo,"c") == 0){
            fscanf(geo,"%s %lf %lf %lf %s %s", cepid, &h, &x, &y, corb, corp);
            listInsert(criarCirculo(cepid,x,y,h,cw,corp,corb), list[4]);
        }
        else if(strcmp(tipo,"r") == 0){
            fscanf(geo,"%s %lf %lf %lf %lf %s %s", cepid, &w, &h, &x, &y, corb, corp);
            listInsert(criarRetangulo(cepid,x,y,w,h,rw,corp,corb), list[5]);
        }
        else if(strcmp(tipo,"t") == 0){
            fscanf(geo,"%s %lf %lf %s %s", cepid, &x, &y, corb, corp);
            fgets(texto, 255, geo);
            listInsert(criarTexto(cepid,x,y,corp,corb,texto), list[6]);
        }
        else if(strcmp(tipo,"q") == 0){
            fscanf(geo,"%s %lf %lf %lf %lf", cepid, &x, &y, &w, &h);
            info = criarQuadra(cepid,x,y,eq,w,h,corQP,corQB);
            listInsert(info, list[0]);
            listInsert(info, list[9]);
        }
        else if(strcmp(tipo,"h") == 0){
            fscanf(geo,"%s %lf %lf", cepid, &x, &y);
            listInsert(criarInstrumento(cepid,x,y,eh,corHP,corHB), list[1]);
        }
        else if(strcmp(tipo,"s") == 0){
            fscanf(geo,"%s %lf %lf", cepid, &x, &y);
            listInsert(criarInstrumento(cepid,x,y,es,corSP,corSB), list[2]);
        }
        else if(strcmp(tipo,"rb") == 0){
            fscanf(geo,"%s %lf %lf", cepid, &x, &y);
            listInsert(criarInstrumento(cepid,x,y,er,corRP,corRB), list[3]);
        }
        else if(strcmp(tipo,"cq") == 0){
            fscanf(geo,"%s %s %s", eq, corQP, corQB);
        }
        else if(strcmp(tipo,"ch") == 0){
            fscanf(geo,"%s %s %s", eh, corHP, corHB);
        }
        else if(strcmp(tipo,"cs") == 0){
            fscanf(geo,"%s %s %s", es, corSP, corSB);
        }
        else if(strcmp(tipo,"cr") == 0){
            fscanf(geo,"%s %s %s", er, corRP, corRB);
        }
        else if(strcmp(tipo,"sw") == 0){
            fscanf(geo,"%s %s", cw, rw);
        }
        else if(strcmp(tipo, "ps") == 0) {
            fscanf(geo, "%lf %lf", &x, &y);
            listInsert(createPoint(x, y), list[7]);
        }
        else if(strcmp(tipo, "dd") == 0) {
            fscanf(geo, "%lf %lf %lf %lf %lf", &x, &y, &w, &h, &d);
            listInsert(criarRegiao(x, y, w, h, d), list[8]);
        }
    }
    void* (*getPonto[8])(void*) = {getPontoQuad, getPontoIU, getPontoIU, getPontoIU, getPontoCirc, getPontoRet, getPontoTxt, NULL};
    void (*swap[8])(void*, void*) = {swapQuad, swapIU, swapIU, swapIU, swapCirc, swapRet, swapTxt, swapPonto};
    for(i = 0; i < 8; i++){
        balancearQuadTree(quadtrees[i], list[i], getPonto[i], swap[i]);
    }
    for(No node = getFirst(list[9]); node != NULL; node = getNext(node)) {
        info = getInfo(node);
        adicionaItem(ht[3], getCEP(info), info);
    }
    for(No node = getFirst(list[8]); node != NULL; node = getNext(node)){
        densidadeQuadras(getInfo(node),quadtrees[0]);
    }
    FILE* svg = iniciarSvg(saida);
    desenharSvg(svg,quadtrees,NULL);
    fecharSvg(svg);
    fclose(geo);
    for(i = 0; i < 8; i++){
        removeList(list[i],NULL);
    }
    removeList(list[8],desalocarRegiao);
    removeList(list[9], NULL);
}

void via(Grafo grafo, char viaArq[]) {
    char tipo[4], nome[100], lesq[50], ldir[50], i[100], j[100];
    double x, y;
    FILE *viaFile = fopen(viaArq, "r");
    if (viaFile == NULL) {
        printf("\nERRO ao abrir o arquivo .via\n");
        exit(1);
    }
    while (fscanf(viaFile, "%s", tipo) != EOF) {
        if(strcmp(tipo, "v") == 0) {
            fscanf(viaFile, "%s %lf %lf",nome, &x, &y);
            adicionarVertice(grafo, createVertice(nome,x,y));
        } else if(strcmp(tipo, "e") == 0) {
            fscanf(viaFile, "%s %s %s %s %lf %lf %s",i, j, ldir, lesq, &x, &y, nome);
            adicionarAresta(grafo, i, createAresta(nome, ldir, lesq, x, y , j));
        }
    }
    excluirVerticesIsolados(grafo);
    fclose(viaFile);
}

void qry(QuadTree qt[11], HashTable ht[4], Grafo grafo, char path[], char nomeSaida[]){
    char* pathTxt = malloc((5 + strlen(nomeSaida))*sizeof(char));
    char* pathSvg = malloc((5 + strlen(nomeSaida))*sizeof(char));
    sprintf(pathTxt,"%s.txt",nomeSaida);
    sprintf(pathSvg,"%s.svg",nomeSaida);
    FILE* consulta = fopen(path,"r");
    FILE* saida = fopen(pathTxt,"w");
    FILE* svg = iniciarSvg(pathSvg);
    if(saida == NULL || consulta == NULL){
        printf("erro ao abrir o arquivo\n");
        exit(1);
    }
    Lista extraFig = createList();
    Ponto reg[11];
    for(int i = 0; i < 11; i++) {
        reg[i] = createPoint(1, 1);
    }
    int j,k,i, idPath = 0;
    double x,y,h,w;
    char face, tipo[7], cepid[20], aux[20], corb[22], corp[22], cpf[15], r1[5], r2[5];
    char sufx[20] = "";
    while(fscanf(consulta,"%s",tipo) != EOF){
        if(strcmp(tipo,"o?") == 0){
            fscanf(consulta,"%s %s",cepid,aux);
            fprintf(saida,"%s %s %s\n",tipo,cepid,aux);
            intersecao(svg,saida,qt,cepid,aux,extraFig);
        }
        else if(strcmp(tipo,"i?") == 0){
	        fscanf(consulta,"%s %lf %lf",cepid,&x,&y);
	        fprintf(saida,"%s %s %lf %lf\n",tipo,cepid,x,y);
	        pontoInterno(svg,saida,qt,cepid,x,y,extraFig);
        }
        else if(strcmp(tipo,"pnt") == 0){
	        fscanf(consulta,"%s %s %s",cepid,corb,corp);
	        fprintf(saida,"%s %s %s %s\n",tipo,cepid,corb,corp);
	        pnt(saida,qt,cepid,corb,corp);
        }
        else if(strcmp(tipo,"pnt*") == 0){
            fscanf(consulta,"%d %d %s %s",&j,&k,corb,corp);
            fprintf(saida,"%s %d %d %s %s\n",tipo,j,k,corb,corp);
            for(i = j; i <= k; i++){
                sprintf(cepid,"%d",i);
                pnt(saida,qt,cepid,corb,corp);
            }
        }
        else if(strcmp(tipo,"delf") == 0){
            fscanf(consulta,"%s",cepid);
            fprintf(saida,"%s %s\n",tipo,cepid);
            delf(saida,qt,cepid);
        }
        else if(strcmp(tipo,"delf*") == 0){
            fscanf(consulta,"%d %d",&j,&k);
            fprintf(saida,"%s %d %d\n",tipo,j,k);
            for(i = j; i <= k; i++){
                sprintf(cepid,"%d",i);
                delf(saida,qt,cepid);
            }
        }
        else if(strcmp(tipo,"dq") == 0){
            fscanf(consulta,"%s", cepid);
            if(strcmp(cepid,"#") == 0){
                i = 1;
                fscanf(consulta,"%s %lf",cepid,&h);
                fprintf(saida,"%s # %s %lf",tipo,cepid,h);
            }else{
                i = 0;
                fscanf(consulta,"%lf", &h);
                fprintf(saida,"%s %s %lf\n",tipo,cepid,h);
            }
            dq(svg, saida, qt, i, cepid, h, extraFig);
        }
        else if(strcmp(tipo,"del") == 0){
            fscanf(consulta,"%s", cepid);
            fprintf(saida,"%s %s\n",tipo,cepid);
            del(svg, saida, qt, cepid, extraFig);
        }
        else if(strcmp(tipo,"cbq") == 0){
            fscanf(consulta,"%lf %lf %lf %s", &x, &y ,&h, corb);
            fprintf(saida,"%s %lf %lf %lf %s\n", tipo, x, y ,h, corb);
            cbq(saida, qt, x, y, h, corb);
        }
        else if(strcmp(tipo,"crd?") == 0){
            fscanf(consulta,"%s", cepid);
            fprintf(saida,"%s %s\n",tipo,cepid);
            crd(saida, qt, cepid);
        }
        else if(strcmp(tipo,"car") == 0){
            fscanf(consulta,"%lf %lf %lf %lf", &x, &y ,&w, &h);
            fprintf(saida,"%s %lf %lf %lf %lf\n", tipo, x, y, w, h);
            car(svg, saida, qt, x, y, w, h, extraFig);
        }
        else if(strcmp(tipo,"cv") == 0){
            fscanf(consulta,"%d %s %c %d", &i, cepid ,&face, &j);
            fprintf(saida,"%s %d %s %c %d\n",tipo, i, cepid ,face, j);
            cv(qt,i,cepid,face,j);
        }
        else if(strcmp(tipo,"soc") == 0){
            fscanf(consulta,"%d %s %c %d", &i, cepid ,&face, &j);
            fprintf(saida,"%s %d %s %c %d\n",tipo, i, cepid ,face, j);
            soc(svg,saida,qt,i,cepid,face,grafo,extraFig);
        }
        else if(strcmp(tipo,"ci") == 0){
            fscanf(consulta,"%lf %lf %lf", &x, &y, &h);
            fprintf(saida,"%s %lf %lf %lf\n",tipo, x, y, h);
            ci(svg,saida,qt,ht,x,y,h,extraFig);
        }
        else if(strcmp(tipo, "m?") == 0){
            fscanf(consulta, "%s", cepid);
            fprintf(saida, "%s %s\n", tipo, cepid);
            moradores(saida, qt, ht, cepid);
        }
        else if(strcmp(tipo, "dm?") == 0){
            fscanf(consulta, "%s", cpf);
            fprintf(saida, "%s %s\n", tipo, cpf);
            dm(svg, saida, ht, cpf, extraFig);
        }
        else if(strcmp(tipo, "de?") == 0) {
            fscanf(consulta, "%s", aux);
            fprintf(saida, "%s %s\n", tipo, aux);
            de(saida, qt, ht, aux);
        }
        else if(strcmp(tipo, "mud") == 0) {
            fscanf(consulta, "%s %s %c %d %s", cpf, cepid, &face, &i, aux);
            fprintf(saida, "%s %s %s %c %d %s\n", tipo, cpf, cepid, face, i, aux);
            mud(svg, saida, qt, ht, cpf, cepid, face, i, aux, extraFig);
        }
        else if(strcmp(tipo, "dmprbt") == 0) {
            fscanf(consulta, " %c %s", &face, cepid);
            fprintf(saida, "%s %c %s\n", tipo, face, cepid);
            dmprbt(qt, face, nomeSaida, cepid);
        }
        else if(strcmp(tipo, "eplg?") == 0) {
            fscanf(consulta, "%s", aux);
            if(strcmp(aux, "*") == 0) {
                fscanf(consulta, "%lf %lf %lf %lf", &x, &y, &w, &h);
                fprintf(saida, "%s * %lf %lf %lf %lf\n", tipo, x, y, w, h);
                eplg(svg, saida, qt, ht, NULL, x, y, w, h, extraFig);
            } else {
                fscanf(consulta, "%lf %lf %lf %lf", &x, &y, &w, &h);
                fprintf(saida, "%s %s %lf %lf %lf %lf\n", tipo, aux, x, y, w, h);
                eplg(svg, saida, qt, ht, aux, x, y, w, h, extraFig);
            }
        }
        else if(strcmp(tipo, "catac") == 0) {
            fscanf(consulta, "%lf %lf %lf", &x, &y, &w);
            fprintf(saida, "%s %lf %lf %lf\n", tipo, x, y, w);
            catac(svg, saida, qt, ht, grafo, x, y, w, extraFig);
        }
        else if(strcmp(tipo, "@m?") == 0) {
            fscanf(consulta, "%s %s", r1, cpf);
            fprintf(saida, "%s %s %s\n", tipo, r1, cpf);
            m(svg, r1, cpf, reg, ht, extraFig);
        }
        else if(strcmp(tipo, "@e?") == 0) {
            fscanf(consulta, "%s %s %s %d", r1, cepid, aux, &j);
            fprintf(saida, "%s %s %s %s %d\n", tipo, r1, cepid, aux, j);
            if(strlen(aux) == 1){
                face = aux[0];
            }
            else{    
                face = aux[strlen(aux) - 1];
            }
            e(svg, r1, cepid, face, j, reg, ht, extraFig);
        }
        else if(strcmp(tipo, "@g?") == 0) {
            fscanf(consulta, "%s %s", r1, cepid);
            fprintf(saida, "%s %s %s\n", tipo, r1, cepid);
            g(svg, r1, reg, cepid, qt, extraFig);
        }
        else if(strcmp(tipo, "@xy") == 0) {
            fscanf(consulta, "%s %lf %lf", r1, &x, &y);
            fprintf(saida, "%s %s %lf %lf\n", tipo, r1, x, y);
            xy(svg, r1, reg, x, y, extraFig);
        }
        else if(strcmp(tipo, "ccv") == 0) {
            fscanf(consulta, "%s", aux);
            fprintf(saida, "%s %s\n", tipo, aux);
            ccv(nomeSaida, aux, grafo);
        }
        else if(strcmp(tipo, "p?") == 0) {
            fscanf(consulta, "%s %s %s %s %s", aux, r1, r2, corb, corp);
            fprintf(saida, "%s %s %s %s %s %s\n", tipo, aux, r1, r2, corb, corp);
            if(strcmp(aux,"-") != 0){
                strcpy(sufx, aux);
            }
            pInit(nomeSaida, sufx, saida, qt, grafo, reg[getIndex(r1)], reg[getIndex(r2)], &idPath, corb, corp);
        }
        else if(strcmp(tipo, "bf") == 0) {
            fscanf(consulta, "%d", &i);
            fprintf(saida, "%s %d\n", tipo, i);
            bf(saida, svg, i, grafo, qt[8], ht[3], extraFig);
        }
        else if(strcmp(tipo, "sp?") == 0) {
            fscanf(consulta, "%s %s %s %s %s", aux, r1, r2, corb, corp);
            fprintf(saida, "%s %s %s %s %s %s\n", tipo, aux, r1, r2, corb, corp);
            if(strcmp(aux,"-") != 0){
                strcpy(sufx, aux);
            }
            sp(nomeSaida, sufx, saida, qt, grafo, reg[getIndex(r1)], reg[getIndex(r2)], &idPath, corb, corp);
        }
        else if(strcmp(tipo, "pb?") == 0) {
            fscanf(consulta, "%s %s %s %s", aux, r1, r2, corb);
            fprintf(saida, "%s %s %s %s %s\n", tipo, aux, r1, r2, corb);
            if(strcmp(aux,"-") != 0){
                strcpy(sufx, aux);
            }
            pb(nomeSaida, sufx, saida, qt, grafo, reg[getIndex(r1)], reg[getIndex(r2)], &idPath, corb);
        }
    }
    for(int i = 0; i < 11; i++) {
        free(reg[i]);
    }
    desenharSvg(svg,qt,extraFig);
    fecharSvg(svg);
    fclose(saida);
    fclose(consulta);
    free(pathSvg);
    free(pathTxt);
    removeList(extraFig,free);
}

void tratamento(char path[], char outPath[], char paramGeo[], char paramQry[], char paramEc[], char paramPm[], char nomeHash[], char nomebase[], char paramVia[]){
    char *geoArq = NULL;
    char *qryArq = NULL;
    char *ecArq = NULL;
    char *pmArq = NULL;
    char *nomeGeo = NULL;
    char *nomeQry = NULL;
    char *saida = NULL;
    char *saidaGeo = NULL;
    char *saidaQry = NULL;
    char *hashFileName = NULL;
    char *viaArq = NULL;
    int i;
    if (path != NULL) {
        if(path[strlen(path) - 1] != '/'){
            geoArq = (char *)malloc((strlen(paramGeo)+strlen(path)+2)*sizeof(char));
    	    sprintf(geoArq,"%s/%s",path,paramGeo);
            if (paramQry != NULL){
                qryArq = (char *)malloc((strlen(paramQry)+strlen(path)+2)*sizeof(char));
                sprintf(qryArq,"%s/%s",path,paramQry);
            }
            if (paramEc != NULL){
                ecArq = (char *)malloc((strlen(paramEc)+strlen(path)+2)*sizeof(char));
                sprintf(ecArq,"%s/%s",path,paramEc);
            }
            if (paramPm != NULL){
                pmArq = (char *)malloc((strlen(paramPm)+strlen(path)+2)*sizeof(char));
                sprintf(pmArq,"%s/%s",path,paramPm);
            }
            if (paramVia != NULL){
                viaArq = (char *)malloc((strlen(paramVia)+strlen(path)+2)*sizeof(char));
                sprintf(viaArq,"%s/%s",path,paramVia);
            }
        }
		else{
            geoArq = (char *)malloc((strlen(paramGeo)+strlen(path)+1)*sizeof(char));
    	    sprintf(geoArq,"%s%s",path,paramGeo);
            if (paramQry != NULL){
                qryArq = (char *)malloc((strlen(paramQry)+strlen(path)+1)*sizeof(char));
                sprintf(qryArq,"%s%s",path,paramQry);
            }
            if (paramEc != NULL){
                ecArq = (char *)malloc((strlen(paramEc)+strlen(path)+1)*sizeof(char));
                sprintf(ecArq,"%s%s",path,paramEc);
            }
            if (paramPm != NULL){
                pmArq = (char *)malloc((strlen(paramPm)+strlen(path)+1)*sizeof(char));
                sprintf(pmArq,"%s%s",path,paramPm);
            }
            if (paramVia != NULL){
                viaArq = (char *)malloc((strlen(paramVia)+strlen(path)+1)*sizeof(char));
                sprintf(viaArq,"%s%s",path,paramVia);
            }
        }
	} else {
		geoArq = (char *)malloc((strlen(paramGeo)+1)*sizeof(char));
    	strcpy(geoArq, paramGeo);
        if(paramQry != NULL){
            qryArq = (char *)malloc((strlen(paramQry)+1)*sizeof(char));
            strcpy(qryArq, paramQry);
        }
        if(paramEc != NULL){
            qryArq = (char *)malloc((strlen(paramEc)+1)*sizeof(char));
            strcpy(ecArq, paramEc);
        }
        if(paramPm != NULL){
            pmArq = (char *)malloc((strlen(paramPm)+1)*sizeof(char));
            strcpy(pmArq, paramPm);
        }
        if(paramVia != NULL){
            viaArq = (char *)malloc((strlen(paramVia)+1)*sizeof(char));
            strcpy(viaArq, paramVia);
        }
	}
    nomeGeo = obterNomeArquivo(paramGeo);
    if (outPath[strlen(outPath) - 1] == '/'){
        saida = (char*)malloc((strlen(nomeGeo) + strlen(outPath) + 1)*sizeof(char));
        sprintf(saida,"%s%s",outPath,nomeGeo);
    }
    else{
        saida = (char*)malloc((strlen(nomeGeo) + strlen(outPath) + 2)*sizeof(char));
        sprintf(saida,"%s/%s",outPath,nomeGeo);void DesidadeQuadras(Regiao reg, QuadTree quadras);
    }
    saidaGeo = (char*)malloc((strlen(saida) + 5)*sizeof(char));
    sprintf(saidaGeo,"%s.svg",saida);
    char* (*getId[11])(void*) = {getCEP, getIdIU, getIdIU, getIdIU, getIdCirc, getIdRet, getIdTxt, NULL, getCEPCaso, getCnpjEstabelecimento, getCpfEndereco};
    QuadTree trees[11];
    for(i = 0; i < 11; i++){
        trees[i] = criaQt(getId[i]);
    }
    HashTable ht[4];
    for (i = 0; i < 4; i++) {
        ht[i] = iniciaTabela(1117);
    }
    Grafo grafo = createGrafo();
    geo(trees, ht, geoArq, saidaGeo);
    if(nomebase != NULL){
        readHashfile(ht, trees[9], trees[10], nomebase);
    }
    else{
        if(paramEc != NULL){
            ec(trees, ht, ecArq);
        }
        if(paramPm != NULL){
            pm(trees, ht, pmArq);
        }
    }
    if(viaArq != NULL){
        via(grafo, viaArq);
        free(viaArq);
    }
    if (paramQry != NULL){
        nomeQry = obterNomeArquivo(paramQry);
        saidaQry = (char*)malloc((strlen(nomeQry) + strlen(saida) + 2)*sizeof(char));
        sprintf(saidaQry,"%s-%s",saida,nomeQry);
        qry(trees, ht, grafo, qryArq, saidaQry);
        free(saidaQry);
        free(qryArq); 
    }
    if(nomeHash != NULL){
        hashFileName = obterNomeArquivo(nomeHash);
        saveHashfile(ht, trees[9], trees[10], hashFileName);
    }
    if(paramEc != NULL){
        free(ecArq);
    }
    if(paramPm != NULL){
        free(pmArq);
    }
    free(geoArq);
    free(saida);
    free(saidaGeo);
    deletaTabela(ht[0], 0);
    deletaTabela(ht[1], 1);
    deletaTabela(ht[2], 1);
    deletaTabela(ht[3], 0);
    for(i = 0; i < 11; i++){
        desalocaQt(trees[i]);
    }
    desalocaGrafo(grafo);
}