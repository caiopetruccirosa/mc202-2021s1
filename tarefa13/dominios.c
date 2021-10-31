#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominios.h"

/****************** Funções Internas ******************/

/**
 * Função que cria um nó baseado em uma struct de Dominio passada como
 * parâmetro.
 * 
 * Essa função aloca memória dinamicamente que deve ser liberada posteriormente.
 */
No_Dominio *criar_no_dominio(Dominio dominio);

/**
 * Função que calcula e retorna o valor da altura da árvore, partindo de sua raiz.
 */
int altura_dominio(Arvore_Dominio raiz);

/**
 * Função que calcula o fator de balanceamento de uma árvore.
 */
int fator_balanceamento_dominio(Arvore_Dominio raiz);

/**
 * Função que faz a rotação para esquerda de um nó raiz de uma árvore de
 * domínios.
 */
void rotacao_esquerda_usuario(Arvore_Dominio *raiz);

/**
 * Função que faz a rotação para direita de um nó raiz de uma árvore de
 * domínios.
 */
void rotacao_direita_usuario(Arvore_Dominio *raiz);

/******************************************************/

No_Dominio *criar_no_dominio(Dominio dominio) {
    No_Dominio *no = malloc(sizeof(No_Dominio));
    
    if (no == NULL) exit(1);

    no->esquerda = no->direita = NULL;
    no->altura = 0;
    no->dominio = dominio;
    
    return no;
}

Dominio ler_dominio() {
    Dominio dominio;
    scanf("%s %s", dominio.nome, dominio.ip);
    
    return dominio;
}

Arvore_Dominio ler_dominios(int n) {
    Arvore_Dominio raiz = NULL;

    for (int i = 0; i < n; i++) {
        Dominio dominio = ler_dominio();
        inserir_dominio(&raiz, dominio);
    }

    return raiz;
}

int altura_dominio(Arvore_Dominio raiz) {
    if (raiz == NULL) return -1;
    if (raiz->esquerda == NULL && raiz->direita == NULL) return 0;

    int maior_altura;
    if (raiz->esquerda == NULL) {
        maior_altura = raiz->direita->altura;
    } else if (raiz->direita == NULL) {
        maior_altura = raiz->esquerda->altura;
    } else if (raiz->esquerda->altura > raiz->direita->altura) {
        maior_altura = raiz->esquerda->altura;
    } else {
        maior_altura = raiz->direita->altura;
    }

    return maior_altura + 1;
}

int fator_balanceamento_dominio(Arvore_Dominio raiz) {
    return (raiz != NULL) ? altura_dominio(raiz->esquerda) - altura_dominio(raiz->direita) : 0;
}

void rotacao_esquerda_dominio(Arvore_Dominio *raiz) {
    No_Dominio *raiz_antiga = *raiz;
    *raiz = (*raiz)->direita;
    raiz_antiga->direita = (*raiz)->esquerda;
    (*raiz)->esquerda = raiz_antiga;

    raiz_antiga->altura = altura_dominio(raiz_antiga);
    (*raiz)->altura = altura_dominio(*raiz);

    return;
}

void rotacao_direita_dominio(Arvore_Dominio *raiz) {
    No_Dominio *raiz_antiga = *raiz;
    *raiz = (*raiz)->esquerda;
    raiz_antiga->esquerda = (*raiz)->direita;
    (*raiz)->direita = raiz_antiga;

    raiz_antiga->altura = altura_dominio(raiz_antiga);
    (*raiz)->altura = altura_dominio(*raiz);

    return;
}

void inserir_dominio(Arvore_Dominio *raiz, Dominio dominio) {
    if (*raiz == NULL) {
        *raiz = criar_no_dominio(dominio);
    } else if (strcmp(dominio.nome, (*raiz)->dominio.nome) < 0) {
        inserir_dominio(&(*raiz)->esquerda, dominio);
    } else {
        inserir_dominio(&(*raiz)->direita, dominio);
    }

    // atualiza a altura do nó
    (*raiz)->altura = altura_dominio(*raiz);

    // faz as rotações necessárias para manter o balanceamento da árvore
    if (fator_balanceamento_dominio(*raiz) < -1) {
        if (fator_balanceamento_dominio((*raiz)->direita) > 0) {
            rotacao_direita_dominio(&(*raiz)->direita);
            rotacao_esquerda_dominio(raiz);
        } else {
            rotacao_esquerda_dominio(raiz);
        }
     } else if (fator_balanceamento_dominio(*raiz) > 1) {
        if (fator_balanceamento_dominio((*raiz)->esquerda) < 0) {
            rotacao_esquerda_dominio(&(*raiz)->esquerda);
            rotacao_direita_dominio(raiz);
        } else {
            rotacao_direita_dominio(raiz);
        }
    }

    return;
}

Dominio *buscar_dominio(Arvore_Dominio raiz, char dominio[101]) {
    if (raiz == NULL) {
        return NULL;
    }

    int comparacao = strcmp(dominio, raiz->dominio.nome);
    if (comparacao == 0) {
        return &raiz->dominio;
    } else if (comparacao < 0) {
        return buscar_dominio(raiz->esquerda, dominio);
    } else {
        return buscar_dominio(raiz->direita, dominio);
    }
}

void destruir_dominios(Arvore_Dominio raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_dominios(raiz->esquerda);
    destruir_dominios(raiz->direita);
    free(raiz);

    return;
}