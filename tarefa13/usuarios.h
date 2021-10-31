/**
 * Estrutura que contêm os dados de um nó de uma árvore de usuários.
 */
struct no_usuario {
    struct no_usuario *esquerda;
    struct no_usuario *direita;
    int altura;
    char ip[16];
    int qtd_requisicoes;
} typedef No_Usuario;

typedef No_Usuario* Arvore_Usuario;

/**
 * Função que contabiliza mais uma requisição para um determinado usuário associado
 * a um IP passado por parâmetro. Caso o usuário não tenha feito uma requisição ainda,
 * um novo nó é criado para ele e ele é inserido na árvore. Esse nó é criado utilizando
 * alocação dinâmica de memória que deve ser liberada posteriormente.
 * 
 * Retorna um valor booleano indicando se foi possível contabilizar a requisições e,
 * portanto, ela foi aceita. Então, a função retorna 1 caso a requisição tenha sido aceita
 * e 0 caso contrário.
 */
int contabilizar_requisicao(Arvore_Usuario *raiz, char ip[16], int limite_requisicoes);

/**
 * Função que libera recursivamente toda a memória alocada dinamicamente contida 
 * dentro de uma árvore de usuários, partindo de um nó raiz.
 */
void destruir_usuarios(Arvore_Usuario raiz);