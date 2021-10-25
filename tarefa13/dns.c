#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominios.h"

/**
 * Struct que armazena os dados de uma requisição, como o domínio
 * requisitado e o IP do usuário.
 */
struct requisicao {
    char dominio[101];
    char ip_usuario[16];
} typedef Requisicao;

/**
 * Struct que armazena os dados de uma resposta, como o status da resposta,
 * o domínio requisitado, o IP do usuário e o IP do servidor que responde ao
 * domínio.
 */
struct resposta {
    char status[10];
    char dominio[101];
    char ip_usuario[16];
    char ip_servidor[16];
} typedef Resposta;

/**
 * Função que lê uma lista de requisições para domínios da entrada padrão
 * e retorna um ponteiro para um vetor de requisições.
 * 
 * Essa função aloca memória dinamicamente que deve ser liberada posteriormente.
 */
Requisicao *ler_requisicoes(int m) {
    Requisicao *requisicoes = malloc(m * sizeof(Requisicao));
    
    if (requisicoes == NULL) exit(1);
    
    for (int i = 0; i < m; i++) {
        scanf("\nGET %s FROM %s", requisicoes[i].dominio, requisicoes[i].ip_usuario);
    }

    return requisicoes;
}

int main() {
    int u, n, m;

    scanf("%d %d", &u, &n);
    No *dominios = ler_dominios(n);

    scanf("%d", &m);
    Requisicao *requisicoes = ler_requisicoes(m);

    for (int i = 0; i < m; i++) {
        Dominio *dominio = buscar_dominio(dominios, requisicoes->dominio);
        if (dominio != NULL) {
            dominio->vezes_consultadas++;
        }

        if (dominio == NULL) {
            printf("NOTFOUND %s FROM %s\n", requisicoes->dominio, requisicoes->ip_usuario);
        } else if (dominio->vezes_consultadas < u) {
            printf("ACCEPTED %s FROM %s RESPOND %s\n", requisicoes->dominio, requisicoes->ip_usuario, dominio->ip);
        } else {
            printf("FORBIDDEN %s FROM %s RESPOND %s\n", requisicoes->dominio, requisicoes->ip_usuario, dominio->ip);
        }
    }

    destruir_dominios(dominios);
    free(requisicoes);

    return 0;
}