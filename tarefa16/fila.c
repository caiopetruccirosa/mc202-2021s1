#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

Fila criar_fila() {
    Fila fila;
    fila.qtd = 0;
    fila.inicio = fila.fim = NULL;

    return fila;
}

void destruir_fila(Fila fila) {
    No_Fila *no = fila.inicio;

    while (no != NULL) {
        No_Fila *proximo = no->proximo;
        free(no);
        no = proximo;
    }
}

void enfileirar(Fila *fila, int valor) {
    No_Fila *novo = malloc(sizeof(No_Fila));
    novo->valor = valor;
    novo->proximo = NULL;

    if (fila->qtd > 0) {
        fila->fim->proximo = novo;
        fila->fim = novo;
    } else {
        fila->inicio = fila->fim = novo;
    }

    fila->qtd++;
}

int desenfileirar(Fila *fila) {
    No_Fila *no = fila->inicio;
    fila->inicio = no->proximo;
    int valor = no->valor;
    fila->qtd--;

    free(no);

    return valor;
}