#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planejar.h"

int main() {
    char operacao[10];
    int qtd_voos = 0;
    Voo voos[100];

    do {
        scanf("%s", operacao);

        if (strcmp(operacao, "registrar") == 0) {
            int numero_voo;
            char *origem_voo, *destino_voo;
            Data data_voo;
            float valor_voo;

            origem_voo = malloc(4*sizeof(char));
            destino_voo = malloc(4*sizeof(char));

            scanf("%d", &numero_voo);
            scanf("%s %s", origem_voo, destino_voo);
            data_voo = ler_data();
            scanf("%f", &valor_voo);

            registrar(voos, &qtd_voos, numero_voo, origem_voo, destino_voo, data_voo, valor_voo);
        } else if (strcmp(operacao, "alterar") == 0) {
            int numero_voo;
            float valor_voo;
            
            scanf("%d %f", &numero_voo, &valor_voo);

            alterar(voos, qtd_voos, numero_voo, valor_voo);
        } else if (strcmp(operacao, "cancelar") == 0) {
            int numero_voo;
            scanf("%d", &numero_voo);

            cancelar(voos, &qtd_voos, numero_voo);
        } else if (strcmp(operacao, "planejar") == 0) {
            char origem_voo[4];
            Data data_inicio, data_fim;

            scanf("%s", origem_voo);
            data_inicio = ler_data();
            data_fim = ler_data();

            planejar(voos, qtd_voos, data_inicio, data_fim, origem_voo);
        }
    } while (strcmp(operacao, "planejar") != 0);

    // libera para o sistema operacional a memória alocada dinamicamente
    for (int i = 0; i < qtd_voos; i++) {
        free(voos[i].origem);
        free(voos[i].destino);
    }

    return 0;
}