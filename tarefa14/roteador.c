#include <stdio.h>
#include <stdlib.h>
#include "filaprioridade.h"

/**
 * Função que executa um tick, de número c, onde os k pacotes
 * com prioridade na fila de prioridade, de tamanho m, serão 
 * removidos, caso possível.
 */
void computar_tick(Fila_Prioridade *pacotes, int k, int c) {
    printf("TICK %d\n", c);

    for (int i = 0; i < k && !esta_vazia(pacotes); i++) {
        Pacote p = extrair_maximo(pacotes);
        printf("%d\t%d\t%d\n", p.id, p.prioridade, p.incremento);
    }

    printf("\n");
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    Fila_Prioridade *pacotes = criar_fila_prioridade(m);

    int contador_tick = 0;
    int id, prioridade, incremento;
    while (scanf("%d %d %d", &id, &prioridade, &incremento) != EOF) {
        if (id == 0 && prioridade == 0 && incremento == 0) {

            // caso ocorra um tick do roteador
            computar_tick(pacotes, k, ++contador_tick);
            incrementar_prioridades(pacotes);

        } else {

            // caso seja possivel adicionar um pacote
            Pacote p = { id, prioridade, incremento };
            inserir_pacote(pacotes, p);

        }

    }

    destruir_fila_prioridade(pacotes);

    return 0;
}