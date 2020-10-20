#include "Matriz.h"
#include "kruskal.h"
#include "Union.h"
#include <stdlib.h>
#include <string.h>

struct matrizy {
    int dim;
    double** distancias;
};

MatrizY* criaMatriz (int dim)
{
    MatrizY* y = (MatrizY*) malloc (sizeof(MatrizY));
    y->dim = dim;
    y->distancias = (double**) malloc (sizeof(double*)* dim);
    for (int i = 0; i < dim; i++)
    {
        y->distancias[i] = (double*) malloc (sizeof(double)* dim);
    }
    return y;
}

int retornaDimensao (MatrizY* y){
    return y->dim;
}

double retornaDistancias (MatrizY* y, int i, int j){
    return y->distancias[i][j];
}

void imprimePontosnoArquivo (Mst* mst, Ponto** pontos, int numPontos)
{
    FILE* saida = fopen ("saida.txt", "w");
    Pais* pais = criaPais (numPontos);
    char* string_saida[MAXTAM];
    int numStrings = 0;
    for (int i = 0; i < retornaQuantidade (mst); i++)
    {
        int index_1 = retornaIndex_1 (mst, i);
        int index_2 = retornaIndex_2 (mst, i);
        
    }
    free (pais);
    fclose (saida);
}

MatrizY* constroiMatriz (FILE* f, int k)
{
    int numPontos = 0;
    int dimensao = 0;
    char c = fgetc(f);

    while (c != '\n')
    {
        if (c == ',') dimensao++;
        c = fgetc (f);
    }

    while (c != EOF)
    {
        if (c == '\n') numPontos++;
        c = fgetc(f); 
    }

    rewind(f);
    Ponto* pontos[numPontos];

    for (int i = 0; i <numPontos; i++)
    {
        char nome [MAXTAM];
        double coordenadas[dimensao];

        fscanf (f, "%[^,],", nome);
        //printf ("%s ->", nome);

        for (int j = 0; j < dimensao; j++)
        {
            fscanf (f, "%lf,", &coordenadas[j]);
           // printf ("%lf\n", coordenadas[j]);
        }
        pontos[i] = criaponto (nome, dimensao, coordenadas);
    }

    fclose (f);
    //printf ("%d\n", dimensao);
    //printf ("%d\n", numPontos);

    MatrizY* matriz = criaMatriz (numPontos); 
 
    for (int i = 0; i < numPontos; i++)
    {
        for (int j = 0; j < numPontos; j++)
        {
            if (i > j)
            matriz->distancias[i][j] = distanciaEuclidiana (pontos[i], pontos[j]);
            else 
            matriz->distancias[i][j] = -1;
        }
    }


    Mst* mst = criaMst (matriz);
    removeKelementos (mst, k);
    ImprimeMst (mst);
    //imprimePontosnoArquivo (mst, pontos, numPontos);
    liberaMst (mst);
    destroiPontos (pontos, numPontos);
    //imprimePontos (pontos, numPontos);
    return matriz;  
}

void imprimeMatriz (MatrizY* matriz)
{
    for (int i = 0; i < matriz->dim; i++)
    {
    printf ("\n");
        for (int j = 0; j < matriz->dim; j++)
            if (i > j)
                printf ("%lf ", matriz->distancias[i][j]);
    }
}

void liberaMatriz (MatrizY* matriz)
{
    for (int i = 0; i < matriz->dim; i++)
    {
        free (matriz->distancias[i]);
    }
    free (matriz->distancias);
    free (matriz);
}