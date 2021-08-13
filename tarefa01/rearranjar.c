#include <stdio.h>
#include <stdlib.h>

/**
Função que lê dois int da entrada padrão (stdin) no endereços 'n'
e 'm', e popula um vetor de int 'v[]', tomando o valor em 'n' como 
tamanho do vetor.
*/
void ler_entradas(int *n, int *m, int v[]) {
    scanf("%d", n);
    scanf("%d", m);

    for (int i = 0; i < *n; i++) {
        v[i] = i+1;
    }
}

/**
Função que inverte os valores de uma sub seção de um vetor de int 'v[]',
baseados em índices de 'inicio' e 'fim'.

Os índices passados devem ser válidos, dado que a função não valida se 
são realmente posições válidas do vetor.
*/
void inverter_subsecao(int v[], int inicio, int fim) {
    while (inicio < fim) {
        int temp = v[inicio];
        v[inicio] = v[fim];
        v[fim] = temp;

        inicio++;
        fim--;
    }
}

/**
Função que move um elemento int para o fim de uma sub seção de um vetor de int 
'v[]', determinada pelos índices de 'inicio' e 'fim' da seção.

Para que um elemento seja movido ao fim da seção, e o resto do vetor não seja 
alterado, os elementos restantes devem ser movidos em uma posição para, então, 
colocar o elemento em 'inicio' para o fim da seção.

Os índices passados devem ser válidos, dado que a função não valida se 
são realmente posições válidas do vetor.
*/
void mover_para_fim_subsecao(int v[], int inicio, int fim) {
    int temp = v[inicio];

    for (int i = inicio; i < fim; i++) {
        v[i] = v[i+1];
    }

    v[fim] = temp;
}

/**
Função que encontra o índice de um valor int 'val' em um vetor de int 'v[]'.

Caso o valor não esteja presente no vetor, a função retorna -1.
*/
int encontrar_indice(int v[], int n, int val) {
    for (int i = 0; i < n; i++) {
        if (v[i] == val) {
            return i;
        }
    }

    return -1;
}

/**
Função que "rearranja" um vetor de int 'v[]' de tamanho n, considerando
o uma fila de participantes, com base nas regras descritas no problema.
*/
void rearranjar(int v[], int n, int m) {
    for (int i = 0; i < m; i++) {
        int acao, a, b;
        scanf("%d %d %d", &acao, &a, &b);

        int a_idx = encontrar_indice(v, n, a);
        int b_idx = encontrar_indice(v, n, b);

        // verifica se o índices são válidos
        if (a_idx != -1 && b_idx != -1) {
            if (acao == 1) {
                inverter_subsecao(v, a_idx, b_idx);
            } else if (acao == 2) {
                mover_para_fim_subsecao(v, a_idx, b_idx);
            }
        }
    }
}

/**
Função que imprime um vetor de int 'v[]' de tamanho n para a saída
padrão (stdout).

O formato da saída será "1 2 3 4 5 6\n" para um vetor v igual a
[1, 2, 3, 4, 5, 6], por exemplo.
*/
void imprimir_vetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", v[i]);

        if (i < n-1) {
            printf(" ");
        }
    }

    printf("\n");
}

int main() {
    int n;
    int m;
    int fila_participantes[10000];

    ler_entradas(&n, &m, fila_participantes);

    rearranjar(fila_participantes, n, m);

    imprimir_vetor(fila_participantes, n);

    return 0;
}