#ifndef MATRIZ_H
#define MATRIZ_H
#include "Ponto.h"
#include <stdio.h>

typedef struct matrizy MatrizY;

MatrizY* criaMatriz (int dim);

int retornaDimensao (MatrizY* y);

double retornaDistancias (MatrizY* y, int i, int j);

void constroiMatriz (FILE* f, int k, char* nomeArqSaida);

void imprimeMatriz (MatrizY* matriz);

void liberaMatriz (MatrizY* matriz);


#endif