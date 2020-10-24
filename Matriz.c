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

int substring (char* str1, char* str2)
{
    int j = 0;
    for (int i = 0; i < strlen(str1); i++)
    {
        if (str1[i] == str2[i])
        {
            for (j = 0; j < strlen (str1); j++)
            {
                if (str1[i + j] != str2[j]) break;
            }
        }
    }
    return j == strlen (str2);
}

void imprimePontosnoArquivo (Mst* mst, Ponto** pontos, int numPontos, char* nomeArqSaida)
{
    FILE* saida = fopen (nomeArqSaida, "w");
    Pais* pais = criaPais (numPontos);
    char* string_saida[MAXTAM];
    int numGrupos = 0;
    int *altura = (int*)calloc(numPontos, sizeof(int));
    for (int i = 0; i < retornaQuantidade (mst); i++)
    {
        int index_1 = retornaIndex_1 (mst, i);
        int index_2 = retornaIndex_2 (mst, i);
        if (!UF_connected (index_1, index_2, pais))
        {
            UF_union (index_1, index_2, pais, altura);
            printf ("%d %d\n", index_1, index_2);
        }
    }


    for (int i = 0; i < numPontos; i++)
    {
        
    }


    free (altura);
    liberaPais(pais);
    fclose (saida);
}

void constroiMatriz (FILE* f, int k, char* nomeArqSaida)
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

        fscanf (f, " %[^,],", nome);
//        printf ("%s->", nome);

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
    imprimePontosnoArquivo (mst, pontos, numPontos, nomeArqSaida);
    liberaMst (mst);
    destroiPontos (pontos, numPontos);
    //imprimePontos (pontos, numPontos);
    liberaMatriz (matriz);
}

void imprimeMatriz (FILE* log, MatrizY* matriz)
{
    fprintf(log, "\n-------Matriz Y distâncias------\n");
    for (int i = 0; i < matriz->dim; i++)
    {
    fprintf (log, "\n");
        for (int j = 0; j < matriz->dim; j++)
            if (i > j)
                fprintf (log, "%lf ", matriz->distancias[i][j]);
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