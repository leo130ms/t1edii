#include "kruskal.h"
#include "Matriz.h"
#include "Union.h"
#include "Ponto.h"
#include <stdio.h>
#include <math.h>
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

void liberaAresta (Aresta* a)
{
    free (a);
}

Mst* criaMst(MatrizY* y){
    Mst* mst = (Mst*)malloc(sizeof(Mst));
    mst->qtd = 0;
    int dim = retornaDimensao (y);
    Aresta** arestas;
    arestas = (Aresta**) malloc (sizeof (Aresta*)* (dim * dim));
    int index = 0;
    for (int i = 1; i < dim; i++)
    {
        for (int j = 0; j < i; j++){
           // if (i > j){
               arestas[index] = criaAresta(i, j, retornaDistancias (y, i, j));
              // printf ("index: %d\n", index);   
               index++;   
          //  }
        }
    }


    Pais* pais = criaPais (index);
    ordenaArestas (arestas, index);
    mst->arestas = (Aresta**) malloc (sizeof (Aresta*) * index);

    //printf ("%d %d\n", index, (dim * dim));

    for (int i = 0; i < index; i++)
    {
        if (!UF_connected (arestas[i]->index_1, arestas[i]->index_2, pais))
        {
            UF_union (arestas[i]->index_1, arestas[i]->index_2, pais);
            //printf ("UF_union OK\n\n\n\n\n\n");

            mst->arestas[mst->qtd] = criaAresta (arestas[i]->index_1, arestas[i]->index_2, arestas[i]->peso);
            //printf ("mst.arestas OK\n\n\n\n\n\n");

            mst->qtd++;
            //printf ("mst->qtd OK\n\n\n\n\n\n");
        }
    }

    for (int i = 0; i < index; i++)
        liberaAresta (arestas[i]);
    free (arestas);
    free (pais);
    return mst;
}

void liberaMst (Mst* mst)
{
    for (int i = 0; i < mst->qtd; i++)
        liberaAresta (mst->arestas[i]);
    free (mst->arestas);
    free (mst);
}

int comparaArestas (const void* x, const void* y){
    return (*(Aresta**) x)->peso > (*(Aresta**) y)->peso;
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