#include <stdio.h>
#include <stdlib.h>

typedef struct NoArvore NoArvore;
struct NoArvore {
    int chave;
    NoArvore *esq, *dir;
};

typedef struct NoLista NoLista;
struct NoLista {
    int valor;
    struct NoLista *prox;
};

void lista_free(struct NoLista* inicio) {
    struct NoLista *aux;

    while (inicio != NULL) {
        aux = inicio;
        inicio = inicio->prox;
        free(aux);
    }
}

int lista_search(NoLista* inicio, int valor) {
    for (NoLista* p = inicio; p != NULL; p = p->prox) {
        if (p->valor == valor) return 1;
    }
    return 0;
}

void flatten_btree_inorder(NoArvore *root, struct NoLista **inicio, struct NoLista **fim) {
    if (root == NULL) return;

    flatten_btree_inorder(root->esq, inicio, fim);

    struct NoLista* NoArvorede = (struct NoLista*) malloc(sizeof(struct NoLista));
    NoArvorede->valor = root->chave;
    NoArvorede->prox = NULL;

    if (*fim == NULL) {
        *inicio = NoArvorede;
    } else {
        (*fim)->prox = NoArvorede;
    }
    *fim = NoArvorede;

    flatten_btree_inorder(root->dir, inicio, fim);    
}

int qtd_chaves_comuns(NoArvore *raiz1, NoArvore *raiz2) {
    if (raiz1 == NULL || raiz2 == NULL) {
        return 0;
    }

    struct NoLista *inicio1 = NULL, *fim1 = NULL;
    flatten_btree_inorder(raiz1, &inicio1, &fim1);
    struct NoLista *inicio2 = NULL, *fim2 = NULL;
    flatten_btree_inorder(raiz2, &inicio2, &fim2);

    int chaves_comuns_count = 0;
    for (NoLista* p = inicio1; p != NULL; p = p->prox) {
        if (lista_search(inicio2, p->valor)) chaves_comuns_count++;
    }

    lista_free(inicio1);
    lista_free(inicio2);

    return chaves_comuns_count;
}