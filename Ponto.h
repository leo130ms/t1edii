#ifndef PONTO_H
#define PONTO_h
#define MAXTAM 500000

typedef struct ponto Ponto;

Ponto* criaponto (char* nome, int dimensao, double* coordenadas);

double distanciaEuclidiana (Ponto* ponto1, Ponto* ponto2);

char* imprimePontos (Ponto** pontos, int tam);

char* imprimePonto (Ponto* ponto);

void destroiPonto (Ponto* ponto);

void destroiPontos (Ponto** ponto, int tam);

#endif