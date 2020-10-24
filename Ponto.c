#include "Ponto.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

struct ponto{
    char* nome;
    int dimensao;
    double* coordenadas;
};

Ponto* criaponto (char* nome, int dimensao, double* coordenadas)
{
    Ponto* novo = (Ponto*) malloc (sizeof(Ponto));
    novo->nome = strdup (nome);
    novo->dimensao = dimensao;
    novo->coordenadas = (double*) malloc (sizeof (double) * dimensao);
    for (int i = 0; i < dimensao ; i++) 
    {
        novo->coordenadas[i] = coordenadas[i];  
    }
    return novo;
}

double distanciaEuclidiana (Ponto* ponto1, Ponto* ponto2)
{
    double dist = 0;

    for (int i = 0; i < ponto1->dimensao; i++)
        dist += pow ((ponto1->coordenadas[i] - ponto2->coordenadas[i]), 2);
    return sqrt (dist);
}

char* imprimePontos (Ponto** pontos, int tam){
    for (int i = 0; i < tam; i++)
        printf ("%s\n", pontos[i]->nome);
}

char* imprimePonto (Ponto* ponto)
{
    return (ponto->nome);
}

void destroiPonto (Ponto* ponto)
{
    free (ponto->coordenadas);
    free (ponto->nome);
    free (ponto);
}

void inserePonto (Ponto* ponto, Ponto** grupo, int pos)
{
    grupo[pos] = ponto;
}

Ponto* achaPonto (Ponto* ponto, Ponto* grupo, int tam)
{
    for (int i = 0; i < tam; i++)
        if (grupo[i].nome == ponto->nome) grupo[i];
    return NULL;
}

void destroiPontos (Ponto** pontos, int tam){
    for (int i = 0; i < tam; i++)
    destroiPonto (pontos[i]);
}