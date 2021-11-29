#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo_cidades.h"

Grafo_Cidades *criar_grafo_cidades(int n) {
    Grafo_Cidades *grafo = malloc(sizeof(Grafo_Cidades));

    grafo->qtd_cidades = n;
    
    grafo->cidades = malloc(n * sizeof(Cidade));
    if (grafo->cidades == NULL)
        exit(1);

    grafo->adjacencias = malloc(n * sizeof(double*));
    if (grafo->adjacencias == NULL)
        exit(1);

    for (int i = 0; i < n; i++) {
        grafo->adjacencias[i] = malloc(n * sizeof(double));
        if (grafo->adjacencias[i] == NULL)
            exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grafo->adjacencias[i][j] = 0.0;
        }
    }

    return grafo;
}

void destruir_grafo_cidades(Grafo_Cidades *grafo) {
    for (int i = 0; i < grafo->qtd_cidades; i++) {
        free(grafo->adjacencias[i]);
    }
    free(grafo->adjacencias);
    free(grafo->cidades);
    free(grafo);
}

int ler_grafo_cidades(Grafo_Cidades *grafo) {
    int populacao_total = 0;

    for (int i = 0; i < grafo->qtd_cidades; i++) {
        char nome[TAMANHO_NOME_CIDADE];
        int qtd_populacao;
        scanf("%s %d", nome, &qtd_populacao);

        Cidade cidade;
        strcpy(cidade.nome, nome);
        cidade.qtd_populacao = qtd_populacao;

        cidade.fator_centralidade = -1;
        cidade.qtd_populacao_alcancada = -1;

        grafo->cidades[i] = cidade;

        populacao_total += cidade.qtd_populacao;
    }

    char cidade_a[TAMANHO_NOME_CIDADE], cidade_b[TAMANHO_NOME_CIDADE];
    double distancia;
    while (scanf("%s %s %lf", cidade_a, cidade_b, &distancia) != EOF) {
        int idx_cidade_a = achar_indice(grafo, cidade_a);
        int idx_cidade_b = achar_indice(grafo, cidade_b);

        grafo->adjacencias[idx_cidade_a][idx_cidade_b] = distancia;
        grafo->adjacencias[idx_cidade_b][idx_cidade_a] = distancia;
    }

    return populacao_total;
}

int achar_indice(Grafo_Cidades *grafo, char nome[TAMANHO_NOME_CIDADE]) {
    for (int i = 0; i < grafo->qtd_cidades; i++) {
        if (strcmp(nome, grafo->cidades[i].nome) == 0) {
            return i;
        }
    }

    return -1;
}

double **calcular_distancias(Grafo_Cidades *grafo) {
    double **distancias = malloc(grafo->qtd_cidades * sizeof(double*));
    for (int i = 0; i < grafo->qtd_cidades; i++) {
        distancias[i] = malloc(grafo->qtd_cidades * sizeof(double));;
        for (int j = 0; j < grafo->qtd_cidades; j++) {
            if (i == j) {
                distancias[i][j] = 0.0;
            } else if (grafo->adjacencias[i][j]) {
                distancias[i][j] = grafo->adjacencias[i][j];
            } else {
                distancias[i][j] = INFINITO;
            }
        }
    }

    for (int k = 0; k < grafo->qtd_cidades; k++) {
        for (int i = 0; i < grafo->qtd_cidades; i++) {
            for (int j = 0; j < grafo->qtd_cidades; j++) {
                double distancia_nova = distancias[i][k] + distancias[k][j];
                if (distancia_nova < distancias[i][j]) {
                    distancias[i][j] = distancia_nova;
                }
            }
        }
    }
    
    return distancias;
}

void calcular_populacao_alcancada(Grafo_Cidades *grafo, double **distancias) {
    for (int i = 0; i < grafo->qtd_cidades; i++) {
        grafo->cidades[i].qtd_populacao_alcancada = 0;
        for (int j = 0; j < grafo->qtd_cidades; j++) {
            if (distancias[i][j] < INFINITO) {
                grafo->cidades[i].qtd_populacao_alcancada += grafo->cidades[j].qtd_populacao;
            }
        }
    }
}

void calcular_fatores_centralidade(Grafo_Cidades *grafo, double **distancias) {
    for (int i = 0; i < grafo->qtd_cidades; i++) {
        double numerador = 0.0;
        double denominador = 0.0;

        for (int j = 0; j < grafo->qtd_cidades; j++) {
            if (distancias[i][j] < INFINITO) {
                numerador += grafo->cidades[j].qtd_populacao * distancias[i][j];
                denominador += grafo->cidades[j].qtd_populacao;
            }
        }

        grafo->cidades[i].fator_centralidade = numerador / denominador;
    }
}

void imprimir_capitais(Cidade *cidades, int qtd_cidades, int populacao_total) {
    for (int i = 0; i < qtd_cidades; i++) {
        if (cidades[i].qtd_populacao_alcancada > populacao_total / 2) {
            printf("%s %.2lf\n", cidades[i].nome, cidades[i].fator_centralidade);
        }
    }
}

int particionamento(Cidade *vetor, int inicio, int fim) {
    int posicao_pivo = fim;

    int i = inicio;
    for (int j = inicio; j < fim; j ++) {
        if ((vetor[j].fator_centralidade < vetor[posicao_pivo].fator_centralidade) ||
            (vetor[j].fator_centralidade == vetor[posicao_pivo].fator_centralidade &&
            strcmp(vetor[j].nome, vetor[posicao_pivo].nome) < 0)) {
            if (i != j) {
                Cidade aux;
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }

            i++;
        }
    }

    // Coloca o pivô no lugar dele
    if (i != posicao_pivo) {
        Cidade aux;
        aux = vetor[i];
        vetor[i] = vetor[posicao_pivo];
        vetor[posicao_pivo] = aux;

        posicao_pivo = i;
    }

    return posicao_pivo;
}

void quick_sort(Cidade *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int posicao_pivo = particionamento(vetor, inicio, fim);

        quick_sort(vetor, inicio, posicao_pivo-1);
        quick_sort(vetor, posicao_pivo+1, fim);
    }
}

Cidade *cidades_ordenadas_por_fator_centralidade(Grafo_Cidades *grafo) {
    Cidade *cidades = malloc(grafo->qtd_cidades * sizeof(Cidade));

    for (int i = 0; i < grafo->qtd_cidades; i++) {
        cidades[i] = grafo->cidades[i];
    }

    quick_sort(cidades, 0, grafo->qtd_cidades-1);

    return cidades;
}