#include <stdlib.h>
#include <time.h>
#include "../include/matriz.h"

// Funcao para criar a matriz de cores
// Pre-condicao: nenhuma
// Pos-condicao: cria uma matriz com cores agradaveis
double** criar_matriz()
{
    srand(time(NULL));
    register int i;
    register int j;
    double cor = 0.0f;
    double **m = calloc(LMAX, sizeof(double*));
    if(!m)
        exit(1);

    for(i = 0; i < LMAX; i++){
        m[i] = calloc(CMAX, sizeof(double));
        if(!m[i])
            exit(1);
    }

    for(i = 0; i < LMAX; i++){
        for(j = 0; j < CMAX; j++){
            cor = cor + 0.135f * (rand()%3);
            m[i][j] = cor;
            cor = cor + 0.27f * (rand()%3);
            m[i][j] = cor;
            cor = cor + 0.405f * (rand()%3);
            m[i][j] = cor;
            cor = 0.0f;
        }
    }

    return m;
}

// Funcao para preencher valores de vertice
// Pre-condicao: nenhuma
// Pos-condicao: retorna matriz de pontos em forma de diamante
double** preencher_vertices()
{
    register int i;
    double** vertice = calloc(M_VERTICE, sizeof(double*));
    if(!vertice)
        exit(1);

    for(i = 0; i < M_VERTICE; i++){
        vertice[i] = calloc(3, sizeof(double));
        if(!vertice[i])
            exit(1);
    }

    // Definicao da altura do topo e base
    vertice[0][1] = 0.8f;
    vertice[1][1] = -V_MAIOR;
    // Definicao do restante do restante das faces, todos os valores de Y zerados
    vertice[2][0] = -V_MENOR;       vertice[2][2] = V_MENOR;
    vertice[3][0] = V_MENOR;        vertice[3][2] = V_MENOR;
    vertice[4][0] = V_MENOR;        vertice[4][2] = -V_MENOR;
    vertice[5][0] = -V_MENOR;       vertice[5][2] = -V_MENOR;

    return vertice;
}

// Funcao para liberar matriz
// Pre-condicao: matriz alocada
// Pos-condicao: retorna nulo para matriz de qualquer tipo
void** liberar_matriz(void** m, int n)
{
    register int i;

    for(i = 0; i < n; i++){
        free(m[i]);
        m[i] = NULL;
    }

    free(m);

    return NULL;
}
