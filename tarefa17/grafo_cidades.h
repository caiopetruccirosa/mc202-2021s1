#define TAMANHO_NOME_CIDADE 51
#define INFINITO 1000000000000

/**
 * Estrutura que armazena todos os dados associados a uma cidade, como nome,
 * quantidade de população na cidade, quantidade de população alcançada pelas 
 * vias de transporte e o fator de centralidade.
 */
struct cidade {
    char nome[TAMANHO_NOME_CIDADE];
    int qtd_populacao;
    double fator_centralidade;
    int qtd_populacao_alcancada;
} typedef Cidade;

/**
 * Estrutura que representa um grafo de cidades, onde os vértices são diferentes
 * cidades de um estado e uma aresta entre os vértices determina uma via de transporte
 * de distância igual ao peso da aresta entre as cidades.
 */
struct grafo_cidades {
    int qtd_cidades;
    Cidade *cidades;
    double **adjacencias;
} typedef Grafo_Cidades;

/**
 * Função que aloca e inicializa a memória utilizada na criação de um grafo do
 * tipo Grafo_Cidades, com n cidades.
 */
Grafo_Cidades *criar_grafo_cidades(int n);

/**
 * Função que acha o índice de uma cidade de certo nome no vetor de vértices
 * do grafo de cidades passado como parâmetro. Caso não seja possível encontrar
 * a cidade no vetor de vértices, o valor retornado é -1.
 */
int achar_indice(Grafo_Cidades *grafo, char nome[TAMANHO_NOME_CIDADE]);

/**
 * Função que calcula a distância entre todos os pares de cidades no grafo
 * utilizando o Algoritmo de Floyd-Warshal.
 */
double **calcular_distancias(Grafo_Cidades *grafo);

/**
 * Função que calcula e atribui a cada cidade o valor indicando a quantidade de
 * população que consegue alcançar cada cidade vértice do grafo, baseado em uma
 * matriz de distâncias entre todos os pares de cidades.
 */
void calcular_populacao_alcancada(Grafo_Cidades *grafo, double **distancias);

/**
 * Função que calcula e atribui a cada cidade o fator de centralidade de cada 
 * cidade vértice do grafo, baseado em uma matriz de distâncias entre todos os 
 * pares de cidades.
 */
void calcular_fatores_centralidade(Grafo_Cidades *grafo, double **distancias);

/**
 * Função que lê um grafo de cidades de acordo com o padrão de entrada descrito
 * no problema.
 */
int ler_grafo_cidades(Grafo_Cidades *grafo);

/**
 * Função que libera toda a memória alocada para a criação de um grafo 
 * do tipo Grafo_Cidades.
 */
void destruir_grafo_cidades(Grafo_Cidades *grafo);

/**
 * Função que imprime as possíveis capitais existentes em um vetor de cidades,
 * considerando que para ser um candidato a capital, pelo menos metade da 
 * população do estado precisa conseguir acessar a cidade.
 */
void imprimir_capitais(Cidade *cidades, int qtd_cidades, int populacao_total);

/**
 * Função que faz o particionamento de um vetor de cidades em duas partições baseadas em 
 * um  pivô escolhido, onde uma partição contem fatores de centralidade "menores" do que
 * o pivô e a outra contem fatores "maiores". Caso os fatores de centralidade sejam iguais,
 * o ordenação lexicografica dos nomes das cidades será considerada.
 */
int particionamento(Cidade *vetor, int inicio, int fim);

/*
 * Função que ordena um vetor de cidades utilizando o algoritmo recursivo quick_sort.
 */
void quick_sort(Cidade *vetor, int inicio, int fim);

/**
 * Função que retorna um vetor de cidades ordenadas pelo fator de 
 * centralidade e, caso necessário, pelo nome.
 * 
 * O vetor retornado de cidades é alocado dinamicamente em tempo de execução,
 * portanto é responsabilidade do usuário da função liberar a memória.
 */
Cidade *cidades_ordenadas_por_fator_centralidade(Grafo_Cidades *grafo);