#ifndef __leitura__
#define __leitura__
#include <stdio.h>
#include <string.h>
#include "quadtree.h"
#include "tabelaEspalhamento.h"

char *obterNomeArquivo(char path[]);
//retorno o nome do arquivo sem a extensao e o as pastas dos path

void geo(QuadTree qt[11], HashTable ht[4], char geoArq[], char saida[]);
//le o arquivo .geo e adiciona os elementos nas lsitas

void qry(QuadTree qt[11], HashTable ht[4], char path[], char nomeSaida[]);
//le o arquivo .qry e chama as funcoes que realizam os comandos

void ec(QuadTree qt[11], HashTable ht[4], char ecArq[]);
//le o arquivo .ec e realiza suas funções, inclusive adicionando dados na tabela de espalhamento

void pm(QuadTree qt[11], HashTable ht[4], char pmArq[]);

void tratamento(char path[], char outPath[], char paramGeo[], char paramQry[], char paramEc[], char paramPm[]);
//recebe os parametros do programa, trata os parametros e chama as funcoes geo e qry

#endif