#ifndef KRUSKAL_H
#define KRUSKAL_H
#include "Matriz.h"
#include "Union.h"


typedef struct aresta Aresta;
typedef struct mst Mst;

Aresta* criaAresta(int index_1, int index_2, double peso);

Mst* criaMst(MatrizY* y);

void ordenaArestas (Aresta** arestas, int index);

void ImprimeMst (Mst* mst);

int retornaQuantidade (Mst* mst);

Aresta* retornaAresta (Mst* mst, int i);

int retornaIndex_1 (Mst* mst, int i);

int retornaIndex_2 (Mst* mst, int i);

void removeKelementos (Mst* mst, int k);

double retornaPeso (Mst* mst, int i);

#endif 