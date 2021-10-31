#include <stdio.h>
#include <stdlib.h>
#include "filaprioridade.h"

/**
 * Macros que facilitam o cálculo dos índices dos "nós" pais e filhos
 * na fila de prioridade (max-heap) no vetor associado.
 */
#define PAI(i) ((i - 1) / 2)
#define F_ESQ(i) (2 * i + 1)
#define F_DIR(i) (2 * i + 2)

/**
 * Função que cria uma fila de prioridade de m pacotes e initializa o 
 * vetor com valores "zero". O espaço do vetor é alocado dinamicamente,
 * portanto, deve ser liberado pelo usuário.
 */
Fila_Prioridade *criar_fila_prioridade(int m) {
    Fila_Prioridade *fila = malloc(sizeof(Fila_Prioridade));
    fila->v = malloc(m * sizeof(Pacote));
    fila->i = 0;
    fila->tamanho = m;

    return fila;
}

/**
 * Função que retorna um valor booleano indicando se a fila 
 * de prioridade está vazia.
 */
int esta_vazia(Fila_Prioridade *fila) {
    return fila->i <= 0;
}

/**
 * Função que retorna um valor booleano indicando se a fila 
 * de prioridade está cheia.
 */
int esta_cheia(Fila_Prioridade *fila) {
    return fila->i >= fila->tamanho;
}

/**
 * Função que troca dois pacotes de posição baseado na posição da memória,
 * ou seja, nos ponteiros que indicam suas posições iniciais.
 */
void trocar(Pacote *a, Pacote *b) {
    Pacote tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * Função que sobe um pacote no heap da fila de prioridade recursivamente, 
 * trocando o pacote pelo seu pai enquanto for possível.
 */
void subir_no_heap(Fila_Prioridade *fila, int k) {
    if (k > 0 && fila->v[k].prioridade > fila->v[PAI(k)].prioridade) {
        trocar(&fila->v[k], &fila->v[PAI(k)]);
        subir_no_heap(fila, PAI(k));
    }
}

/**
 * Função que desce um pacote no heap da fila de prioridade recursivamente, 
 * trocando o pacote pelo seu filho de maior prioridade, enquanto for possível.
 */
void descer_no_heap(Fila_Prioridade *fila, int k) {
    if (F_ESQ(k) < fila->i) {
        int maior_filho = F_ESQ(k);
        if (F_DIR(k) < fila->i && 
            fila->v[F_DIR(k)].prioridade > fila->v[F_ESQ(k)].prioridade) {
            maior_filho = F_DIR(k);
        }

        if (fila->v[maior_filho].prioridade > fila->v[k].prioridade) {
            trocar(&fila->v[k], &fila->v[maior_filho]);
            descer_no_heap(fila, maior_filho);
        }
    }
}

/**
 * Função que insere um pacote na fila de prioridades de pacotes, caso haja espaço 
 * para inserção. Caso contrário, o pacote é ignorado.
 */
void inserir_pacote(Fila_Prioridade *fila, Pacote p) {    
    if (esta_cheia(fila)) 
        return;

    fila->v[fila->i] = p;
    subir_no_heap(fila, fila->i);

    fila->i++;
}

/**
 * Função que extrai o pacote com prioridade máxima da fila de prioridade e
 * mantêm as propriedades da fila de prioridade.
 */
Pacote extrair_maximo(Fila_Prioridade *fila) {
    Pacote p = fila->v[0];

    fila->i--;
    trocar(&fila->v[0], &fila->v[fila->i]);
    descer_no_heap(fila, 0);

    return p;
}

/**
 * Função que incrementa a prioridade de um pacote na posição k da fila de prioridade
 * de acordo com os seus respectivos incrementos e mantêm as propriedades da fila 
 * de prioridade.
 */
void incrementa_prioridade(Fila_Prioridade *fila, int k) {
    fila->v[k].prioridade += fila->v[k].incremento;
    if (fila->v[k].incremento > 0) {
        subir_no_heap(fila, k);
    } else if (fila->v[k].incremento < 0) {
        descer_no_heap(fila, k);
    }
}

/**
 * Função que incrementa a prioridade de todos os pacotes da fila de prioridade
 * de acordo com os seus respectivos incrementos e mantêm as propriedades da fila 
 * de prioridade.
 */
void incrementar_prioridades(Fila_Prioridade *fila) {
    for (int i = 0; i < fila->i; i++) {
        incrementa_prioridade(fila, i);
    }
}

/**
 * Função que libera toda a memória alocada dinamicamente para a criação de uma
 * fila de prioridade.
 */
void destruir_fila_prioridade(Fila_Prioridade *fila) {
    free(fila->v);
    free(fila);
}