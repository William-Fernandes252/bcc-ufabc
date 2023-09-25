#include <stdlib.h>
#include <stdio.h>

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
   int data;
   LinkedNode *next;
};

typedef struct DLinkedNode DLinkedNode;
struct DLinkedNode {
   int data;
   DLinkedNode *next, *prev;
};

void duplicar_pares1(LinkedNode *inicio) {
    LinkedNode* node;

    for (LinkedNode* p = inicio; p != NULL; p = p->next) {
        if (p->data % 2 == 0) {
            node = malloc(sizeof(LinkedNode));
            node->data = p->data;
            node->next = p->next;
            p->next = node;
            p = p->next;
        }
    }
}

void duplicar_pares2(DLinkedNode *inicio) {
    DLinkedNode* node;

    for (DLinkedNode* p = inicio; p != NULL; p = p->next) {
        if (p->data % 2 == 0) {
            node = malloc(sizeof(DLinkedNode));
            node->data = p->data;
            node->next = p->next;
            if (p->next != NULL) p->next->prev = node;
            node->prev = p;
            p->next = node;
            p = p->next;
        }
    }
}

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

int main() {
    LinkedNode *inicio;
    inicio = NULL;

    inicio = insert(inicio, 1);
    insert(inicio, 2);
    insert(inicio, 3);
    insert(inicio, 4);
    insert(inicio, 5);
    insert(inicio, 6);
    insert(inicio, 7);
    insert(inicio, 14);

    duplicar_pares1(inicio);

    for (LinkedNode* p = inicio; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }

    return 0;
}