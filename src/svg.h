#ifndef __svg__
#define __svg__
#include <stdio.h>
#include "lista.h"
#include "quadtree.h"

FILE* iniciarSvg(char filename[]);
//Inicializa o arquivo e abre a tag svg

void fecharSvg(FILE* svg);
//fecha o arquivo e a tag svg

void desenharSvg(FILE* svg, QuadTree tree[11], Lista l);
//adiciona no arquivo svg as figuras presentes nas trees

#endif