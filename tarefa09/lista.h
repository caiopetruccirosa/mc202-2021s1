struct no {
    int dado;
    struct no* anterior;
    struct no* proximo;
} typedef No;

/**
 * Função que lê uma lista de elementos na entrada padrão e os insere
 * sequencialmente (inserindo no fim) em uma lista circular duplamente ligada.
 * 
 * Todos os nós da lista são alocados dinamicamente, então é responsabilidade do usuário
 * liberar toda a memória alocada dinamicamente.
 */
No *ler_lista(int m);

/**
 * Função que imprime todos os elementos de uma lista duplamente ligada em uma linha.
 */
void imprimir_lista(No *fila);

/**
 * Função que destroi uma lista ligada, liberando toda a memória alocada dinamicamente
 * para a criação dos nós.
 */
void destruir_lista(No *lista);

/**
 * Função que adiciona um "dado" ao final de uma lista circular duplamente ligada.
 * 
 * É necessário passar uma referência ao ponteiro do primeiro nó da lista, que nunca 
 * deve ser NULL, pois não é possível adicionar um elemento de uma referência NULL de 
 * uma lista. Isso não significa, que o valor do primeiro nó não pode ser NULL, o que 
 * é válido, já que nesse caso a lista apenas está vazia.
 * 
 * Essa função aloca memória dinamicamente para criação do novo nó que irá armazenar o
 * dado.
 */
void adicionar(No **lista, int dado);

/**
 * Função que remove um nó de uma lista circular duplamente ligada. Para isso, se assume
 * que o nó passado faz parte da lista cuja referência é passada.
 * 
 * É necessário passar uma referência ao ponteiro do primeiro nó da lista, que nunca 
 * deve ser NULL, pois não é possível remover um elemento de uma referência NULL de 
 * uma lista. Isso não significa, que o valor do primeiro nó não pode ser NULL, o que 
 * é válido, já que nesse caso a lista apenas está vazia.
 * 
 * Essa função libera a memória alocada dinamicamente para criação do nó.
 */
void remover(No **lista, No *no);

/**
 * Função que ordena uma lista ligada que armazena inteiros, usando o algoritmo de 
 * ordenação Selection Sort.
 */
void ordernar_lista(No *lista);