#include "Matriz.h"
#include <stdio.h>
#include <string.h>

int main ()
{
    char nomeArquivo[50];
    //strcpy (nomeArquivo, "1.txt");
    scanf ("%s", nomeArquivo);
    FILE* f;
    while (!(f = fopen (nomeArquivo, "r"))) 
    {
        printf ("Arquivo %s não encontrado!\n", nomeArquivo);
        scanf ("%s", nomeArquivo);
    }
    MatrizY* y = constroiMatriz (f);
    return 0;
}