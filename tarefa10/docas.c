#include <stdio.h>
#include "pilha.h"
#include "fila.h"

/**
 * Existem várias docas (n), e cada doca inicia o dia vazia.
 * 
 * Os containers sao armazenados na doca como uma pilha, então um container
 * é armazenado em cima do outro e só que o que está em cima pode ser retirado
 * 
 * As docas vão ser um array de pilhas.
 */


Pilha *criar_docas(int numero_docas, int capacidade_doca) {
    Pilha *docas = malloc(numero_docas * sizeof(Pilha));

    for (int i = 0; i < numero_docas; i++) {
        docas[i] = criar_pilha(capacidade_doca);
    }

    return docas;
}


int main() {
    int numero_docas, capacidade_docas, numero_navios;
    scanf("%d", &numero_docas);
    scanf("%d", &capacidade_docas);
    scanf("%d", &numero_navios);

    //printf("ALERTA: impossivel esvaziar fila, restam %d navios.", 99);

    return 0;
}