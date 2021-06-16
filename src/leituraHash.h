#ifndef __leituraHash__
#define __leituraHash__
#include <stdio.h>
#include <string.h>
#include "quadtree.h"
#include "tabelaEspalhamento.h"
#include "hashfile.h"

void ec(QuadTree qt[11], HashTable ht[4], char ecArq[]);
//le o arquivo .ec e realiza suas funções, inclusive adicionando dados na tabela de espalhamento

void pm(QuadTree qt[11], HashTable ht[4], char pmArq[]);
//le o arquivo .pm e realiza suas funções, inclusive adicionando dados na tabela de espalhamento

#endif