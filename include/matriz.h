#ifndef _MATRIZ_H_INCLUDED
#define _MATRIZ_H_INCLUDED

#define LMAX 16
#define CMAX 3
#define M_VERTICE 6
#define V_MAIOR 2.0f
#define V_MENOR (V_MAIOR/2)
#define ESCALA_TELA 0.35f

// Funcao para criar a matriz de cores
// Pre-condicao: nenhuma
// Pos-condicao: cria uma matriz com cores agradaveis
double** criar_matriz();

// Funcao para preencher valores de vertice
// Pre-condicao: nenhuma
// Pos-condicao: retorna matriz de pontos em forma de diamante
double** preencher_vertices();

// Funcao para liberar matriz
// Pre-condicao: matriz alocada
// Pos-condicao: retorna nulo para matriz de qualquer tipo
void** liberar_matriz(void** m, int n);

#endif
