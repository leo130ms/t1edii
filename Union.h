#include "kruskal.h"
#include "Matriz.h"

typedef struct pais Pais;

Pais* criaPais (int tam);

void liberaPais (Pais* p);

void UF_union(int p, int q, Pais* pais, int* h);

int UF_find(int p, Pais* pais);

int UF_connected(int p, int q, Pais* pais);
