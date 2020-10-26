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
    } //Criando o vetor com todas as Arestas


    Pais* pais = criaPais (index); //Vetor usado para fazer as Unions
    ordenaArestas (arestas, index); //Ordenando o vetor de Arestas via Qsort
    mst->arestas = (Aresta**) malloc (sizeof (Aresta*) * index);


    for (int i = 0; i < index; i++)
    {
        if (!UF_connected (arestas[i]->index_1, arestas[i]->index_2, pais)) //Se duas arestas não estiverem conectadas 
        {
            UF_union (arestas[i]->index_1, arestas[i]->index_2, pais); //Une as duas arestas com Weighted Quick Union, usando compressão de caminho

            mst->arestas[mst->qtd] = criaAresta (arestas[i]->index_1, arestas[i]->index_2, arestas[i]->peso); //è criada uma nova aresta

            mst->qtd++; //quantidade de arestas na mst é incrementada
        }
    }

    for (int i = 0; i < index; i++)
        liberaAresta (arestas[i]); //liberando memória
    free (arestas);
    liberaPais (pais);
    return mst; //retorna a estrutura da MST
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
    for (int i = 0; i < (k-1); i++)
    {
        mst->qtd--;
        liberaAresta (mst->arestas[mst->qtd]);
    }
}

int retornaQuantidade (Mst* mst){
    return mst->qtd;
}

Aresta* retornaAresta (Mst* mst, int i){
    return mst->arestas[i];
}