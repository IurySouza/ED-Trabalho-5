#ifndef __pilha__
#define __pilha__

typedef void* Pilha;
typedef void* PilhaInfo;

Pilha createStack();
// "constructor" da estrutura pilha

int stackIsEmpty(Pilha pilha);
// retorna 1 se a pilha estiver vazia e 0 existir pelo menos um elemento

void pushStack(Pilha pilha, PilhaInfo info);
// adiciona um elemento na pilha

PilhaInfo popStack(Pilha pilha);
// remove o último elemento da pilha e retorna a informação armazenada nele

#endif