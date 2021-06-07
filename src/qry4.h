#ifndef __qry4__
#define __qry4__

#include "tabelaEspalhamento.h"
#include "lista.h"
#include "quadtree.h"

void moradores(FILE *txt, QuadTree qt[11], HashTable ht[4], char cep[]);
/*
* Informa os moradores de uma quadra
* Entrada: vetor das quadtrees, arquivo de saida txt, vetor das hashtables e cep da quadra
* Saida: void
*/

void dm(FILE *svg, FILE *txt, HashTable ht[4], char cpf[], Lista extraFig);
/*
* Informa o morador identificado por cpf
* Entrada: arquivos de saida txt e svg, vetor das hashtables, lista de figuras do qry e cpf
* Saida: void
*/

void de(FILE *txt, QuadTree qt[11], HashTable ht[4], char cnpj[]);
/*
* Informa os dados de estabelecimentos comerciais identificado por cnpj
* Entrada: vetor das quadtrees, vetor das hashtables, arquivo de saida txt e cnpj
* Saida: void
*/

void mud(FILE *svg, FILE *txt, QuadTree qt[11], HashTable ht[4], char cpf[], char cep[], char face, int num, char compl[], Lista extraFig);
/*
* Muda o endereço de uma pessoa
* Entrada: vetor das quadtrees, vetor das hashtables, arquivos de saidas txt e svg, lista de figuras do qry e novo endereço
* Saida: void
*/

void dmprbt(QuadTree qt[11], char t, char saida[], char sfx[]);
/*
* desenha uma quadtree no arquivo svg de sufixo sfx 
* Entrada: vetor das quadtrees, char identificando a arvore, nome do arquivo de saida do qry e sufixo
* Saida: void
*/


void eplg(FILE *svg, FILE *txt, QuadTree qt[11], HashTable ht[4], char tipo[], double x, double y, double w, double h, Lista extraFig);
/*
* Informa os estabelecimentos comerciais dentro de uma região retangular
* Entrada: vetor das quadtrees, vetor das hashtables, arquivos de saidas txt e svg, char identificando tipo de estabelecimento, lista de figuras do qry e região retangular
* Saida: void
*/


void catac(FILE *svg, FILE *txt, QuadTree qt[11], HashTable ht[4], double x, double y, double r, Lista extraFig);
/*
* Remove as quadras, IUs, moradores e estabelecimentos comerciais dentro de um circulo
* Entrada: vetor das quadtrees, vetor das hashtables, arquivos de saidas txt e svg, lista de figuras do qry e circulo
*/

#endif