#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
   int data;
   LinkedNode *next;
};

typedef struct FilaDinamica FilaDinamica;
struct FilaDinamica {
   LinkedNode *inicio, *fim;
};

FilaDinamica* criar_fila() {
    FilaDinamica* fila = malloc(sizeof(FilaDinamica));
    fila->fim = fila->inicio = NULL;
    return fila;
}

int enfileirar(FilaDinamica* fila, int valor) {
    LinkedNode* item = malloc(sizeof(LinkedNode));
    item->data = valor;
    item->next = fila->fim;
    if (fila->inicio == NULL) {
        fila->inicio = fila->fim;
    }
    fila->fim = item;
    return 1;
}

int desenfileirar(FilaDinamica *fila, int *valor) {
    if (fila->inicio == NULL) return 0;

    *valor = fila->inicio->data;

    LinkedNode *trash = fila->inicio, *aux = fila->fim;
    if (fila->fim != fila->inicio) {
        while (aux->next != fila->inicio) aux = aux->next;
        fila->inicio = aux;
        fila->inicio->next = NULL;
    } else {
        fila->inicio = fila->fim = NULL;
    }
    
    free(trash);
    return 1;
}

void liberar_fila(FilaDinamica *fila, int *valor) {
    if (fila->fim == NULL) {
        free(fila);
        *valor = 1; 
        return;
    }

    LinkedNode* trash = fila->fim;
    fila->fim = fila->fim->next;
    free(trash);
    return liberar_fila(fila, valor);
}