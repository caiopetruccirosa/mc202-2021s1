/**
 * Estrutura (struct) de uma Pessoa, contendo informações como número de 
 * documento, profissão e estado de vacinação da pessoa.
 */
struct pessoa {
    int numero_documento;
    char profissao[26];
    char estado_vacinacao[13];
} typedef Pessoa;

/**
 * Estrutura (struct) de um Nó de Pessoa, que pode ser usado em uma lista
 * ligada simples ou uma fila por exemplo.
 */
struct no {
    Pessoa* pessoa;
    struct no* proximo;
} typedef No;

/**
 * Estrutura (struct) de uma Fila de Pessoa, que segue as regras de uma fila
 * de boate, ou seja, contem ponteiros para o ínicio, fim e o nó da fila que
 * está a pessoa com a lanterna.
 */
struct fila {
    No* inicio;
    No* lanterna;
    No* fim;
} typedef Fila;

/**
 * Função responsável por alocar e inicializar uma struct do tipo Fila e retornar
 * um ponteiro para a estrutura. Portanto, a estrutura foi alocada dinamicamente e é
 * responsabilidade do usuário liberar a memória envolvida.
 */
Fila *criar_fila();

/**
 * Função responsável por liberar toda a memória que envolve a struct do tipo Fila, 
 * liberando a própria estrutura assim como todos os nós e os dados armazenados nela.
 */
void destruir_fila(Fila *fila);

/**
 * Função responsável por alocar e inicializar uma struct do tipo No, a partir de
 * uma struct do tipo Pessoa e retornar um ponteiro para a estrutura. Portanto, a 
 * estrutura foi alocada dinamicamente e é responsabilidade do usuário liberar a 
 * memória envolvida.
 */
No *criar_no(Pessoa pessoa);

/**
 * Função responsável por liberar toda a memória que envolve a struct do tipo No, 
 * liberando a própria estrutura assim como a estrutura do dado associado a esse nó.
 */
void destruir_no(No *no);

/**
 * Função que retorna uma struct do tipo Pessoa baseado em valor associados passados
 * como parâmetro para a função, como o número do documento, a profissão e o estado
 * de vacinação da pessoa.
 */
Pessoa criar_pessoa(int numero_documento, char profissao[26], char estado_vacinacao[13]);

/**
 * Função que lê os dados de uma fila de pessoas da entrada padrão (stdin).
 */
Fila *ler_fila();

/**
 * Função que imprime os dados de uma fila de pessoas na saída padrão (stdout).
 */
void imprimir_fila(Fila *fila);

/**
 * Função responsável por enfileirar uma pessoa em uma fila, baseado em todas as regras
 * de enfileiramento e de como a fila funciona. Portanto, enfileirar uma nova pessoa
 * pode causar na saída de outras pessoas ou mudar a organização da fila, já que nem
 * todas as pessoas entram na mesma posição da fila como no fim.
 * 
 * São passados como parâmetros para a função um ponteiro para a fila que deve ser
 * incrementada e o valor contendo os dados da pessoa em uma struct do tipo Pessoa.
 */
void enfileirar(Fila *fila, Pessoa pessoa);

/**
 * Função responsável por desenfileirar uma pessoa, removendo a do ínicio e retornando
 * os dados dessa pessoa ao usuário.
 * 
 * Essa função foi implementada por propósitos de implementação padrão de estruturas 
 * como filas.
 */
Pessoa desenfileirar(Fila *fila);