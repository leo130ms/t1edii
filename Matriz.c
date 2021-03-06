#include "Matriz.h"
#include "kruskal.h"
#include "Union.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct matrizy {
    int dim; //dimensão da matriz quadrada
    double** distancias; //matriz com nxn valores representando as distâncias
};


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

    for (int j = 1; j < retornaQuantidade (mst); j++)//procura nos vetores de pontos os pontos correspondentes às arestas da MST e os insere uma matriz de strings
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


    for (int i = 1; i < retornaQuantidade (mst); i++)//loop usado para construir os demais grupos
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
        if (achaString (string_saida, numGrupos, grupo) < 0)
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

    qsort (string_saida, numGrupos, sizeof (char**), comparaStrings);//Ordenando as strings

    for (int i = 0; i < numGrupos; i++)//Imprimindo no Arquivo
    {
        fprintf (saida, "%s\n", string_saida[i]);
    }

    //liberando memória

    fclose (saida);
}

MatrizY* constroiMatriz (FILE* f, int k, char* nomeSaida)
{
    int numPontos = 0;
    int dimensao = 0;
    char c = fgetc(f);

    clock_t sLeitura = clock();

    while (c != '\n')
    {
        if (c == ',') dimensao++;
        c = fgetc (f);
    } //contanto a dimensão

    while (c != EOF)
    {
        if (c == '\n') numPontos++;
        c = fgetc(f); 
    } //contando o numero de pontos

    rewind(f);
    Ponto* pontos[numPontos]; //criando um vetor para ponteiros de pontos

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
    } //realizando a leitura do arquivo

    fclose (f);
    clock_t eLeitura = clock();

    double tLeitura = ((double)eLeitura - sLeitura) / CLOCKS_PER_SEC;
    //printf ("Tempo de Leitura: %lf\n", tLeitura);

    clock_t sCalcDist = clock();
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
    } //preenchendo a matriz de distancias

    clock_t eCalcDist = clock();
    double tCalcDist = ((double)eCalcDist - sCalcDist) / CLOCKS_PER_SEC;
    //printf ("Tempo de calculo das distancias: %lf\n", tCalcDist);

    clock_t sIdfGrupos = clock();
    Mst* mst = criaMst (matriz); //processo de criar a MST
    removeKelementos (mst, k); 
    clock_t eIdfGrupos = clock();
    double tIdfGrupos = ((double)eIdfGrupos - sIdfGrupos) / CLOCKS_PER_SEC;
    //printf ("Tempo de identificacao dos grupos: %lf\n", tIdfGrupos);
    clock_t sEscrita = clock();
    //imprimePontosnoArquivo (nomeSaida, mst, pontos, numPontos);
    clock_t eEscrita = clock();
    double tEscrita = ((double)eEscrita - sEscrita) / CLOCKS_PER_SEC;
    //printf ("Tempo de calculo das distancias: %lf\n", tEscrita);
    liberaMst (mst); //liberando a memoria de mst
    destroiPontos (pontos, numPontos); //liberando a memoria do vetor de pontos
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