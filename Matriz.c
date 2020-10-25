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

int interSecao (char* str1, char* str2)
{
    int count = 0;
    for (int i = 0; i <strlen (str1); i++)
        if (str1[count] == str2[i]) count++;
    return count == strlen(str1);
}

int achaString (char** texto, int numStrings, char* word)
{
    char noCommaW[MAXTAM];
    int j = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (word[i] != ',')
        {
            noCommaW[j++] = word[i];
        }
    }

    noCommaW[j] = '\0';

    for (int i = 0; i < numStrings; i++)
    {
        if (interSecao(noCommaW, texto[i])) 
        {
            return 1;
        }
    }
    return -1;
}

void imprimePontosnoArquivo (char* nomeSaida, Mst* mst, Ponto** pontos, int numPontos)
{
    FILE* saida = fopen (nomeSaida, "w");
    char* string_saida[MAXTAM];
    int numGrupos = 0;
    char grupo[MAXTAM];
    int index01 = retornaIndex_1 (mst, 0);
    int index02 = retornaIndex_2 (mst, 0);
    char ponto2[MAXTAM];
    strcpy (grupo, imprimePonto (pontos[index01]));
    strcat (grupo, ",");
    strcpy (ponto2, imprimePonto (pontos[index02]));
    strcat (grupo, ponto2);
    strcat (grupo, ",");

    for (int j = 1; j < retornaQuantidade (mst); j++)
    {
        char ponto1[MAXTAM];
        char ponto2[MAXTAM];
        int jndex1 = retornaIndex_1 (mst, j);
        int jndex2 = retornaIndex_2 (mst, j);
        if (jndex1 == index01)
        {
            strcat (grupo, imprimePonto (pontos[jndex2]));
            strcat (grupo, ",");
        }
        else if (jndex2 == index02)
        {
            strcat (grupo, imprimePonto (pontos[jndex1]));
            strcat (grupo, ",");
        }
        else if (jndex2 == index01)
        {
            strcat (grupo, imprimePonto (pontos[jndex1]));
            strcat (grupo, ",");
        }
        else if (jndex1 == index02)
        {
            strcat (grupo, imprimePonto (pontos[jndex2]));
            strcat (grupo, ",");
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
        strcat (grupo, ",");
        strcpy (ponto2, imprimePonto (pontos[index2]));
        strcat (grupo, ponto2);
        strcat (grupo, ",");
        if (achaString (string_saida, numGrupos, grupo) == -1)
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
                    strcat (grupo, ",");
                }
                else if (jndex2 == index2)
                {
                    strcat (grupo, imprimePonto (pontos[jndex1]));
                    strcat (grupo, ",");
                }
                else if (jndex2 == index1)
                {
                    strcat (grupo, imprimePonto (pontos[jndex1]));
                    strcat (grupo, ",");
                }
                else if (jndex1 == index2)
                {
                    strcat (grupo, imprimePonto (pontos[jndex2]));
                    strcat (grupo, ",");
                }
            }
            string_saida[numGrupos] = strdup (grupo);
            numGrupos++;
            //printf ("%s\n %d\n", string_saida[numGrupos], numGrupos);
        }

    }


    qsort (string_saida, numGrupos, sizeof (char**), comparaStrings);

    for (int i = 0; i < numGrupos; i++)
    {
        fprintf (saida, "%s\n", string_saida[i]);
    }

    for (int i = 0; i < numGrupos; i++)
    {
        free (string_saida[i]);
    }

    fclose (saida);
}

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