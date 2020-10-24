#include "Matriz.h"
#include "kruskal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv)
{
    //declaração variáveis entrada
    char nomeArqEnt[50];
    char nomeArqSaida[50];
    int k;
    
    
    //atribuição variáveis de entrada
    strcpy (nomeArqEnt, argv[1]);
    strcpy(nomeArqSaida, argv[3]);
    k = atoi(argv[2]);

    //printf("%s %s %d\n", nomeArqEnt, nomeArqSaida, k);
    
    //manipulação de arquivos
    FILE *f, *saida, *log;
    saida = fopen(nomeArqSaida, "w");
    log = fopen("log.txt", "w");
    if(saida == NULL || log==NULL){
        //printf("Não foi possivel criar arquivos de log/saida - abortando programa\n");
        return 0;
    }
    while (!(f = fopen (nomeArqEnt, "r"))) 
    {
        fprintf (log, "Arquivo %s não encontrado!\n", nomeArqEnt);
    }

    //execução programa
    MatrizY* y = constroiMatriz (f, k);
    imprimeMatriz(log, y);
    Mst* mst = criaMst(y);
    ImprimeMst(log, mst);
    printf("\n");
    
    //finalização programa
    //liberaMatriz (y);
    //fclose(f);
    //fclose(saida);
    //fclose(log);
    printf("acabei\n");
    return 0;
}