#include "kruskal.h"
#include "Matriz.h"
#include "Union.h"
#include <stdio.h>
#include <stdlib.h>

struct aresta{
    int index_1, index_2;//indices que indicam um ponto cada
    double peso;//peso = distancia netre pontos
};

struct mst{
    Aresta* arestas[MAXTAM];
    int qtd;
};

Aresta* criaAresta(int index_1, int index_2, double peso){
    Aresta* a = (Aresta*)malloc(sizeof(Aresta));
    a->index_1=index_1;
    a->index_2=index_2;
    a->peso=peso;
    return a;
}

void liberaAresta (Aresta* a)
{
    free (a);
}

Mst* criaMst(MatrizY* y){
    Mst* mst = (Mst*)malloc(sizeof(Mst));
    mst->qtd = 0;
    int dim = retornaDimensao (y);
    Aresta* arestas [MAXTAM];
    int index = 0;
    for (int i = 0; i < dim; i++)
    {
        for (int j = 0; j < dim; j++){
            if (i > j){
               arestas[index] = criaAresta(i, j, retornaDistancias (y, i, j));
               index++;
               //printf ("index: %d\n", index);      
            }
        }
    }

    Pais* pais = criaPais (index);
    ordenaArestas (arestas, index);

    for (int i = 0; i < index; i++)
    {
        if (!UF_connected (arestas[i]->index_1, arestas[i]->index_2, pais))
        {
            UF_union (arestas[i]->index_1, arestas[i]->index_2, pais);
            mst->arestas[mst->qtd] = arestas[i];
            mst->qtd++;
        }
        else
        {
            liberaAresta (arestas[i]);
        }
    }
    free (pais);
    return mst;
}

void liberaMst (Mst* mst)
{
    for (int i = 0; i < mst->qtd; i++)
        liberaAresta (mst->arestas[i]);
    free (mst);
}

int comparaArestas (const void* x, const void* y){
    Aresta* index_1 = *(Aresta**) x;
    Aresta* index_2 = *(Aresta**) y;
    return (index_1->peso > index_2->peso);
}

void ordenaArestas (Aresta** arestas, int index)
{
    qsort (arestas, index, sizeof(Aresta*), comparaArestas);
}

void ImprimeMst (Mst* mst){
    for (int i = 0; i <mst->qtd; i++)
        printf ("(%d, %d) peso: %lf\n", mst->arestas[i]->index_1, mst->arestas[i]->index_2, mst->arestas[i]->peso);
}

int retornaIndex_1 (Mst* mst, int i){
    return mst->arestas[i]->index_1;
}

int retornaIndex_2 (Mst* mst, int i){
    return mst->arestas[i]->index_2;
}

double retornaPeso (Mst* mst, int i){
    return mst->arestas[i]->peso;
}

void removeKelementos (Mst* mst, int k){
    for (int i = 1; i < k; i++)
    {
        liberaAresta (mst->arestas[mst->qtd - i]);
    }
    mst->qtd -= (k - 1);
}

int retornaQuantidade (Mst* mst){
    return mst->qtd;
}

Aresta* retornaAresta (Mst* mst, int i){
    return mst->arestas[i];
}

//fazer um imprime mst para ajudar

//implementar o qsort e ordenar as arestas por peso

//continuar a mst