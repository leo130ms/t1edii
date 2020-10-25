#include "Matriz.h"
#include "kruskal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    char nomeArquivo[MAXTAM];
    strcpy (nomeArquivo, argv[1]);
    //scanf ("%s", nomeArquivo);
    int k = atoi (argv[2]);
    //scanf ("%d", &k);
    FILE* f;
    if (!(f = fopen (nomeArquivo, "r"))) 
    {
        printf ("Arquivo %s não encontrado!\n", nomeArquivo);
        exit(1);
    }
    MatrizY* y = constroiMatriz (f, k, argv[3]);

    liberaMatriz (y);
    printf ("\n ------------------------------------------------------------------------\n");

   // imprimeMatriz(y);
    return 0;
}