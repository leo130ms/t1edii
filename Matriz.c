#include "Matriz.h"
#include <stdlib.h>
#include <string.h>

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

MatrizY* constroiMatriz (FILE* f)
{
    int numPontos = 0;
    int dimensao = 0;
    char c = fgetc(f);

    while (c != '\n')
    {
        if (c == ',') dimensao++;
        c = fgetc (f);
    }

    printf ("%d\n", dimensao);

    while (c != EOF)
    {
        if (c == '\n') numPontos++;
        c = fgetc(f); 
    }

    printf ("%d\n", numPontos);

    rewind(f);
    Ponto* pontos[numPontos];

    for (int i = 0; i <numPontos; i++)
    {
        char nome [50];
        double coordenadas[dimensao];

        fscanf (f, "%[^,],", nome);
        printf ("%s\n", nome);

        for (int j = 0; j < dimensao; j++)
        {
            fscanf (f, "%lf,", &coordenadas[j]);
            printf ("%lf\n", coordenadas[j]);
        }
        pontos[i] = criaponto (nome, dimensao, coordenadas);
    }

    MatrizY* matriz = criaMatriz (numPontos);  
    for (int i = 0; i < numPontos; i++)
    {
        for (int j = 0; j < numPontos; j++)
        {
            if (i >= j)
            matriz->distancias[i][j] = distanciaEuclidiana (pontos[i], pontos[j]);
            else 
            matriz->distancias[i][j] = -1;
        }
    }
    imprimeMatriz (matriz);
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

void liberaMatriz (MatrizY* matriz);