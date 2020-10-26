#include "Matriz.h"
#include "kruskal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    char nomeArquivo[MAXTAM];
    strcpy (nomeArquivo, argv[1]);
    int k = atoi (argv[2]);
    FILE* f;
    if (!(f = fopen (nomeArquivo, "r"))) 
    {
        printf ("Arquivo %s não encontrado!\n", nomeArquivo);
        exit(1);
    }
    MatrizY* y = constroiMatriz (f, k, argv[3]); //função para construir a matriz de coordenadas e imprimir a saida da MST

    liberaMatriz (y); //liberando a memória da matriz y

    return 0;
}