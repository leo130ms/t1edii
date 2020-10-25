#include "Union.h"
#include <stdlib.h>

struct pais
{
    int* id;
    int tamanho;
    int* pesos;
};

Pais* criaPais (int tam)
{
    Pais* p = (Pais*) malloc (sizeof (Pais));
    p->id = (int*) malloc (sizeof (int) * tam);
    p->pesos = (int*) malloc (sizeof (int) * tam);
    for (int i = 0; i < tam; i++) p->id[i] = i;
    for (int i = 0; i < tam; i++) p->pesos[i] = i;
    p->tamanho = tam;
    return p;
}

void liberaPais (Pais* p)
{
    free (p->id);
    free (p->pesos);
    free (p);
}

void UF_union(int p, int q, Pais* pais){
    int i = UF_find (pais->id[p], pais);
    int j = UF_find (pais->id[q], pais);
    if ( i == j ) return;
    if (pais->pesos[i] < pais->pesos[j])
    {
        pais->id[i] = j;
        pais->pesos[j] += pais->pesos[i];
    }
    else
    {
        pais->id[j] = i;
        pais->pesos[i] += pais->pesos[j];
    }
}

int UF_find(int p, Pais* pais){
    while (p != pais->id[p]) 
    {
        pais->id[p] = pais->id[pais->id[p]];
        p = pais->id[p];
    }
    return p;
}

int UF_connected(int p, int q, Pais* pais){
    return UF_find (p, pais) == UF_find (q, pais);
}