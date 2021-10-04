#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "fila.h"

/**
 * Função que imprime na saída padrão uma operação feita sobre uma doca, a partir de
 * um número de conteineres.
 */
void imprimir_operacao(char nome[], char tipo_operacao[], char tipo_mercadoria[], int doca, int n_conteineres) {
    printf("%s %s %s doca: %d conteineres: %d\n", nome, tipo_operacao, tipo_mercadoria, doca, n_conteineres);
}

/**
 * Cria um vetor de docas de mesma capacidade, docas que são pilhas de 
 * conteineres, cuja capacidade deve ser um número inteiro passado por parâmetro.
 */
Pilha *criar_docas(int numero_docas, int capacidade_doca) {
    Pilha *docas = malloc(numero_docas * sizeof(Pilha));

    for (int i = 0; i < numero_docas; i++) {
        docas[i] = criar_pilha(capacidade_doca);
    }

    return docas;
}

/**
 * 
 */
int primeira_doca_carregar(Navio *navio, Pilha *docas, int numero_docas) {
    for (int i = 0; i < numero_docas; i++) {
        if (pode_carregar(docas[i], navio->tipo_mercadoria)) {
            return i;
        }
    }

    return -1;
}

/**
 * 
 */
int primeira_doca_descarregar(Navio *navio, Pilha *docas, int numero_docas) {
    for (int i = 0; i < numero_docas; i++) {
        if (!eh_pilha_cheia(docas[i])) {
            return i;
        }
    }

    return -1;
}

/**
 * Função que descarrega a mercadoria de um navio em um conjuntos de docas, 
 * inserindo conteineres nelas, e retorna um valor booleano indicando se o 
 * navio foi totalmente descarregado ou não.
 */
int descarregar(Navio *navio, Pilha *docas, int numero_docas) {
    int idx_doca = primeira_doca_descarregar(navio, docas, numero_docas);
    if (idx_doca < 0) {
        return 0;
    }

    Pilha doca = docas[idx_doca];
    int carga_descarregada = 0;
    while (navio->carga > 0 && !eh_pilha_cheia(doca)) {
        Conteiner conteiner = {};
        strcpy(conteiner.tipo_mercadoria, navio->tipo_mercadoria);

        empilhar(&doca, conteiner);

        carga_descarregada++;
        navio->carga--;
    }

    imprimir_operacao(navio->nome, navio->objetivo, navio->tipo_mercadoria, idx_doca, carga_descarregada);

    return navio->carga <= 0;
}

/**
 * Função que carrega um navio a partir dos recursos uma doca, consumindo as
 * mercadorias em certas docas, e retorna um valor booleano indicando se o navio
 * foi totalmente carregado ou não.
 */
int carregar(Navio *navio, Pilha *docas, int numero_docas) {
    int idx_doca = primeira_doca_carregar(navio, docas, numero_docas);
    if (idx_doca < 0) {
        return 0;
    }

    Pilha doca = docas[idx_doca];
    int carga_carregada = 0;
    while (navio->carga > 0 && !eh_pilha_vazia(doca) && pode_carregar(doca, navio->tipo_mercadoria)) {
        desempilhar(&doca);
        
        navio->carga--;
        carga_carregada++;
    }

    imprimir_operacao(navio->nome, navio->objetivo, navio->tipo_mercadoria, idx_doca, carga_carregada);

    return navio->carga <= 0;
}

int main() {
    int numero_docas, capacidade_docas, numero_navios;
    scanf("%d", &numero_docas);
    scanf("%d", &capacidade_docas);
    scanf("%d", &numero_navios);

    Pilha *docas = criar_docas(numero_docas, capacidade_docas);
    Fila navios = ler_fila_navios(numero_navios);

    /*for (int i = 0; i < numero_docas; i++) {
        imprimir_pilha(docas[i]);
        printf("doca: %d, esta cheia: %d, esta vazia: %d\n", i, eh_pilha_cheia(docas[i]), eh_pilha_vazia(docas[i]));
    }*/

    while (!eh_fila_vazia(navios)) {
        Navio navio = desenfileirar(&navios);

        int sucedeu = 1;
        if (strcmp(navio.objetivo, "descarrega") == 0) {
            sucedeu = descarregar(&navio, docas, numero_docas);
        } else if (strcmp(navio.objetivo, "carrega") == 0) {
            sucedeu = carregar(&navio, docas, numero_docas);
        }

        if (!sucedeu) {
            enfileirar(&navios, navio);
        }
    }

    destruir_fila_navios(navios);

    return 0;
}