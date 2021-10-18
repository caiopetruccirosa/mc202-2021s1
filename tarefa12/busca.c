#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------ Oferta de Item ------------ */

/* Struct que representa uma oferta de um item */
struct oferta {
    char loja[15];
    int codigo;
    double valor;
} typedef Oferta;

/* Função que lê uma oferta da entrada padrão e retorna a struct associada */
Oferta ler_oferta() {
    Oferta oferta = {};
    scanf("%s %d %lf", oferta.loja, &oferta.codigo, &oferta.valor);
    return oferta;
}

/* ------------ Lista Duplamente Ligada ------------ */

/* Struct representa um nó de uma lista duplamente ligada de ofertas */
struct no_lista {
    Oferta oferta;
    struct no_lista *anterior;
    struct no_lista *proximo;
} typedef No_Lista;

/* Função que cria e retorna um nó baseado em uma oferta passada como parâmetro. 
   Para isso, memória é alocada dinamicamente, e é responsabilidade do usuário liberá-la. */
No_Lista *criar_no_lista(Oferta oferta) {
    No_Lista *no = malloc(sizeof(No_Lista));
    no->oferta = oferta;
    no->anterior = no->proximo = NULL;

    return no;
}

/* Função recursiva que libera a memória de todos os nós de uma lista de ofertas */
void destruir_lista(No_Lista *lista) {
    if (lista == NULL) {
        return;
    }

    destruir_lista(lista->proximo);
    free(lista);

    return;
}

/* Função que insere uma oferta de maneira ordenada em uma lista duplamente ligada. Após 
   a inserção, a função retorna um ponteiro para o novo nó (ou não novo) "cabeça" da lista */
No_Lista *inserir_na_lista(No_Lista *lista, Oferta oferta) {
    No_Lista *no = criar_no_lista(oferta);
    
    if (lista == NULL) {
        return no;
    } else if (strcmp(oferta.loja, lista->oferta.loja) < 0) {
        no->proximo = lista;
        lista->anterior = no;
        return no;
    } else {
        No_Lista *anterior = lista;
        while(anterior->proximo != NULL && strcmp(anterior->proximo->oferta.loja, oferta.loja) < 0) {
            anterior = anterior->proximo;
        }

        if (anterior->proximo == NULL) {
            anterior->proximo = no;
            no->anterior = anterior;
        } else {
            No_Lista *proximo = anterior->proximo;
            
            no->anterior = anterior;
            no->proximo = proximo;

            anterior->proximo = no;
            proximo->anterior = no;
        }

        return lista;
    }
}

/* ------------ Árvore Binária de Busca ------------ */

/* Struct que representa um nó de uma árvore binária de busca, onde cada
   nó armazena uma referencia a uma lista de ofertas associadas a um tipo 
   de item de determinado código. */
struct no_arvore {
    int codigo_item;
    No_Lista *lista_ofertas;
    struct no_arvore *esquerda;
    struct no_arvore *direita;
} typedef No_Arvore;

/* Função que cria e retorna um nó de uma árvore de ofertas, armazenando 
   a oferta na lista associada ao nó. */
No_Arvore *criar_no_arvore(Oferta oferta) {
    No_Arvore *no = malloc(sizeof(No_Arvore));
    no->esquerda = no->direita = NULL;
    no->codigo_item = oferta.codigo;
    no->lista_ofertas = inserir_na_lista(NULL, oferta);

    return no;
}

/* Função recursiva que libera a memória associada a todos os nós de uma 
   árvore binária de busca de ofertas */
void destruir_arvore(No_Arvore *raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_arvore(raiz->esquerda);
    destruir_arvore(raiz->direita);
    destruir_lista(raiz->lista_ofertas);
    free(raiz);

    return;
}

/* Função recursiva que insere uma nova oferta em uma árvore binária
   de busca de lista de ofertas. Após a inserção, a função retorna um 
   ponteiro para o novo nó (ou não novo) "raiz" da árvore. */
No_Arvore *inserir_na_arvore(No_Arvore *raiz, Oferta oferta) {
    if (raiz == NULL) {
        raiz = criar_no_arvore(oferta);
    } else if (oferta.codigo == raiz->codigo_item) {
        raiz->lista_ofertas = inserir_na_lista(raiz->lista_ofertas, oferta);
    } else if (oferta.codigo < raiz->codigo_item) {
        raiz->esquerda = inserir_na_arvore(raiz->esquerda, oferta);
    } else if (oferta.codigo > raiz->codigo_item) {
        raiz->direita = inserir_na_arvore(raiz->direita, oferta);
    }

    return raiz;
}

/* Função recursiva que busca uma lista de ofertas a partir de um
   código de item em uma árvore binária de busca. Caso nenhuma lista
   seja encontrada, o ponteiro retornado é de valor nulo. */
No_Lista *achar_na_arvore(No_Arvore *raiz, int codigo_item) {
    if (raiz == NULL) {
        return NULL;
    } else if (raiz->codigo_item == codigo_item) {
        return raiz->lista_ofertas;
    } else if (codigo_item < raiz->codigo_item) {
        return achar_na_arvore(raiz->esquerda, codigo_item);
    } else {
        return achar_na_arvore(raiz->direita, codigo_item);
    }
}

/* ------------ Funções específicas ------------ */

/* Função que filtra uma lista de ofertas associadas a um item, a partir de um valor 
   da faixa de ofertas e retorna uma sublista contendo as ofertas dentro da faixa.  */
No_Lista *filtar_ofertas_na_faixa(No_Arvore *ofertas, int codigo_item, double valor) {
    No_Lista *na_faixa = NULL;

    No_Lista *lista_ofertas = achar_na_arvore(ofertas, codigo_item);
    for (No_Lista *no = lista_ofertas; no != NULL; no = no->proximo) {
        Oferta oferta = no->oferta;
        if (oferta.valor <= valor * 1.1) {
            na_faixa = inserir_na_lista(na_faixa, oferta);
        }
    }

    return na_faixa;
}

/* Função que imprime uma lista de ofertas associadas a um item de
   determinado código. Caso a lista de ofertas não exista ou esteja
   vazia, é impressa uma mensagem indicando isso. */
void imprimir_ofertas(No_Lista *ofertas, int codigo_item) {
    printf("OFERTAS para %d:\n", codigo_item);

    if (ofertas != NULL) {
        for (No_Lista *no = ofertas; no != NULL; no = no->proximo) {
            Oferta oferta = no->oferta;
            printf("%s %d %.2lf\n", oferta.loja, oferta.codigo, oferta.valor);
        }
    } else {
        printf("nenhuma boa oferta foi encontrada\n");
    }

    printf("\n");

    return;
}

int main() {
    No_Arvore *ofertas = NULL;

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        Oferta oferta = ler_oferta();
        ofertas = inserir_na_arvore(ofertas, oferta);
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int codigo_item;
        double valor;
        scanf("%d %lf", &codigo_item, &valor);

        No_Lista *na_faixa = filtar_ofertas_na_faixa(ofertas, codigo_item, valor);
        
        imprimir_ofertas(na_faixa, codigo_item);

        destruir_lista(na_faixa);
    }

    destruir_arvore(ofertas);
    
    return 0;
}