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

    noCommaW[j++] = '\0';

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

    /*Segmento para imprimir o primeiro dos grupos*/

    for (int j = 1; j < retornaQuantidade (mst); j++) //procura nos vetores de pontos os pontos correspondentes às arestas da MST e os insere uma matriz de strings
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


    for (int i = 1; i < retornaQuantidade (mst); i++) //loop usado para construir os demais grupos
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
        if (!strstr (string_saida[numGrupos-1], grupo))
        {
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
        }

    }


    qsort (string_saida, numGrupos, sizeof (char**), comparaStrings); //Ordenando as strings

    for (int i = 0; i < numGrupos; i++)
    {
        fprintf (saida, "%s\n", string_saida[i]); //Imprimindo no Arquivo
    }

    for (int i = 0; i < numGrupos; i++) //liberando memória
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
    } //contar a dimensão dos pontos

    while (c != EOF)
    {
        if (c == '\n') numPontos++;
        c = fgetc(f); 
    } //contar o numero de pontos no arquivo

    rewind(f); //retornando ao começo do arquivo
    Ponto* pontos[numPontos];

    for (int i = 0; i <numPontos; i++)
    {
        char nome [MAXTAM];
        double coordenadas[dimensao];

        fscanf (f, " %[^,],", nome);

        for (int j = 0; j < dimensao; j++)
        {
            fscanf (f, "%lf,", &coordenadas[j]);
        }
        pontos[i] = criaponto (nome, dimensao, coordenadas);
    } //lendo coisas do arquivo de entrada

    fclose (f);

    MatrizY* matriz = criaMatriz (numPontos); //Matriz de coordenada criada
 
    for (int i = 0; i < numPontos; i++)
    {
        for (int j = 0; j < numPontos; j++)
        {
            if (i > j)
            matriz->distancias[i][j] = distanciaEuclidiana (pontos[i], pontos[j]);
            else 
            matriz->distancias[i][j] = -1;
        }
    } //preenchendo a matriz

    Mst* mst = criaMst (matriz);
    removeKelementos (mst, k); //remover os k-1 elementos
    imprimePontosnoArquivo (nomeSaida, mst, pontos, numPontos); //função para imprimir na saida 
    //liberar memória
    liberaMst (mst);
    destroiPontos (pontos, numPontos); 
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