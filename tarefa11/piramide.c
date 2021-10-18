#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piramide.h"

#define PORCENTAGEM_BONIFICACAO 0.1
#define PORCENTAGEM_LUCRO 0.06

/**
 * Função que cria um nó baseado em um nome e em um valor
 * de investimento inicial.
 * 
 * A função aloca memória dinamicamente para criar o nó, 
 * e é responsabilidade do usuário libera-lá.
 */
No *criar_no(char nome[21], double investimento) {
    No *no = malloc(sizeof(No));
    if (no == NULL) {
        exit(1);
    }

    no->recrutador = no->recrutado_dir = no->recrutado_esq = NULL;
    no->investimento = investimento;
    strcpy(no->nome, nome);

    return no;
}

/**
 * Função que libera toda a memória alocada dinamicamente 
 * durante a construção da estrutura da pirâmide.
 */
void destruir_piramide(No *topo) {
    if (topo == NULL) {
        return;
    }

    destruir_piramide(topo->recrutado_dir);
    destruir_piramide(topo->recrutado_esq);
    free(topo);

    return;
}

/**
 * Função que procura o nó de uma pessoa com um nome passado
 * dentro da estrutura da pirâmide.
 */
No *procura_pessoa(No *topo, char nome[21]) {
    if (topo == NULL) {
        return NULL;
    }

    if (strcmp(topo->nome, nome) == 0) {
        return topo;
    } else {
        No *pessoa = procura_pessoa(topo->recrutado_esq, nome);
        if (pessoa == NULL) {
            pessoa = procura_pessoa(topo->recrutado_dir, nome);
        }

        return pessoa;
    }
}

/**
 * Função que insere um nó contendo uma pessoa recrutada baseada
 * em um nó contendo uma pessoa recrutadora.
 */
void insere_recrutado(No *recrutador, No *recrutado) {
    if (recrutador == NULL || recrutado == NULL) {
        return;
    }

    recrutador->investimento -= PORCENTAGEM_BONIFICACAO * recrutado->investimento;
    recrutado->investimento += PORCENTAGEM_BONIFICACAO * recrutado->investimento;

    recrutado->recrutador = recrutador;
    if (recrutador->recrutado_esq == NULL) {
        recrutador->recrutado_esq = recrutado;
    } else {
        recrutador->recrutado_dir = recrutado;
    }

    if (recrutador->recrutado_dir != NULL && recrutador->recrutado_esq != NULL) {
        fazer_pagamento(recrutador, recrutador->recrutado_dir, PORCENTAGEM_LUCRO);
        fazer_pagamento(recrutador, recrutador->recrutado_esq, PORCENTAGEM_LUCRO);
        propagar_lucro(recrutador, PORCENTAGEM_LUCRO - 0.01);
    }

    return;
}

/**
 * Função que realiza um pagamento de uma pessoa recebidora para uma 
 * pessoa pagadora, baseada em uma porcentagem do investimento da 
 * pessoa pagadora.
 */
void fazer_pagamento(No *recebidora, No *pagadora, double porcentagem) {
    // se não há porque fazer o pagamento
    if (recebidora == NULL || porcentagem <= 0) {
        return;
    }

    recebidora->investimento += pagadora->investimento * porcentagem;
    pagadora->investimento -= pagadora->investimento * porcentagem;

    return;
}

/**
 * Função que propaga o lucro de uma pessoa para todos os seus 
 * recrutadores, baseado em uma porcentagem inicial que vai 
 * decrementando conforme a propagação do lucro. 
 */
void propagar_lucro(No *pessoa, double porcentagem) {
    // se não há porque propagar o lucro
    if (pessoa == NULL || pessoa->recrutador == NULL || porcentagem <= 0) {
        return;
    }

    fazer_pagamento(pessoa->recrutador, pessoa, porcentagem);

    // propaga os lucros para os recrutadores superiores
    propagar_lucro(pessoa->recrutador, porcentagem - 0.01);

    return;
}

/**
 * Função que retorna a altura da pirâmide.
 */
int achar_altura(No *topo) {
    if (topo == NULL) {
        return 0;
    }

    int altura_esquerda = 1 + achar_altura(topo->recrutado_esq);
    int altura_direita = 1 + achar_altura(topo->recrutado_dir);

    if (altura_esquerda > altura_direita) {
        return altura_esquerda;
    } else {
        return altura_direita;
    }
}
 
/**
 * Função que imprime um nível de uma pirâmide.
 */
void imprimir_nivel(No* no, int nivel, int i) {
    if (no == NULL || i > nivel) {
        return;
    }

    if (i < nivel) {
        imprimir_nivel(no->recrutado_esq, nivel, i+1);
        imprimir_nivel(no->recrutado_dir, nivel, i+1);
    } else {
        printf("[%s %.2lf] ", no->nome, no->investimento);
    }

    return;
}

/**
 * Função que imprime uma pirâmide por completo, nível
 * por nível.
 */
void imprimir_piramide(No *piramide) {
    int altura = achar_altura(piramide);

    for (int nivel = 0; nivel < altura; nivel++) {
        printf("Nivel %d: ", nivel+1);
        imprimir_nivel(piramide, nivel, 0);
        printf("\n");
    }

    return;
}

int main() {
    char nome[21];
    double investimento;
    scanf("Topo %s %lf", nome, &investimento);

    No *topo = criar_no(nome, investimento);
    imprimir_piramide(topo);
    
    char nome_recrutador[21], nome_recrutado[21];
    while (scanf("%s recruta %s %lf", nome_recrutador, nome_recrutado, &investimento) !=  EOF) {
        No* recrutador = procura_pessoa(topo, nome_recrutador);
        No *recrutado = criar_no(nome_recrutado, investimento);

        insere_recrutado(recrutador, recrutado);

        printf("\n");
        imprimir_piramide(topo);
    }

    destruir_piramide(topo);

    return 0;
}