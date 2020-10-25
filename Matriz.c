#include "Matriz.h"
#include "kruskal.h"
#include "Union.h"
#include <stdlib.h>
#include <string.h>

struct matrizy {
    int dim;
    double** distancias;
};

typedef struct grupo
{
  int indices[MAXTAM];
  int tam;  
}Grupo;


MatrizY* criaMatriz (int dim)
{
    MatrizY* y = (MatrizY*) malloc (sizeof(MatrizY));
    y->dim = dim;
    y->distancias = (double**) malloc (sizeof(double*)* dim);
    for (int i = 0; i < dim; i++)
    {
        y->distancias[i] = (double*) malloc (sizeof(double)* dim);
    }
    return y;
}

int retornaDimensao (MatrizY* y){
    return y->dim;
}

double retornaDistancias (MatrizY* y, int i, int j){
    return y->distancias[i][j];
}

int comparaStrings (const void* s1, const void* s2)
{
    return strcmp ((char*) s1, (char*) s2);
}

int achaString (char** texto, int numStrings, char* word)
{
    //printf ("%s %s\n", texto, word);
    for (int i = 0; i < numStrings; i++)
    {
        for (int j = 0; j < strlen (word); j++)
            if (strchr (texto[i], word[j])) return 1;
    }
    return -1;
}

Ponto* achaPontoNoGrupo (Grupo* g, int indice)
{
    for (int i = 0; i < g->tam; i++)
        if (g->indices[i] == indice) return g->indices[i];
    return 0;
}

Ponto* achaPontoNosGrupos (Grupo** gs, int indice, int numGrupos)
{
    if (numGrupos <= 0) return 0;
    for (int i = 0; i < numGrupos; i++)
        if (achaPontoNoGrupo(gs[i], indice)) return achaPontoNoGrupo(gs[i], indice);
    return 0;
}

int achaGrupo (Grupo** gs, Ponto* p, int numGrupos)
{
    if (numGrupos <= 0) return 0;
    for (int i = 0; i < numGrupos; i++)
        if (achaPontoNoGrupo(gs[i], p)) return i+1;
    return 0;
}

void imprimeGrupos (Grupo** gs, int numGrupos)
{
    for (int i = 0; i < numGrupos; i++)
    {
        for (int j = 0; j < gs[i]->tam - 1; j++)
        {
        }
    }
}

void imprimePontosnoArquivo (char* nomeSaida, Mst* mst, Ponto** pontos, int numPontos)
{
    FILE* saida = fopen (nomeSaida, "w");
    int tamMst = retornaQuantidade (mst);
    Grupo** grupos = (Grupo**) malloc (sizeof (Grupo*)* tamMst);
    for (int i = 0; i < tamMst; i++)
    {
        grupos[i] = (Grupo*) malloc (sizeof (Grupo));
        grupos[i]->tam = 0;
    }
    int numGrupos = 0;

    for (int i = 0; i < tamMst; i++)
    {
        printf ("AAAAAAAAAAAA\n");
        int index1 = retornaIndex_1 (mst, i);
        int index2 = retornaIndex_2 (mst, i);
        if (!achaPontoNosGrupos (grupos, index1, numGrupos) && !achaPontoNosGrupos (grupos, index2, numGrupos))
        {
            for (int j = i; j <tamMst; j++)
            {
                int jndex1 = retornaIndex_1 (mst, j);
                int jndex2 = retornaIndex_2 (mst, j);
                if (jndex1 == index1)
                {
                    grupos[numGrupos]->indices[grupos[numGrupos]->tam] = jndex2;
                    grupos[numGrupos]->tam++;
                    printf ("AAAAAAAAAAAA\n");
                }
                
                else if (jndex2 == index2)
                {
                    grupos[numGrupos]->indices[grupos[numGrupos]->tam] = jndex1;
                    grupos[numGrupos]->tam++;
                }
                else if (jndex2 == index1)
                {
                    grupos[numGrupos]->indices[grupos[numGrupos]->tam] = jndex1;
                    grupos[numGrupos]->tam++;
                }
                else if (jndex1 == index2)
                {
                    grupos[numGrupos]->indices[grupos[numGrupos]->tam] = jndex2;
                    grupos[numGrupos]->tam++;
                }      
            }
            numGrupos++;
            imprimeGrupos (grupos, numGrupos);
        }
    }

    imprimeGrupos (grupos, numGrupos);    
}

