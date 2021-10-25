/**
 * 
 */
struct dominio {
    char nome[101];
    char ip[16];
} typedef Dominio;

/**
 * 
 */
struct no_dominio {
    struct no_dominio* esquerda;
    struct no_dominio* direita;
    int altura;
    Dominio dominio;
} typedef No_Dominio;

typedef No_Dominio* Arvore_Dominio;

/**
 * Função que lê os dados de um domínio (nome do domínio e o seu IP)
 * a partir da entrada padrão e retorna uma struct contendo os dados.
 */
Dominio ler_dominio();

/**
 * Função que lê uma Árvore AVL de domínios a partir da entrada padrão e
 * retorna um ponteiro para o nó raiz da árvore.
 */
Arvore_Dominio ler_dominios(int n);

/**
 * Função que insere um domínio passado como parâmetro em uma Árvore AVL cuja
 * raiz deve ser passada por parâmetro como um ponteiro de ponteiro, sendo
 * uma referência para o ponteiro da raiz.
 * 
 * Essa função aloca memória dinamicamente para expansão da AVL,
 * que deve ser liberada depois.
 */
void inserir_dominio(Arvore_Dominio *raiz, Dominio dominio);

/**
 * Função que busca um domínio armazenado em uma Árvore AVL de domínios com
 * base no nome do domínio e retorna um ponteiro para o domínio.
 * Deve ser passado a raiz da árvore onde a busca será realizada e o
 * domínio como uma string.
 */
Dominio *buscar_dominio(Arvore_Dominio raiz, char dominio[101]);

/**
 * Função que libera toda a memória alocada dinamicamente existente
 * em uma Árvore AVL cuja raiz deve ser passada como parâmetro.
 */
void destruir_dominios(Arvore_Dominio raiz);