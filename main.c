#include "Matriz.h"
#include "kruskal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    char nomeArquivo[50];
    strcpy (nomeArquivo, "ent.txt");
    //scanf ("%s", nomeArquivo);
    int k = 3;
    //scanf ("%d", &k);
    FILE* f;
    while (!(f = fopen (nomeArquivo, "r"))) 
    {
        printf ("Arquivo %s não encontrado!\n", nomeArquivo);
        scanf ("%s", nomeArquivo);
    }
    MatrizY* y = constroiMatriz (f, k);

    liberaMatriz (y);
    printf ("\n ------------------------------------------------------------------------\n");

   // imprimeMatriz(y);
    return 0;
}