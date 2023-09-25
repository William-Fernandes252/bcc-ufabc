#include <stdio.h>
#include <stdlib.h>

typedef struct NoArvore NoArvore;
struct NoArvore {
    int chave;
    NoArvore *esq, *dir;
};

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

int sucessor(NoArvore *raiz, int chave) {
    if (raiz == NULL) return -1;

    struct NoLista *inicio = NULL, *fim = NULL;
    flatten_btree_inorder(raiz, &inicio, &fim);

    for (struct NoLista* p = inicio; p != NULL; p = p->prox) {
        if (p->valor == chave && p->prox != NULL) {
            return p->prox->valor;
        } 
    }

    lista_free(fim);

    return -1;
}

int antecessor(NoArvore *raiz, int chave) {
    if (raiz == NULL) return -1;

    struct NoLista *inicio = NULL, *fim = NULL;
    flatten_btree_inorder(raiz, &inicio, &fim);

    for (struct NoLista* p = inicio; p != NULL; p = p->prox) {
        if (p->prox != NULL && p->prox->valor == chave) {
            return p->valor;
        } 
    }

    lista_free(fim);

    return -1;
}

int main() {
    struct NoArvore *raiz = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->chave = 4;
    raiz->esq = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->esq->chave = 2;
    raiz->esq->esq = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->esq->esq->chave = 1;
    raiz->esq->esq->esq = NULL;
    raiz->esq->esq->dir = NULL;
    raiz->esq->dir = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->esq->dir->chave = 3;
    raiz->esq->dir->esq = NULL;
    raiz->esq->dir->dir = NULL;
    raiz->dir = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->dir->chave = 6;
    raiz->dir->esq = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->dir->esq->chave = 5;
    raiz->dir->esq->esq = NULL;
    raiz->dir->esq->dir = NULL;
    raiz->dir->dir = (NoArvore*) malloc(sizeof(NoArvore));
    raiz->dir->dir->chave = 7;
    raiz->dir->dir->esq = NULL;
    raiz->dir->dir->dir = NULL;

    printf("%d\n", sucessor(raiz, 1));

    return 0;
}