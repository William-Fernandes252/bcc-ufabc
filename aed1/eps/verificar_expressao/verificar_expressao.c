#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAX_EXPRESSION_SIZE 10000

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

char get_caractere_correspondente(char caractere) {
    if (caractere == '(') return ')';
    if (caractere == '{') return '}';
    if (caractere == '[') return ']';
    return caractere;
}

int verificar_expressao(char expressao[]) {
    int caractere_correspondente, resultado = 1;
    PilhaDinamica* pilha_caracteres = criar_pilha();

    for (int i = 0; expressao[i] != '\n'; i++) {
        if (expressao[i] == '(' || expressao[i] == '{' || expressao[i] == '[') {
            empilhar(pilha_caracteres, get_caractere_correspondente(expressao[i]));
        } else if (expressao[i] == ')' || expressao[i] == '}' || expressao[i] == ']') {
            if (
                desempilhar(pilha_caracteres, &caractere_correspondente) != 1 ||
                (char) caractere_correspondente != expressao[i]) {
                resultado = 0;
                break;
            };
        }
    }

    if (desempilhar(pilha_caracteres, &caractere_correspondente) != 0) {
        resultado = 0;
    }

    liberar_pilha(pilha_caracteres);

    return resultado;
}

int main() {
    char expressao[MAX_EXPRESSION_SIZE];
    fgets(expressao, MAX_EXPRESSION_SIZE - 1, stdin);
    printf("%s", verificar_expressao(expressao) == 1 ? "SIM" : "NAO");
    return 0;
}