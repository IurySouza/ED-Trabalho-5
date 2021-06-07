#ifndef __fila__
#define __fila__

typedef void* Fila;
typedef void* FilaInfo;

Fila createQueue();
// "constructor" da estrutura fila

int queueIsEmpty(Fila fila);
// retorna 1 se a fila estiver vazia e 0 existir pelo menos um elemento

void enqueue(FilaInfo info, Fila fila);
// adiciona um elemento da  fila

FilaInfo dequeue(Fila fila);
// remove o primeiro elemento da fila e retorna a informação armazenada nele

#endif