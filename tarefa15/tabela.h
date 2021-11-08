#ifndef TABELA_HASH
#define TABELA_HASH

#ifndef TAMANHO_PALAVRA
#define TAMANHO_PALAVRA 51
#endif

#define QTD_PALAVRAS_MAIS_FREQUENTES 50

struct contador {
    char palavra[TAMANHO_PALAVRA]; // chave
    int contagem;                  // valor
} typedef Contador;

struct tabela_hash {
    Contador **vetor;
    int capacidade;
} typedef Tabela_Hash;

/**
 * Função de particionamento usada durante a ordenação do quick sort.
 * 
 * O critério de ordenação para os contadores do vetor é: primeiro
 * considerar o valor da contagem, em ordem decrescente; e segundo, 
 * a ordenação lexicografica das palavras associadas, em ordem crescente.
 */
int particionamento_contador(Contador *vetor, int inicio, int fim);

/**
 * Função que ordena um vetor de contadores de palavra utilizando o
 * método quick sort de maneira recursiva.
 */
void quick_sort_contador(Contador *vetor, int inicio, int fim);

/**
 * Função que cria e retorna uma tabela hash de capacidade passada.
 * 
 * Para a criação da tabela, memória associada a tabela é alocada 
 * dinamicamente, e é responsabilidade do usuário liberá-la.
 */
Tabela_Hash criar_tabela(int capacidade);

/**
 * Função que libera toda a memória alocada dinamicamente associada 
 * a uma tabela hash passada como parâmetro.
 */
void destruir_tabela(Tabela_Hash tabela);

/**
 * Função que calcula o hash de uma string.
 */
unsigned int long hash(char *palavra);

/**
 * Função que incrementa a contagem de frequência de uma palavra na tabela hash.
 * Caso, a contagem de frequência da palavra ainda não exista, inicializa um contador
 * com uma contagem.
 * 
 * A função retorna um valor booleano, indicando se foi possível ou não incrementar a
 * contagem na tabela.
 */
int incrementar_contagem(Tabela_Hash *tabela, char palavra[TAMANHO_PALAVRA]);

/**
 * Função que retorna um vetor contendo as palavras mais frequentes da tabela hash
 * passada como parâmetro.
 * 
 * A função aloca memória dinamicamente para a criação do vetor com as palavras mais
 * frequentes, portanto, é responsabilidade do usuário retorná-la.
 */
Contador *palavras_mais_frequentes(Tabela_Hash tabela);

/**
 * Função que imprime as palavras mais frequentes de uma tabela hash.
 */
void imprimir_palavras_mais_frequentes(Tabela_Hash tabela);

#endif