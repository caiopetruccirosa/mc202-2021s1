struct conteiner {
    char tipo_mercadoria[21];
} typedef Conteiner;

struct pilha {
    Conteiner *v;
    int topo;
    int capacidade;
} typedef Pilha;

/**
 * Função que cria um pilha de conteineres vazia, de capacidade passada por parâmetro.
 */
Pilha criar_pilha(int capacidade);

/**
 * Função que empilha um conteiner em uma pilha
 */
void empilhar(Pilha *pilha, Conteiner conteiner);

/**
 * Função que desempilha um conteiner de uma pilha e retorna o valor do conteiner
 * desempilhado.
 */
Conteiner desempilhar(Pilha *pilha);

/**
 * Função que retorna um valor booleano indicando se a pilha está cheia.
 */
int eh_pilha_cheia(Pilha pilha);

/**
 * Função que retorna um valor booleano indicando se a pilha está vazia.
 */
int eh_pilha_vazia(Pilha pilha);


void imprimir_pilha(Pilha pilha);

/**
 * 
 */
int pode_carregar(Pilha pilha, char tipo_mercadoria[]);