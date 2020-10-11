#include "Matriz.h"
#include <stdio.h>
#include <string.h>

int main ()
{
    char nomeArquivo[50];
    strcpy (nomeArquivo, "ent.txt");
    //scanf ("%s", nomeArquivo);
    FILE* f;
    while (!(f = fopen (nomeArquivo, "r"))) 
    {
        printf ("Arquivo %s não encontrado!\n", nomeArquivo);
        scanf ("%s", nomeArquivo);
    }
    MatrizY* y = constroiMatriz (f);
    imprimeMatriz(y);

    return 0;
}