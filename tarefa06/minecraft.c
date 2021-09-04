#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"
#define ALTURA_MAX 256

/**
 * Cria uma matriz de altitudes representando
 * o relevo de um mundo.
 **/
int **calcularAltitudes(int m, int n, int seed) {
    int **altitudes = malloc(m * sizeof(int*));

    for (int x = 0; x < m; x++) {
        altitudes[x] = malloc(n * sizeof(int*));

        for (int z = 0; z < n; z++) {
            altitudes[x][z] = (seed * (202 + x + z) + 12345 + x + z) % 256;
        }
    }

    return altitudes;
}

/**
 * Cria um novo mundo representado por uma matriz
 * de blocos alocada dinamicamente.
 **/
Bloco ***criarMundo(int m, int n, int **altitudes, int seed) {
    Bloco ***mundo = malloc(m * sizeof(Bloco**));

    for (int x = 0; x < m; x++) {
        mundo[x] = malloc(n * sizeof(Bloco*));

        for (int z = 0; z < n; z++) {
            mundo[x][z] = malloc(ALTURA_MAX * sizeof(Bloco));

            for (int y = 0; y <= altitudes[x][z]; y++) {
                int M = (seed * (202 + x + y + z) + x + y + z) % 33;

                Bloco bloco = { x, y, z, M };

                mundo[x][z][y] = bloco;
            }
        }
    }

    return mundo;
}

/**
 * Explora o mapa de um mundo e devolve o tempo
 * necessário para minerar todo ele. Além disso,
 * devolve a quantidade de alguns minérios de
 * interesse.
 **/
double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBloco
) {
    double tempoTotal = 0;
    *qtdDiamante = *qtdOuro = *qtdFerro = *qtdBloco = 0;

    for (int x = 0; x < m; x++) {
        for (int z = 0; z < n; z++) {
            for (int y = 0; y <= altitudes[x][z]; y++) {
                Bloco bloco = mundo[x][z][y];
                int tipo = bloco.M;

                if (tipo < 21) {
                    tempoTotal += tempoPorBloco;
                    (*qtdBloco)++;
                }

                if (tipo == 0) {
                    (*qtdDiamante)++;
                } else if (tipo <= 2) {
                    (*qtdOuro)++;
                } else if (tipo <= 5) {
                    (*qtdFerro)++;
                }
            }
        }
    }
    
    return tempoTotal;
}

/**
 * Função que imprime as informações sobre quantidade de blocos, minérios e tempo
 * total do mundo na saída padrão.
 **/
void imprimirInformacoes(int qtdBloco, double tempoTotal, int qtdDiamante, int qtdOuro, int qtdFerro) {
    printf("Total de Blocos: %d\n", qtdBloco);
    printf("Tempo total: %.2lfs\n", tempoTotal);
    printf("Diamantes: %d\n", qtdDiamante);
    printf("Ouros: %d\n", qtdOuro);
    printf("Ferros: %d\n", qtdFerro);

    return;
}

/**
 * Função responsável por liberar toda memória alocada dinamicamente na criação 
 * de uma matriz de altitudes em um mundo de minecraft.
 */
void liberarAltitudes(int **altitudes, int m) {
    for (int x = 0; x < m; x++) {
        free(altitudes[x]);
    }

    free(altitudes);

    return;
}

/**
 * Função responsável por liberar toda memória alocada dinamicamente na criação 
 * de blocos em um mundo de minecraft.
 */
void liberarMundo(Bloco ***mundo, int m, int n) {
    for (int x = 0; x < m; x++) {
        for (int z = 0; z < n; z++) {
            free(mundo[x][z]);
        }
        
        free(mundo[x]);
    }

    free(mundo);

    return;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int seed;
    scanf("%d", &seed);

    double tempoMedio;
    scanf("%lf", &tempoMedio);

    int **altitudes = calcularAltitudes(m, n, seed);
    Bloco ***mundo = criarMundo(m, n, altitudes, seed);

    int qtdDiamante, qtdOuro, qtdFerro, qtdBloco;
    double tempoTotal = explorarMundo(mundo, m, n, altitudes, tempoMedio, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBloco);

    imprimirInformacoes(qtdBloco, tempoTotal, qtdDiamante, qtdOuro, qtdFerro);

    liberarAltitudes(altitudes, m);
    liberarMundo(mundo, m, n);

    return 0;
}