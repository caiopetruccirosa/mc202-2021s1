#include <stdio.h>
#include <stdlib.h>

/**
 * Função que lê um inteiro da entrada padrão, que indica o tamanho da matriz
 * de um quebra-cabeça de arranha-céus.
 */
int ler_tamanho() {
    int n;

    scanf("%d", &n);

    // Incrementa 2 no valor retornado para considerar as bordas
    return n + 2;
}

/**
 * Função que lê uma matriz de inteiro n x n da entrada padrão e torna um ponteiro
 * para o seu ínicio. A matriz é alocada dinamicamente internamente e é responsabilidade
 * do usuário liberar a memória alocada.
 */
int **ler_matriz(int n) {
    int **matriz = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        matriz[i] = malloc(n * sizeof(int));

        for (int j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    return matriz;
}

/**
 * Função responsável por liberar a memória de uma matriz de inteiros n x n, que
 * foi alocada dinamicamente anteriormente.
 */
void liberar_matriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }

    free(matriz);
}

/**
 * Função que imprime os elementos internos de uma matriz de inteiros n x n,
 * excluindo os elementos das bordas da matriz.
 */
void imprimir_matriz(int **matriz, int n) {
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            printf("%d ", matriz[i][j]);
        }

        printf("\n");
    }
}

/**
 * Função que verifica 
 */
int eh_solucao_final(int **matriz, int n) {
    for (int i = 1; i < n - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (matriz[i][j] == 0) {
                return 0;
            }
        }
    }

    return 1;
}

int eh_valor_valido(int **matriz, int n, int i, int j) {   
    for (int i_aux = 1; i_aux < n - 1; i_aux++) {
        if (i != i_aux && matriz[i_aux][j] == matriz[i][j]) {
            return 0;
        }
    }

    for (int j_aux = 1; j_aux < n - 1; j_aux++) {
        if (j != j_aux && matriz[i][j_aux] == matriz[i][j]) {
            return 0;
        }
    }

    int cont = 0;
    int max_v = -1;
    for (int j_aux = 1; j_aux < n - 1; j_aux++) {
        if (max_v < matriz[i][j_aux]) {
            cont += 1;
            max_v = matriz[i][j_aux];
        }

        if (cont > matriz[i][0]) {
            return 0;
        }
    }

    cont = 0;
    max_v = -1;
    for (int j_aux = n - 2; j_aux > 0; j_aux--) {
        if (max_v < matriz[i][j_aux]) {
            cont += 1;
            max_v = matriz[i][j_aux];
        }

        if (cont > matriz[i][n-1]) {
            return 0;
        }
    }

    cont = 0;
    max_v = -1;
    for (int i_aux = 1; i_aux < n - 1; i_aux++) {
        if (max_v < matriz[i_aux][j]) {
            cont += 1;
            max_v = matriz[i_aux][j];
        }

        if (cont > matriz[0][j]) {
            return 0;
        }
    }

    cont = 0;
    max_v = -1;
    for (int i_aux = n - 2; i_aux > 0; i_aux--) {
        if (max_v < matriz[i_aux][j]) {
            cont += 1;
            max_v = matriz[i_aux][j];
        }

        if (cont > matriz[n-1][j]) {
            return 0;
        }
    }

    return 1;
}

/**
 * Função que encontra uma solução para o quebra-cabeça dos arranha-céus de
 * maneira recursiva usando backtracking. Retorna um número inteiro, que pode
 * ser 0 ou 1, indicando se existe solução para o quebra-cabeça ou não.
 */
int encontrar_solucao(int **matriz, int n, int idx) {
    if (eh_solucao_final(matriz, n)) {
        return 1;
    }

    int i = (idx / (n - 2)) + 1;
    int j = (idx % (n - 2)) + 1;

    if (i < n - 1 && j < n - 1) {
        for (int v = 1; v <= n; v++) {
            matriz[i][j] = v;

            if (eh_valor_valido(matriz, n, i, j) && encontrar_solucao(matriz, n, idx++)) {
                return 1;
            }

            matriz[i][j] = 0;
        }
    }

    return 0;
}


int main() {
    int n = ler_tamanho();
    int** matriz = ler_matriz(n);

    encontrar_solucao(matriz, n, 0);

    imprimir_matriz(matriz, n);

    liberar_matriz(matriz, n);

    return 0;
}