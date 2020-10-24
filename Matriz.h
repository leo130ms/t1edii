#ifndef MATRIZ_H
#define MATRIZ_H
#include "Ponto.h"
#include <stdio.h>

typedef struct matrizy MatrizY;

MatrizY* criaMatriz (int dim);

int retornaDimensao (MatrizY* y);

double retornaDistancias (MatrizY* y, int i, int j);

MatrizY* constroiMatriz (FILE* f, int k);

void imprimeMatriz (FILE* log, MatrizY* matriz);


void liberaMatriz (MatrizY* matriz);


#endif