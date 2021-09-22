#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

Fila *criar_fila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->lanterna = NULL;
    fila->fim = NULL;

    return fila;
}

void destruir_fila(Fila *fila) {
    No *no = fila->inicio;
    while (no != NULL) {
        No *prox = no->proximo;

        destruir_no(no);

        no = prox;
    }

    free(fila);

    return;
}

No *criar_no(Pessoa pessoa) {
    No *no = malloc(sizeof(No));
    no->pessoa = malloc(sizeof(Pessoa));

    no->pessoa->numero_documento = pessoa.numero_documento;
    strcpy(no->pessoa->profissao, pessoa.profissao);
    strcpy(no->pessoa->estado_vacinacao, pessoa.estado_vacinacao);
    no->proximo = NULL;

    return no;
}

void destruir_no(No *no) {
    free(no->pessoa);
    free(no);

    return;
}

Pessoa criar_pessoa(int numero_documento, char profissao[26], char estado_vacinacao[13]) {
    Pessoa pessoa = {};
    
    pessoa.numero_documento = numero_documento;
    strcpy(pessoa.profissao, profissao);
    strcpy(pessoa.estado_vacinacao, estado_vacinacao);

    return pessoa;
}

Fila *ler_fila() {
    Fila *fila = criar_fila();

    int numero_documento;
    char profissao[26];
    char estado_vacinacao[13];
    while (scanf("%d %s %s", &numero_documento, profissao, estado_vacinacao) != EOF) {
        Pessoa pessoa = criar_pessoa(numero_documento, profissao, estado_vacinacao);

        enfileirar(fila, pessoa);
    }

    return fila;
}

void imprimir_fila(Fila *fila) {
    for (No* atual = fila->inicio; atual != NULL; atual = atual->proximo) {
        Pessoa *pessoa = atual->pessoa;

        printf("%d %s %s\n", pessoa->numero_documento, pessoa->profissao, pessoa->estado_vacinacao);
    }

    return;
}

void enfileirar(Fila *fila, Pessoa pessoa) {
    No *no = criar_no(pessoa);

    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = no;
    } else {
        // Verifica se a pessoa tem uma profissão ""privilegiada""
        if (
            strcmp(pessoa.profissao, "coach") == 0 || 
            strcmp(pessoa.profissao, "ex-bbb") == 0 || 
            strcmp(pessoa.profissao, "filho-politico") == 0 || 
            strcmp(pessoa.profissao, "herdeiro") == 0 || 
            strcmp(pessoa.profissao, "youtuber-financas") == 0
        ) {
            // Insere a pessoa no ínicio da fila
            no->proximo = fila->inicio;
            fila->inicio = no;
        } else if (strcmp(pessoa.profissao, "funcionario") == 0) {
            // Caso a pessoa não esteja vacinada e iria entrar atrás de um fiscal, nem insere a pessoa na fila
            if (strcmp(pessoa.estado_vacinacao, "vacinado") != 0 && strcmp(fila->fim->pessoa->profissao, "fiscal") == 0) {
                destruir_no(no);

                return;
            }

            // Insere a pessoa no fim da fila
            fila->fim->proximo = no;
            fila->fim = no;
        } else {
            // Caso a pessoa não esteja vacinada e iria entrar atrás de um fiscal, nem insere a pessoa na fila
            if (strcmp(pessoa.estado_vacinacao, "vacinado") != 0 && strcmp(fila->lanterna->pessoa->profissao, "fiscal") == 0) {
                destruir_no(no);

                return;
            }

            // Insere a pessoa entre a pessoa com a lanterna e a pessoa seguinte
            no->proximo = fila->lanterna->proximo;
            fila->lanterna->proximo = no;
        }

        // Remove todas as pessoas da fila que estão diretamente atrás de um fiscal e não estão vacinadas
        if (strcmp(pessoa.profissao, "fiscal") == 0) {
            No *fiscalizado = no->proximo;
            while (fiscalizado != NULL && strcmp(fiscalizado->pessoa->estado_vacinacao, "vacinado") != 0) {
                no->proximo = fiscalizado->proximo;

                destruir_no(fiscalizado);

                fiscalizado = no->proximo;
            }
        }
    }

    if (no->proximo == NULL) {
        fila->fim = no;
    }

    fila->lanterna = no;

    return;
}

Pessoa desenfileirar(Fila *fila) {
    No *no = fila->inicio;

    Pessoa pessoa = criar_pessoa(
        no->pessoa->numero_documento, 
        no->pessoa->profissao, 
        no->pessoa->estado_vacinacao);
    
    fila->inicio = fila->inicio->proximo;

    destruir_no(no);

    return pessoa;
}