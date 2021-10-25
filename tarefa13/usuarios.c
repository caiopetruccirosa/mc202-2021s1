#include <stdlib.h>
#include <string.h>
#include "usuarios.h"

/****************** Funções Internas ******************/

/**
 * 
 */
No_Usuario *criar_no_usuario(char ip[16]);

/**
 * 
 */
void rotacao_esquerda_usuario(Arvore_Usuario *raiz);

/**
 * 
 */
void rotacao_direita_usuario(Arvore_Usuario *raiz);

/**
 * 
 */
void rotacao_esquerda_direita_usuario(Arvore_Usuario *raiz);

/**
 * 
 */
void rotacao_direita_esquerda_usuario(Arvore_Usuario *raiz);

/******************************************************/

No_Usuario *criar_no_usuario(char ip[16]) {
    No_Usuario *no = malloc(sizeof(No_Usuario));
    
    if (no == NULL) exit(1);

    no->esquerda = no->direita = NULL;
    no->altura = 0;
    strcpy(no->ip, ip);
    no->qtd_requisicoes = 0;
    
    return no;
}

int altura_usuario(Arvore_Usuario raiz) {
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

int fator_balanceamento_usuario(Arvore_Usuario raiz) {
    return (raiz != NULL) ? altura_usuario(raiz->esquerda) - altura_usuario(raiz->direita) : 0;
}

void rotacao_esquerda_usuario(Arvore_Usuario *raiz) {
    No_Usuario *raiz_antiga = *raiz;
    *raiz = (*raiz)->direita;
    raiz_antiga->direita = (*raiz)->esquerda;
    (*raiz)->esquerda = raiz_antiga;

    raiz_antiga->altura = altura_usuario(raiz_antiga);
    (*raiz)->altura = altura_usuario(*raiz);

    return;
}

void rotacao_direita_usuario(Arvore_Usuario *raiz) {
    No_Usuario *raiz_antiga = *raiz;
    *raiz = (*raiz)->esquerda;
    raiz_antiga->esquerda = (*raiz)->direita;
    (*raiz)->direita = raiz_antiga;

    raiz_antiga->altura = altura_usuario(raiz_antiga);
    (*raiz)->altura = altura_usuario(*raiz);

    return;
}

void rotacao_esquerda_direita_usuario(Arvore_Usuario *raiz) {
    rotacao_esquerda_usuario(&(*raiz)->esquerda);
    rotacao_direita_usuario(raiz);
    return;
}
 
void rotacao_direita_esquerda_usuario(Arvore_Usuario *raiz) {
    rotacao_direita_usuario(&(*raiz)->direita);
    rotacao_esquerda_usuario(raiz);
    return;
 }

int contabilizar_requisicao(Arvore_Usuario *raiz, char ip[16], int limite_requisicoes) {
    int foi_contabilizado;
    if (*raiz == NULL) {
        *raiz = criar_no_usuario(ip);
        (*raiz)->qtd_requisicoes++;
        foi_contabilizado = 1;
    } else if (strcmp(ip, (*raiz)->ip) == 0) {
        if ((*raiz)->qtd_requisicoes < limite_requisicoes) {
            (*raiz)->qtd_requisicoes++;
            foi_contabilizado = 1;
        } else {
            foi_contabilizado = 0;
        }
    } else if (strcmp(ip, (*raiz)->ip) < 0) {
        foi_contabilizado = contabilizar_requisicao(&(*raiz)->esquerda, ip, limite_requisicoes);
    } else {
        foi_contabilizado = contabilizar_requisicao(&(*raiz)->direita, ip, limite_requisicoes);
    }

    (*raiz)->altura = altura_usuario(*raiz);

    // rotações
    if (fator_balanceamento_usuario(*raiz) < -1) {
        if (fator_balanceamento_usuario((*raiz)->direita) > 0) {
            rotacao_direita_esquerda_usuario(raiz);
        } else {
            rotacao_esquerda_usuario(raiz);
        }
     } else if (fator_balanceamento_usuario(*raiz) > 1) {
        if (fator_balanceamento_usuario((*raiz)->esquerda) < 0) {
            rotacao_esquerda_direita_usuario(raiz);
        } else {
            rotacao_direita_usuario(raiz);
        }
    }

    return foi_contabilizado;
}

void destruir_usuarios(Arvore_Usuario raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_usuarios(raiz->esquerda);
    destruir_usuarios(raiz->direita);
    free(raiz);

    return;
}