#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

/**
 * Função que lê uma lista de elementos na entrada padrão e os insere
 * sequencialmente (inserindo no fim) em uma lista circular duplamente ligada.
 * 
 * Todos os nós da lista são alocados dinamicamente, então é responsabilidade do usuário
 * liberar toda a memória alocada dinamicamente.
 */
No *ler_lista(int m) {
    No *lista = NULL;

    for (int i = 0; i < m; i++) {
        int h;
        scanf("%d", &h);

        adicionar(&lista, h);
    }

    return lista;
}

/**
 * Função que imprime todos os elementos de uma lista duplamente ligada em uma linha.
 */
void imprimir_lista(No *lista) {
    if (lista != NULL) {
        No *atual = lista;
        
        do {
            printf("%d ", atual->dado);
            atual = atual->proximo;
        } while (atual != lista);

        printf("\n");
    }

    return;
}

/**
 * Função que destroi uma lista ligada, liberando toda a memória alocada dinamicamente
 * para a criação dos nós.
 */
void destruir_lista(No *lista) {
    if (lista != NULL) {
        No *atual = lista;
        do {
            No *proximo = atual->proximo;

            free(atual);

            atual = proximo;
        } while (atual != lista);
    }

    return;
}

/**
 * Função que adiciona um "dado" ao final de uma lista circular duplamente ligada.
 * 
 * É necessário passar uma referência ao ponteiro do primeiro nó da lista, que nunca 
 * deve ser NULL, pois não é possível adicionar um elemento de uma referência NULL de 
 * uma lista. Isso não significa, que o valor do primeiro nó não pode ser NULL, o que 
 * é válido, já que nesse caso a lista apenas está vazia.
 * 
 * Essa função aloca memória dinamicamente para criação do novo nó que irá armazenar o
 * dado.
 */
void adicionar(No **lista, int dado) {
    No *no = malloc(sizeof(No));
    if (no == NULL) {
        exit(1);
    }

    no->dado = dado;
    no->anterior = NULL;
    no->proximo = NULL;

    if (*lista != NULL) {
        No *ultimo = (*lista)->anterior;

        ultimo->proximo = no;
        no->anterior = ultimo;

        (*lista)->anterior = no;
        no->proximo = *lista;
    } else {
        *lista = no->anterior = no->proximo = no;
    }

    return;
}

/**
 * Função que remove um nó de uma lista circular duplamente ligada. Para isso, se assume
 * que o nó passado faz parte da lista cuja referência é passada.
 * 
 * É necessário passar uma referência ao ponteiro do primeiro nó da lista, que nunca 
 * deve ser NULL, pois não é possível remover um elemento de uma referência NULL de 
 * uma lista. Isso não significa, que o valor do primeiro nó não pode ser NULL, o que 
 * é válido, já que nesse caso a lista apenas está vazia.
 * 
 * Essa função libera a memória alocada dinamicamente para criação do nó.
 */
void remover(No **lista, No *no) {
    // Caso a lista esteja vazia, não tem o que remover
    if (*lista == NULL) {
        return;
    } 

    // Caso o nó a ser removido, seja o primeiro da lista, transforma o próximo no primeiro
    if (*lista == no) {
        *lista = (*lista)->proximo;
    }

    No *anterior = no->anterior;
    No *proximo = no->proximo;

    // Caso só exista um nó na lista, transforma a lista em NULL
    if (anterior == no && proximo == no) {
        *lista = NULL;
    } else {
        anterior->proximo = proximo;
        proximo->anterior = anterior;
    }

    free(no);

    return;
}

/**
 * Função que ordena uma lista ligada que armazena inteiros, usando o algoritmo de 
 * ordenação Selection Sort.
 */
void ordernar_lista(No *lista) {
    // Caso a lista esteja vazia, não tem o que ordenar
    if (lista == NULL) {
        return;
    }

    No *fixo = lista;
    do {
        No *variante, *menor;
        variante = menor = fixo;

        do {
            if (variante->dado < menor->dado) {
                menor = variante;
            }

            variante = variante->proximo;
        } while (variante != lista);

        // troca os dados de "menor" com "fixo"
        if (menor != fixo) {
            int aux = fixo->dado;
            fixo->dado = menor->dado;
            menor->dado = aux;
        }

        fixo = fixo->proximo;
    } while (fixo != lista);

    return;
}