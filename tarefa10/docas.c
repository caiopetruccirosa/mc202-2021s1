#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "fila.h"

/**
 * Função que imprime na saída padrão uma operação feita 
 * sobre uma doca, a partir de um número de conteineres.
 */
void imprimir_operacao(char nome[], char tipo_operacao[], char tipo_mercadoria[], int doca, int n_conteineres) {
    printf("%s %s %s doca: %d conteineres: %d\n", nome, tipo_operacao, tipo_mercadoria, doca, n_conteineres);
}

/**
 * Cria um vetor de docas de mesma capacidade, docas essas que são pilhas de 
 * conteineres, cuja capacidade deve ser um número inteiro passado por parâmetro.
 */
Pilha *criar_docas(int numero_docas, int capacidade_doca) {
    Pilha *docas = malloc(numero_docas * sizeof(Pilha));
    if (docas == NULL) {
        exit(1);
    }

    for (int i = 0; i < numero_docas; i++) {
        docas[i] = criar_pilha(capacidade_doca);
    }

    return docas;
}

/**
 * Função que destroi a memória alocada dinamicamente para a criação das docas.
 */
void destruir_docas(Pilha *docas, int numero_docas) {
    for (int i = 0; i < numero_docas; i++) {
        free(docas[i].v);
    }

    free(docas);

    return;
}

/**
 * Função que retorna um valor booleano indicando se pode 
 * carregar um tipo de mercadoria do topo de uma doca.
 */
int pode_carregar_em_doca(Pilha doca, char tipo_mercadoria[]) {
    if (doca.topo < 0) {
        return 0;
    }

    if (strcmp(doca.v[doca.topo], tipo_mercadoria) == 0) {
        return 1;
    }

    return 0;
}

/**
 * Função que retorna um valor booleano indicando 
 * se pode descarregar mercadorias em uma doca.
 */
int pode_descarregar_em_doca(Pilha doca) {
    return doca.topo < doca.capacidade - 1;
}

/**
 * Função que retorna o índice da primeira doca disponível para cumprir um objetivo,
 * seja ele "carregar" ou "descarregar", para um tipo de mercadoria.
 * 
 * Caso não exista docas disponíveis, o valor retornado é -1.
 */
int primeira_doca_disponivel(Pilha *docas, int numero_docas, char objetivo[], char tipo_mercadoria[]) {
    for (int i = 0; i < numero_docas; i++) {
        if ((strcmp(objetivo, "descarrega") == 0 && pode_descarregar_em_doca(docas[i])) ||
            (strcmp(objetivo, "carrega") == 0 && pode_carregar_em_doca(docas[i], tipo_mercadoria))) {

            return i;
        }
    }

    return -1;
}

/**
 * Função que simula o funcionamento do porto, conforme a proposta da tarefa.
 */
void simular_porto(Fila *navios, int numero_navios, Pilha *docas, int numero_docas, int capacidade_docas) {
    // valor que indica a quantidade de falhas consecutivas ocorridas em operações de
    // carregar e descarregar navios ao longo do funcionamento do porto
    int falhas_consecutivas = 0;

    while (navios->qtd > 0 && falhas_consecutivas < navios->qtd) {
        Navio navio = desenfileirar(navios);
        
        int i = primeira_doca_disponivel(docas, numero_docas, navio.objetivo, navio.tipo_mercadoria);
        if (i < 0) {
            falhas_consecutivas++;
        } else {
            falhas_consecutivas = 0;

            int carga_operada = 0;
            if (strcmp(navio.objetivo, "descarrega") == 0) {
                // descarrega o navio
                while (carga_operada < navio.carga && pode_descarregar_em_doca(docas[i])) {
                    empilhar(&docas[i], navio.tipo_mercadoria);
                    carga_operada++;
                }
            } else if (strcmp(navio.objetivo, "carrega") == 0) {
                // carrega o navio
                while (carga_operada < navio.carga && pode_carregar_em_doca(docas[i], navio.tipo_mercadoria)) {
                    desempilhar(&docas[i]);
                    carga_operada++;
                }
            }

            navio.carga -= carga_operada;

            imprimir_operacao(navio.nome, navio.objetivo, navio.tipo_mercadoria, i, carga_operada);
        }

        // caso o navio ainda não tenha completado o seu objetivo no porto
        if (navio.carga > 0) {
            enfileirar(navios, navio);
        }
    }

    // caso ainda existam navios na fila
    if (navios->qtd > 0) {
        printf("ALERTA: impossivel esvaziar fila, restam %d navios.", navios->qtd);
    }
     
    return;
}

int main() {
    int numero_docas, capacidade_docas, numero_navios;
    scanf("%d %d %d", &numero_docas, &capacidade_docas, &numero_navios);

    Pilha *docas = criar_docas(numero_docas, capacidade_docas);
    Fila navios = ler_fila_navios(numero_navios);

    simular_porto(&navios, numero_navios, docas, numero_docas, capacidade_docas);

    destruir_fila_navios(navios);
    destruir_docas(docas, numero_docas);

    return 0;
}