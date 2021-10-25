/**
 * 
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
 * 
 * 
 * Retorna um valor booleano indicando se foi possível contabilizar a requisições e,
 * portanto, ela foi aceita. Então, a função retorna 1 caso a requisição tenha sido aceita
 * e 0 caso contrário.
 */
int contabilizar_requisicao(Arvore_Usuario *raiz, char ip[16], int limite_requisicoes);

/**
 * 
 */
void destruir_usuarios(Arvore_Usuario raiz);