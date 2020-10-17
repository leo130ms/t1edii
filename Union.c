#include "Union.h"
#include <stdlib.h>

struct pais
{
    int id [MAXTAM];
    int tamanho;
};

Pais* criaPais (int tam)
{
    Pais* p = (Pais*) malloc (sizeof (Pais));
    for (int i = 0; i < tam; i++) p->id[i] = i;
    p->tamanho = tam;
    return p;
}

void UF_union(int p, int q, Pais* pais){
    int pid = pais->id[p];
    int qid = pais->id[q];
    for (int i = 0; i < pais->tamanho; i++)
    {
        if (pais->id[i] == pid)
            pais->id[i] = qid;
    }
}

int UF_find(int p, Pais* pais){
    return pais->id[p];
}

int UF_connected(int p, int q, Pais* pais){
    return UF_find (p, pais) == UF_find (q, pais);
}