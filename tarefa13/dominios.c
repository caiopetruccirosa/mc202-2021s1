#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominios.h"

/**
 * Função que cria um nó baseado em uma struct de Dominio passada como
 * parâmetro.
 * 
 * Essa função aloca memória dinamicamente e deve ser liberada posteriormente.
 */
No *criar_no(Dominio dominio) {
    No *no = malloc(sizeof(No));
    
    if (no == NULL) exit(1);

    no->esquerda = no->direita = NULL;
    no->dominio = dominio;
    
    return no;
}

/**
 * Função que lê os dados de um domínio (nome do domínio e o seu IP)
 * a partir da entrada padrão e retorna uma struct contendo os dados.
 */
Dominio ler_dominio() {
    Dominio dominio;

    scanf("%s %s", dominio.nome, dominio.ip);
    dominio.vezes_consultadas = 0;
    
    return dominio;
}

/**
 * Função que lê uma ABB de domínios a partir da entrada padrão e
 * retorna um ponteiro para o nó raiz da árvore.
 */
No *ler_dominios(int n) {
    No *raiz = NULL;

    for (int i = 0; i < n; i++) {
        Dominio dominio = ler_dominio();
        inserir_dominio(&raiz, dominio);
    }

    return raiz;
}

/**
 * Função que calcula a altura de uma ABB a partir de uma raiz passada.
 */
int calcular_altura(No *raiz) {
    if (raiz == NULL) {
        return 0;
    }

    int altura_esquerda = calcular_altura(raiz->esquerda);
    int altura_direita = calcular_altura(raiz->direita);

    if (altura_esquerda > altura_direita) {
        return altura_esquerda + 1;
    } else {
        return altura_direita + 1;
    }
}

/**
 * Função que balanceia uma subABB a partir do ponteiro para a sua raiz
 * passado como parâmetro.
 */
void balancear_subarvore(No *raiz) {
    if (raiz == NULL) return;
    
    return;
}

/**
 * Função que insere um domínio passado como parâmetro em uma ABB cuja
 * raiz deve ser passada por parâmetro como um ponteiro de ponteiro, sendo
 * uma referência para o ponteiro da raiz.
 * 
 * Essa função aloca memória dinamicamente para expansão da ABB,
 * que deve ser liberada depois.
 */
void inserir_dominio(No **raiz, Dominio dominio) {
    if (raiz == NULL) return;

    if (*raiz == NULL) {
        *raiz = criar_no(dominio);
    } else if (strcmp(dominio.nome, (*raiz)->dominio.nome) <= 0) {
        inserir_dominio(&(*raiz)->esquerda, dominio);
    } else {
        inserir_dominio(&(*raiz)->direita, dominio);
    }

    return;
}

/**
 * Função que busca um domínio armazenado em uma ABB de domínios com
 * base no nome do domínio e retorna um ponteiro para o domínio.
 * Deve ser passado a raiz da árvore onde a busca será realizada e o
 * domínio como uma string.
 */
Dominio *buscar_dominio(No *raiz, char dominio[101]) {
    if (raiz == NULL) return NULL;

    int comparacao = strcmp(dominio, raiz->dominio.nome);

    if (comparacao == 0) {
        return &raiz->dominio;
    } else if (comparacao < 0) {
        return buscar_dominio(raiz->esquerda, dominio);
    } else {
        return buscar_dominio(raiz->direita, dominio);
    }
}

/**
 * Função que libera toda a memória alocada dinamicamente existente
 * em uma ABB cuja raiz deve ser passada como parâmetro.
 */
void destruir_dominios(No *raiz) {
    if (raiz == NULL) return;

    destruir_dominios(raiz->esquerda);
    destruir_dominios(raiz->direita);
    
    free(raiz);

    return;
}