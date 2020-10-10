#ifndef PONTO_H
#define PONTO_h

typedef struct ponto Ponto;

Ponto* criaponto (char* nome, int dimensao, double* coordenadas);

double distanciaEuclidiana (Ponto* ponto1, Ponto* ponto2);

void imprimePonto (Ponto* ponto);

void destroiPonto (Ponto* ponto);

#endif