/*void imprimePontosnoArquivo (char* nomeSaida, Mst* mst, Ponto** pontos, int numPontos)
{
    FILE* saida = fopen (nomeSaida, "w");
    char* string_saida[MAXTAM];
    int numGrupos = 0;
    char grupo[MAXTAM];
    int index01 = retornaIndex_1 (mst, 0);
    int index02 = retornaIndex_2 (mst, 0);
    char ponto2[MAXTAM];
    strcpy (grupo, imprimePonto (pontos[index01]));
    //strcat (grupo, ",");
    strcpy (ponto2, imprimePonto (pontos[index02]));
    strcat (grupo, ponto2);
    //strcat (grupo, ",");

    for (int j = 1; j < retornaQuantidade (mst); j++)
    {
        char ponto1[MAXTAM];
        char ponto2[MAXTAM];
        int jndex1 = retornaIndex_1 (mst, j);
        int jndex2 = retornaIndex_2 (mst, j);
        if (jndex1 == index01)
        {
            strcat (grupo, imprimePonto (pontos[jndex2]));
            //strcat (grupo, ",");
        }
        else if (jndex2 == index02)
        {
            strcat (grupo, imprimePonto (pontos[jndex1]));
           // strcat (grupo, ",");
        }
        else if (jndex2 == index01)
        {
            strcat (grupo, imprimePonto (pontos[jndex1]));
            //strcat (grupo, ",");
        }
        else if (jndex1 == index02)
        {
            strcat (grupo, imprimePonto (pontos[jndex2]));
            //strcat (grupo, ",");
        }         
    }
    string_saida[numGrupos] = strdup (grupo);
    numGrupos++;


    for (int i = 1; i < retornaQuantidade (mst); i++)
    {
        char grupo[MAXTAM];
        int index1 = retornaIndex_1 (mst, i);
        int index2 = retornaIndex_2 (mst, i);
        char ponto2[MAXTAM];
        strcpy (grupo, imprimePonto (pontos[index1]));
        //strcat (grupo, ",");
        strcpy (ponto2, imprimePonto (pontos[index2]));
        strcat (grupo, ponto2);
        //strcat (grupo, ",");
        if (achaString (string_saida, numGrupos, grupo) < 0)
        {
            //printf ("%c %c\n", grupo[0], grupo[1]);
            for (int j = i+1; j < retornaQuantidade (mst); j++)
            {
                char ponto1[MAXTAM];
                char ponto2[MAXTAM];
                int jndex1 = retornaIndex_1 (mst, j);
                int jndex2 = retornaIndex_2 (mst, j);
                if (jndex1 == index1)
                {
                    strcat (grupo, imprimePonto (pontos[jndex2]));
                    //strcat (grupo, ",");
                }
                else if (jndex2 == index2)
                {
                    strcat (grupo, imprimePonto (pontos[jndex1]));
                    //strcat (grupo, ",");
                }
                else if (jndex2 == index1)
                {
                    strcat (grupo, imprimePonto (pontos[jndex1]));
                    //strcat (grupo, ",");
                }
                else if (jndex1 == index2)
                {
                    strcat (grupo, imprimePonto (pontos[jndex2]));
                    //strcat (grupo, ",");
                }
            }
            string_saida[numGrupos] = strdup (grupo);
            numGrupos++;
            //printf ("%s\n %d\n", string_saida[numGrupos], numGrupos);
        }

    }


    for (int i = 0; i < numGrupos; i++)
    {
        qsort (string_saida[i], strlen(string_saida[i]), sizeof(char), comparaStrings);
    }

    qsort (string_saida, numGrupos, sizeof (char**), comparaStrings);

    for (int i = 0; i < numGrupos; i++)
    {
        for (int j = 0; j < strlen (string_saida[i]); j++)
        fprintf (saida, "%s,", string_saida[i]);
    }

    //fprintf (saida, "%s,", string_saida[numGrupos]);

    fclose (saida);
}*/

MatrizY* constroiMatriz (FILE* f, int k, char* nomeSaida)
{
    int numPontos = 0;
    int dimensao = 0;
    char c = fgetc(f);

    while (c != '\n')
    {
        if (c == ',') dimensao++;
        c = fgetc (f);
    }

    while (c != EOF)
    {
        if (c == '\n') numPontos++;
        c = fgetc(f); 
    }

    rewind(f);
    Ponto* pontos[numPontos];

    for (int i = 0; i <numPontos; i++)
    {
        char nome [MAXTAM];
        double coordenadas[dimensao];

        fscanf (f, " %[^,],", nome);
        //printf ("%s ->", nome);

        for (int j = 0; j < dimensao; j++)
        {
            fscanf (f, "%lf,", &coordenadas[j]);
           // printf ("%lf\n", coordenadas[j]);
        }
        pontos[i] = criaponto (nome, dimensao, coordenadas);
    }

    fclose (f);
    //printf ("%d\n", dimensao);
    //printf ("%d\n", numPontos);

    MatrizY* matriz = criaMatriz (numPontos); 
 
    for (int i = 0; i < numPontos; i++)
    {
        for (int j = 0; j < numPontos; j++)
        {
            if (i > j)
            matriz->distancias[i][j] = distanciaEuclidiana (pontos[i], pontos[j]);
            else 
            matriz->distancias[i][j] = -1;
        }
    }

    Mst* mst = criaMst (matriz);
    removeKelementos (mst, k);
    ImprimeMst (mst);
    imprimePontosnoArquivo (nomeSaida, mst, pontos, numPontos);
    liberaMst (mst);
    destroiPontos (pontos, numPontos);
    //imprimePontos (pontos, numPontos);
    return matriz;  
}

void imprimeMatriz (MatrizY* matriz)
{
    for (int i = 0; i < matriz->dim; i++)
    {
    printf ("\n");
        for (int j = 0; j < matriz->dim; j++)
            if (i > j)
                printf ("%lf ", matriz->distancias[i][j]);
    }
}

void liberaMatriz (MatrizY* matriz)
{
    for (int i = 0; i < matriz->dim; i++)
    {
        free (matriz->distancias[i]);
    }
    free (matriz->distancias);
    free (matriz);
}