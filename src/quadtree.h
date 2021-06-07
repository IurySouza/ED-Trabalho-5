#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED

#include "lista.h"
#include "ponto.h"

/*
     Implementa uma Point Quadtree. Uma quadtree vazia é criada pela operação criaQt().
     Após a criação, dados associados a coordenadas bidimensionais podem ser inseridos
     por meio da operação insereQt()

     São implementadas várias funções de busca espacial que retornam uma lista contendo
     as chaves, pontos ou nós da árvore que estejam dentro de um dado círculo ou retângulo.

     A árvore pode ser percorrida em largura ou em profundidade (percorreLarguraQt() e percorreProfundidadeQt()).
     Para cada nó visitado é invocada um procedimento que processa a informação contida no nó visitado.
 */

typedef void *QuadTree;
typedef void *QtInfo;
typedef void *QtNo;
typedef char *InfoKey;
typedef void *ExtraInfo;

typedef InfoKey funcGetChave(QtInfo);
typedef void funcVisita(QtInfo,ExtraInfo);

QuadTree criaQt(funcGetChave f);
/**
    Cria e retorna uma quadtree vazia. "f" é uma função
    que retorna a chave de ordenação do dado armazenado.
 */

Lista chavesDentroRetanguloQt(QuadTree qt, double x1, double y1, double x2, double y2);
/**
    Cria uma lista contendo as chaves de ordenação de todas as informações
    cujas coordenas associadas (no momento da inserção) estão dentro do
    retângulo determinado pelo vértices opostos (x1,y1) e (x2,y2).
    Memória é alocada para cada chave armazenada na lista, portanto,
    é seguro (e recomendável) desaloca-la quando a respectiva chave
    não for mais necessária.
    Caso não exista nenhuma informação interna à região especificada,
    retorna uma lista vazia.
    É recomendável que a lista retornada seja desalocada após ser usada.
 */

Lista chavesDentroCirculoQt(QuadTree qt,double x, double y, double r);
/**
    Similar à função chavesDentroRetanguloQt(). Retorna a chave cuja
    coordenada é interna à circunferência de raio r e centro em (x,y).
 */

Lista pontosDentroRetanguloQt(QuadTree qt,double x1, double y1,double x2, double y2);
/**
    Similar à função chavesDentroRetanguloQt().Porém, retorna a coordenada geográfica (Ponto)
    associada á informação. Memória também é alocada para cada ponto retornado na lista.
 */

Lista pontosDentroCirculoQt(QuadTree qt,double x, double y, double r);
/**
    Similar à função pontosDentroRetanguloQt(). Retorna pontos internos
    à circunferência de raio r e centro em (x,y).
 */

Lista nosDentroRetanguloQt(QuadTree qt,double x1, double y1,double x2, double y2);
/**
    Similar à função pontosDentroRetanguloQt(). Retorna apontadores para
    nós da árvore contendo informações cuja coordenada está dentro da
    região de busca.

    A memória relativa aos apontadores da lista não deve ser desalocada.
 */

Lista nosDentroCirculoQt(QuadTree qt,double x, double y, double r);
/**
    Similar à função nosDentroRetanguloQt(). Retorna nós internos
    à circunferência de raio r e centro em (x,y).
 */

void percorreProfundidadeQt(QuadTree qt,funcVisita f,ExtraInfo ei);
/**
    Percorre a árvore em profundidade. Em cada nó visitado invoca
    a função f. Seja pInfo o valor retornado pela operação getInfoQt()
    aplicada ao nó visitado; a invocação de f é da forma:

         f(pInfo,ei)
 */

void percorreLarguraQt(QuadTree qt,funcVisita f,ExtraInfo ei);
/**
    Semelhante a percorreProfundidadeQt. Percorre a árvore em largura.
 */

QtNo insereQt(QuadTree qt,Ponto p, QtInfo pInfo);
/**
    Insere na árvore a informação "pInfo", associada à coordenada referente ao ponto "p".
    Retorna referência ao nó da árvore onde a pInfo foi armazenada.
 */

QtInfo removeNoQt(QuadTree qt,QtNo pNo);
/**
    Remove da árvore o nó referenciiado por "pNo".
    "pNo" deve referenciar um nó válido dentro da árvore.
    Retorna a informação contida na nó removido.
 */

QtNo getNoQt(QuadTree qt, double x, double y);
/**
    Retorna uma referência ao nó da árvore associado à coordenada (x,y).
    Retorna NULL, caso não exista tal nó.
 */

QtInfo getInfoQt(QuadTree qt, QtNo pNo);
/**
    Retorna a informação armazenada na árvore no nó referenciiado por pNo.
    "pNo" deve referenciar um nó válido dentro da árvore.
 */

QtNo getNodeByIdQt(QuadTree qt, char* chave);
/*
* Retorna a informação armazenada na árvore associada a chave
* Entrada: quadtree e chave
* Saida: nó da quadtree
*/
void desalocaQt(QuadTree qt);
/**
    Libera memória alocada pela implementação da árvore. Desaloca apenas memória alocada por criaQt()) e os
    nós da árvore criados por insereQt(). Não desaloca as listas retornadas nas consultas
    espaciais (_*_DentroRetanguloQt() e _*_DentroCirculoQt().

    A função do tipo funcGetChave, parâmetro em criaQt(), poderia alocar dinamicamente memória e retornar
    um apontador para ela. Neste caso, esta memória não será desalocada.
 */

void desenharQt(QuadTree qt, FILE* svg);
/*
* Desenha a quadtree em um arquivo svg
* Entrada: quadtree e arquivo svg
* Saida: void
*/

#endif // QUADTREE_H_INCLUDED
