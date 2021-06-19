#ifndef __ITEM__
#define __ITEM__
#include <stdio.h>
#include "lista.h"

typedef void *Item;

//"constructor" da estrutura Item
Item createItem(char chave[], Info valor);

//Retorna uma estrutura item com seu atributos alocado de acordo com os valores passados, porem não inicializados
Item alocarItem(int tamCh, int tamRec);

//Retorna a chave de um item
char* getChaveItem(Item item);

//Retorna o valor armazenado em um item
Info getValorItem(Item item);

//Altera o valor de um item
void setValorItem(Item item, Info valor);

//Desaloca o item e valor armazenado nele
void desalocaValorItem(Item item);

//Desaloca o item, porém não o valor armazenado nele
void desalocaItem(Item item);

#endif