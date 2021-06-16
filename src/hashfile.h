#ifndef __HASHFILE__
#define __HASHFILE__

/*
    Implementa operações para criação, abertura, consulta, escrita, atualização
    de hashfiles.
    Um hashfile contém uma certa quantidade (nbuckets) de buckkets.
    Cada bucket possui uma capacidade fixa para armazenar registros (numRecPerBkt).
    Os registros armazenados no arquivo possuem o mesmo tamanho fixo.

    Os registros são organizados  no arquivo segunda sua chave (única) e
    alfa-numérica.
     */

#include <stdio.h>
#include "tabelaEspalhamento.h"

typedef void *Hashfile;
typedef void (*PrintRecord)(void *, void *);

Hashfile fcreateHF(char *nome,int nbuckets,int numRecPerBkt, int tamRec, int tamCh);
/*
    Cria um novo arquivo segundo o path "nome", com nbuckets buckets,
    contendo "numRecPerBkt" registros cada bucket, cada registro de tamanho
    "tamRec" bytes. A chave do registro deve ser uma string de, no máximo,
    "tamCh" caracteres. Retorna NULL caso não tenha sido possível criar o arquivo.
*/

Hashfile fopenHF(char *nome);
/*
    Abre arquivo existente para escrita e leitura. Retorna NULL, se não foi possível
    abrir o arquivo (provavelmente porque não existe ou está protegido contra escrita).

    (ATENÇÃO: os parâmetros de criação do arquivo NÃO podem ser solicitados novamente.
     Ou seja, estes parâmetros devem ser guardados junto com o arquivo e recuperados
     quando o arquivo for aberto.)
*/


int fwriteRec(Hashfile hf, void *buf);
/*
  Escreve o registro contido em "buf" no arquivo. A chave do registro
  deve estar no início de "buf" e ter, no máximo, o tamanho especificado (tamCh)
  na criação do arquivo. A capacidade de "buf" deve ser aquela especificada na
  criação do arquivo (tamRec).
  Retorna: 0,se ok;  1, se o bucket que abrigaria tal registro já está cheio.
*/

int freadHF(Hashfile hf, char *ch, void *buf);
/*
   Retorna em "buf" o registro cuja chave é "ch". O buffer "buf" deve
   ter a capacidade especificada na criação do arquivo (tamRec).
   Retorna 0, se o registro foi encontrado e lido; 1, caso contrário (neste
   caso o conteúdo de "buf" é não especificado).
*/

void dumpFileHF(Hashfile hf, Info F, PrintRecord p);
/*
    Produz no arquivo-texto "nomeArq" uma representação da
    organização e conteúdo do arquivo "hf". O parâmetro "p"
    é um procedimento que formata o conteúdo do registro
    para impressão (via fprintf).
*/

void fcloseHF(Hashfile hf);
/*
     Fecha o arquivo. O resultado de qualquer operação sobre o arquivo
     fechado é não especificado.
*/

#endif