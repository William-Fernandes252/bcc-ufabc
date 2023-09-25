#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct NoArvore NoArvore;
struct NoArvore {
    char *chave;
    NoArvore *esq, *dir;
};

NoArvore *inserir(NoArvore *raiz, char *chave_nova) {
    char* chave = malloc(sizeof(char) * 100);
    strcpy(chave, chave_nova);

    if (raiz == NULL) {
        raiz = malloc(sizeof(NoArvore));
        raiz->chave = chave;
        raiz->esq = NULL;
        raiz->dir = NULL;
    } else if (strcmp(chave_nova, raiz->chave) < 0) {
        raiz->esq = inserir(raiz->esq, chave_nova);
    } else {
        raiz->dir = inserir(raiz->dir, chave_nova);
    }

    return raiz;
}

NoArvore* find_no_minimo(NoArvore* raiz) {
    if (raiz->esq == NULL) {
        return raiz;
    }

    return find_no_minimo(raiz->esq);
}

NoArvore *remover(NoArvore *raiz, char *chave) {
    if (raiz == NULL) {
        return NULL;
    } 

    int cmp_result = strcmp(chave, raiz->chave);
    if (cmp_result < 0) {
        raiz->esq = remover(raiz->esq, chave);
    } else if (cmp_result > 0) {
        raiz->dir = remover(raiz->dir, chave);
    } else {
        if (raiz->dir == NULL) {
            NoArvore* filho = raiz->esq;
            free(raiz->chave);
            free(raiz);
            return filho;
        }
        if (raiz->esq == NULL) {
            NoArvore* filho = raiz->dir;
            free(raiz->chave);
            free(raiz);
            return filho;
        }
        NoArvore* folha_minima = find_no_minimo(raiz->dir);

        raiz->chave = folha_minima->chave;
        raiz->dir = remover(raiz->dir, folha_minima->chave);
    }

    return raiz;
}

NoArvore *buscar(NoArvore *raiz, char *chave) {
    if (raiz != NULL) {
        int cmp_result = strcmp(chave, raiz->chave);
        if (cmp_result < 0) return buscar(raiz->esq, chave);
        else if (cmp_result > 0) return buscar(raiz->dir, chave);
        else return raiz;
    }

    return NULL;
}

void liberar_arvore(NoArvore *raiz) {
    if (raiz == NULL) return;

    free(raiz->chave);
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);

    free(raiz);
}

int main() {
    NoArvore* raiz = inserir(NULL, "foda");
    inserir(raiz, "Caramba");
    inserir(raiz, "ah");
    inserir(raiz, "doy,");
    inserir(raiz, "Die Hard");
    liberar_arvore(raiz);
    return 0;
}