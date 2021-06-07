#ifndef __ponto__
#define __ponto__

typedef void* Ponto;
typedef void* PontoInfo;

Ponto createPoint(double x, double y);
// "constructor" da estrutura Ponto

void setX(Ponto ponto, double x);
// atualiza o valor de x

double getX(Ponto ponto);
// retorna o valor de x

void setY(Ponto ponto, double y);
// atualiza o valor de y

double getY(Ponto ponto);
// retorna o valor de y

void desenharPonto(Ponto pont, FILE* svg);
// desenha o ponto no arquivo SVG

void swapPonto(Ponto p1, Ponto p2);
// troca o valor de dois ponteiros Ponto

void atribuirPonto(Ponto p1, Ponto p2);
// atribui p2 a p1

double getPontoDist(Ponto pont, double x, double y);
// retorna a distância entre dois pontos

#endif