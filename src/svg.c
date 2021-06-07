#include <stdio.h>
#include <stdlib.h>
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "quadra.h"
#include "instrumentoUrbano.h"
#include "ponto.h"
#include "lista.h"
#include "casos.h"
#include "quadtree.h"

FILE* iniciarSvg(char filename[]){
    
    FILE* svg = fopen(filename, "w");
    if(svg == NULL){
        printf("erro ao abrir o arquivo\n");
        exit(1);
    }
    char* corSombra[6] = {"#FFFF00", "#FF9955", "#FF0000", "#FF00CC", "#6600FF", "#A02C5A"};
    fprintf(svg, "<svg>\n\t<defs>\n");
    for(int i = 0; i < 6; i++){
        fprintf(svg, "\t\t<filter id=\"shadow%d\">\n\t\t\t<feDropShadow dx=\"2\" dy=\"2\" stdDeviation=\"0.2\" flood-color=\"%s\"/>\n\t\t</filter>\n", i, corSombra[i]);
    }
    fprintf(svg, "\t</defs>\n");
    return svg;
}

void fecharSvg(FILE* svg){
    fprintf(svg, "</svg>");
    fclose(svg);
}

void desenharSvg(FILE* svg, QuadTree tree[11], Lista l){
    No node;
    void (*desenhar[9])(void*, FILE*) = {desenharQuadra, desenharIU, desenharIU, desenharIU, desenharCirculo, desenharRetangulo, desenharTexto, desenharPonto,  desenharCasos};
    for(int i = 0; i < 9; i++){
        percorreLarguraQt(tree[i],(void (*)(void *, void *))desenhar[i],svg);
    }
    if(l != NULL){
        for(node = getFirst(l); node != NULL; node = getNext(node)){
            fprintf(svg,"\t<use xlink:href=\"#%d\"/>",*(int*)getInfo(node));
        }
    }
}
