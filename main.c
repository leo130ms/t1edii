#include "Matriz.h"
#include "kruskal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
    char nomeArquivo[50];
    //strcpy (nomeArquivo, argv[0]);
    strcpy (nomeArquivo, "ent.txt");
    //scanf ("%s", nomeArquivo);
    int k = atoi (argv[1]);
    //scanf ("%d", &k);
    FILE* f;
    if (!(f = fopen (nomeArquivo, "r"))) 
        exit(1);
    constroiMatriz (f, k, argv[2]);
   // imprimeMatriz(y);
    return 0;
}