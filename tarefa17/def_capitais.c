#include <stdio.h>
#include <stdlib.h>
#include "grafo_cidades.h"

/**
 * Função que libera a memória alocada em uma matriz quadrada de doubles,
 * de tamanho n.
 */
void destruir_matriz(double **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main() {
    int n;
    scanf("%d", &n);

    Grafo_Cidades *grafo_cidades = criar_grafo_cidades(n);
    
    int populacao_total = ler_grafo_cidades(grafo_cidades);

    double **distancias = calcular_distancias(grafo_cidades);

    calcular_fatores_centralidade(grafo_cidades, distancias);
    calcular_populacao_alcancada(grafo_cidades, distancias);

    Cidade *possiveis_capitais = cidades_ordenadas_por_fator_centralidade(grafo_cidades);

    imprimir_capitais(possiveis_capitais, n, populacao_total);

    // libera a matriz de distâncias geradas pelo algoritmo de Floyd-Warshal
    destruir_matriz(distancias, n);
    destruir_grafo_cidades(grafo_cidades);
    free(possiveis_capitais);

    return 0;
}