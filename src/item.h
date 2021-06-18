#ifndef __ITEM__
#define __ITEM__
#include <stdio.h>
#include "lista.h"
typedef void *Item;

Item createItem(char chave[], Info valor);

Item alocarItem(int tamCh, int tamRec);

char* getChaveItem(Item item);

Info getValorItem(Item item);

void setValorItem(Item item, Info valor);

void desalocaValorItem(Item item);

void desalocaItem(Item item);

#endif