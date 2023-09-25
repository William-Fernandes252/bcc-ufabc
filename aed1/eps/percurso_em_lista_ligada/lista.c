#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
   int data;
   LinkedNode *next;
};

LinkedNode* insert(LinkedNode *inicio, int value) {
    LinkedNode* next = malloc(sizeof(LinkedNode));
    next->data = value;
    next->next = NULL;

    while (inicio != NULL && inicio->next != NULL) {
        inicio = inicio->next;
    }

    if (inicio == NULL) {
        inicio = next;
    } else {
        inicio->next = next;
    }

    return inicio;
}

void contar(LinkedNode *inicio, int *qtd, int *soma) {
    LinkedNode *atual;

    *qtd = 0;
    *soma = 0;
    if (inicio == NULL) return;
    while (1) {
        atual = inicio;
        *qtd += 1;
        *soma += atual->data;

        inicio = inicio->next;
        if (inicio == NULL) break;
    } 
}

void imprimir1(LinkedNode *inicio) {
    do {
        printf("%d", inicio->data);
        if (inicio->next != NULL) printf(" ");
    } while ((inicio = inicio->next) != NULL);
    printf("\n");
}

void imprimir2(LinkedNode *inicio) {
    int qtd, count, i; 
    contar(inicio, &qtd, &count);

    int *valores_lista = malloc(sizeof(int) * qtd);
    i = 0;
    do {
        valores_lista[i] = inicio->data;
        i += 1;
    } while ((inicio = inicio->next) != NULL);

    i -= 1;
    while (i >= 0) {
        printf("%d", valores_lista[i]);
        if (i != 0) {
            printf(" ");
        }
        i -= 1;
    }
    printf("\n");

    free(valores_lista);
}

int main(int argc, char const *argv[]) {
    LinkedNode* inicio = malloc(sizeof(LinkedNode));
    inicio = NULL;

    inicio = insert(inicio, 1);
    insert(inicio, 2);
    insert(inicio, 3);

    int qtd, soma;
    contar(inicio, &qtd, &soma);
    assert(qtd == 3);
    assert(soma == 6);
    imprimir2(inicio);

    return 0;
}
