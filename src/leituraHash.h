#ifndef __leituraHash__
#define __leituraHash__
#include <stdio.h>
#include <string.h>
#include "quadtree.h"
#include "tabelaEspalhamento.h"
#include "hashfile.h"

//le o arquivo .ec e realiza suas funções, inclusive adicionando dados na tabela de espalhamento
void ec(QuadTree qt[11], HashTable ht[4], char ecArq[]);

//le o arquivo .pm e realiza suas funções, inclusive adicionando dados na tabela de espalhamento
void pm(QuadTree qt[11], HashTable ht[4], char pmArq[]);

//salva o conteudo de uma hashfile
void saveHashfile(HashTable ht[4], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[]);

//le o conteudo de uma hashfile
void readHashfile(HashTable ht[4], QuadTree estabelecimentos, QuadTree enderecos, char nomebase[]);

#endif