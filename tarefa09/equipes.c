#include <stdio.h>
#include "lista.h"

#define ESQUERDA -1
#define DIREITA 1

void separar_times(No **lista, int m, No **time_esquerda, No **time_direita) {
    int direcao = ESQUERDA;

    for (int i = 0; i < m; i++) {
        int numero_sorteado;
        scanf("%d", &numero_sorteado);

        No *pessoa_escolhida = *lista;
        for (int j = 0; j < numero_sorteado - 1; j++) {
            if (direcao == ESQUERDA) {
                pessoa_escolhida = pessoa_escolhida->anterior;
            } else if (direcao == DIREITA) {
                pessoa_escolhida = pessoa_escolhida->proximo;
            }
        }

        int dado = pessoa_escolhida->dado;
        if (direcao == ESQUERDA) {
            adicionar(time_esquerda, dado);
        } else if (direcao == DIREITA) {
            adicionar(time_direita, dado);
        }

        remover(lista, pessoa_escolhida);

        direcao *= -1;
    }

    return;
}


int main() {
    int m;
    scanf("%d", &m);

    No *lista = ler_lista(m);

    No *time_esquerda, *time_direita;
    time_esquerda = time_direita = NULL;

    separar_times(&lista, m, &time_esquerda, &time_direita);

    ordernar_lista(time_esquerda);
    ordernar_lista(time_direita);

    imprimir_lista(time_esquerda);
    imprimir_lista(time_direita);

    destruir_lista(lista);
    destruir_lista(time_esquerda);
    destruir_lista(time_direita);

    return 0;
}