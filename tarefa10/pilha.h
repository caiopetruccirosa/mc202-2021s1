typedef char Mercadoria[21];

struct pilha {
    Mercadoria *v;
    int topo;
    int capacidade;
} typedef Pilha;

/**
 * Função que cria um pilha vazia, de capacidade passada por parâmetro.
 */
Pilha criar_pilha(int capacidade);

/**
 * Função que empilha um conteiner de mercadoria em uma pilha e retorna
 * um valor booleano indicando se foi possível ou não empilhar.
 */
int empilhar(Pilha *pilha, Mercadoria m);

/**
 * Função que desempilha um conteiner de mercadoria em uma pillha e retorna
 * um valor booleano indicando se foi possível ou não desempilhar.
 */
int desempilhar(Pilha *pilha);