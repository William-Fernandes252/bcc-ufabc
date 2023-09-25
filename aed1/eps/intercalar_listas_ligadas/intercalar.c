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

LinkedNode* intercalar_listas(LinkedNode *inicio1, LinkedNode *inicio2) {
    if (inicio1 == NULL) {
        return inicio2;
    } else if (inicio2 == NULL) {
        return inicio1;
    }

    LinkedNode *inicio = inicio1;
    while (inicio1->next != NULL) inicio1 = inicio1->next;
    inicio1->next = inicio2;

    int inversoes = 1, temp;
    while (1) {
        inversoes = 0;
        for (LinkedNode *p = inicio; p != NULL && p->next; p = p->next) {
            if (p->data > p->next->data) {
                temp = p->next->data;
                p->next->data = p->data;
                p->data = temp;
                inversoes += 1;
            }
        }

        if (inversoes == 0) break;
    }

    return inicio;
}

int main(int argc, char const *argv[]) {
    LinkedNode *inicio1, *inicio2, *inicio3;
    inicio1 = inicio2 = inicio3 = NULL;

    inicio1 = insert(inicio1, 1);
    insert(inicio1, 2);
    insert(inicio1, 3);
    insert(inicio1, 4);
    insert(inicio1, 5);
    insert(inicio1, 6);
    insert(inicio1, 7);

    inicio2 = insert(inicio2, 10);
    insert(inicio2, 20);
    insert(inicio2, 30);

    inicio3 = intercalar_listas(inicio1, inicio2);

    return 0;
}