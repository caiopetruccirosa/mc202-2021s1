struct no {
    struct no *recrutador;
    struct no *recrutado_dir;
    struct no *recrutado_esq;
    char nome[21];
    double investimento;
} typedef No;

/**
 * Função que cria um nó baseado em um nome e em um valor
 * de investimento inicial.
 * 
 * A função aloca memória dinamicamente para criar o nó, 
 * e é responsabilidade do usuário libera-lá.
 */
No *criar_no(char nome[21], double investimento);

/**
 * Função que libera toda a memória alocada dinamicamente 
 * durante a construção da estrutura da pirâmide.
 */
void destruir_piramide();

/**
 * Função que procura o nó de uma pessoa com um nome passado
 * dentro da estrutura da pirâmide.
 */
No *procura_pessoa(No *topo, char nome[21]);

/**
 * Função que insere um nó contendo uma pessoa recrutada baseada
 * em um nó contendo uma pessoa recrutadora.
 */
void insere_recrutado(No *recrutador, No *recrutado);

/**
 * Função que realiza um pagamento de uma pessoa recebidora para uma 
 * pessoa pagadora, baseada em uma porcentagem do investimento da 
 * pessoa pagadora.
 */
void fazer_pagamento(No *recebidora, No *pagadora, double porcentagem);

/**
 * Função que propaga o lucro de uma pessoa para todos os seus 
 * recrutadores, baseado em uma porcentagem inicial que vai 
 * decrementando conforme a propagação do lucro. 
 */
void propagar_lucro(No *pessoa, double porcentagem);

/**
 * Função que retorna a altura da pirâmide.
 */
int achar_altura(No *topo);

/**
 * Função que imprime um nível de uma pirâmide.
 */
void imprimir_nivel(No* no, int nivel, int i);

/**
 * Função que imprime uma pirâmide por completo, nível
 * por nível.
 */
void imprimir_piramide(No *piramide);