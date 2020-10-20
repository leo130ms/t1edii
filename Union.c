#include "Union.h"
#include <stdlib.h>

struct pais
{
    int* id;
    int tamanho;
};

Pais* criaPais (int tam)
{
    Pais* p = (Pais*) malloc (sizeof (Pais));
    p->id = (int*) malloc (sizeof (int) * tam);
    for (int i = 0; i < tam; i++) p->id[i] = i;
    p->tamanho = tam;
    return p;
}

void liberaPais (Pais* p)
{
    free (p->id);
    free (p);
}

void UF_union(int p, int q, Pais* pais, int *h){
    int i = UF_find(p, pais);
    int j = UF_find(q, pais);
    if(h[i]<h[j]){
        pais->id[i]=j;
        h[j]+=h[i];
    }else{
        pais->id[j]=i;
        h[i]+=h[j];
    }
}

int UF_find(int p, Pais* pais){
    while(p != pais->id[p]){
        pais->id[p] = pais->id[pais->id[p]];
        p = pais->id[p];
    }
    return p;
}

int UF_connected(int p, int q, Pais* pais){
    return UF_find (p, pais) == UF_find (q, pais);
}
