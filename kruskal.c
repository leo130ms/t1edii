#include "kruskal.h"
#include "Matriz.h"
#include <stdio.h>
#include <stdlib.h>

struct aresta{
    int index_1, index_2;//indices que indicam um ponto cada
    double peso;//peso = distancia netre pontos
};

struct mst{
    Aresta** arestas;
    int qtd;
};

Aresta* criaAresta(int index_1, int index_2, double peso){
    Aresta* a = (Aresta*)malloc(sizeof(Aresta));
    a->index_1=index_1;
    a->index_2=index_2;
    a->peso=peso;
    return a;
}

void criaMst(MatrizY* y){
    Mst* mst = (Mst*)malloc(sizeof(Mst));
    mst->qtd = (((y->dim)*((y->dim) - 1))/(2));
    mst->arestas = (Aresta**)malloc(mst->qtd*sizeof(Aresta*));
    int index=0;
    for (int i = 0; i < y->dim; i++)
    {
        for (int j = 0; j < y->dim; j++){
            if (i > j){
                mst->arestas[index] = criaAresta(i, j, y->distancias[i][j]);
                index++;
            }
        }      
    }
}

//fazer um imprime mst para ajudar

//implementar o qsort e ordenar as arestas por peso

//continuar a mst