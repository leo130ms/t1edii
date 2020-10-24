#ifndef PONTO_H
#define PONTO_h
#define MAXTAM 2^64

typedef struct ponto Ponto;

Ponto* criaponto (char* nome, int dimensao, double* coordenadas);

double distanciaEuclidiana (Ponto* ponto1, Ponto* ponto2);

char* imprimePontos (Ponto** pontos, int tam);

char* imprimePonto (Ponto* ponto);

void destroiPonto (Ponto* ponto);

void inserePonto (Ponto* ponto, Ponto** grupo, int pos);

Ponto* achaPonto (Ponto* ponto, Ponto* grupo, int tam);

void destroiPontos (Ponto** ponto, int tam);

#endif