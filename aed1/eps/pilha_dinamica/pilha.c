#include <stdlib.h>
#include <assert.h>

typedef struct LinkedNode LinkedNode;
struct LinkedNode {
   int data;
   LinkedNode *next;
};

typedef struct PilhaDinamica PilhaDinamica;
struct PilhaDinamica {
   LinkedNode *topo;
};

PilhaDinamica* criar_pilha() {
    PilhaDinamica* pilha = malloc(sizeof(PilhaDinamica));
    pilha->topo = NULL;
    return pilha;
}

int empilhar(PilhaDinamica* pilha, int valor) {
    LinkedNode* item = malloc(sizeof(LinkedNode));
    item->data = valor;
    item->next = pilha->topo;
    pilha->topo = item;
    return 1;
}

int desempilhar(PilhaDinamica* pilha, int* valor) {
    if (pilha->topo == NULL) return 0;

    *valor = pilha->topo->data;

    LinkedNode *trash = pilha->topo;
    pilha->topo = pilha->topo->next;
    free(trash);
    return 1;
}

void liberar_pilha(PilhaDinamica* pilha) {
    if (pilha->topo == NULL) {
        free(pilha);
        return;
    }

    LinkedNode* trash = pilha->topo;
    pilha->topo = pilha->topo->next;
    free(trash);
    return liberar_pilha(pilha);
}

int main() {
    PilhaDinamica* pilha = criar_pilha();
    int valor;
    assert(desempilhar(pilha, &valor) == 0);
    for (int i = 0; i < 10; i++) {
        assert(empilhar(pilha, i) == 1);
    }
    for (int i = 9; i >= 0; i--) {
        assert(desempilhar(pilha, &valor) == 1);
        assert(valor == i);
    }
    liberar_pilha(pilha);
    return 0;
}