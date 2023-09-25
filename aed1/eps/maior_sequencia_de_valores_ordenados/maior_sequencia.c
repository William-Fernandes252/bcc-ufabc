#include <stdio.h>
#include <stdlib.h>

void imprimir_lista(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

void imprimir_maior_sequencia(int lista[], int n) {
    int index_inicio = 0, index_fim = 0, maior_index_inicio = 0, maior_index_fim = 0;

    for (int i = 1; i < n; i++) {
        if (lista[i] > lista[i - 1]) {
            index_fim = i;
        } else {
            if (index_fim - index_inicio > maior_index_fim - maior_index_inicio) {
                maior_index_inicio = index_inicio;
                maior_index_fim = index_fim;
            }
            index_inicio = i;
            index_fim = i;
        }

    }
    if (index_fim - index_inicio > maior_index_fim - maior_index_inicio) {
        maior_index_inicio = index_inicio;
        maior_index_fim = index_fim;
    }

    int maior_comprimento = maior_index_fim - maior_index_inicio  + 1; 
    int* sequencia = (int*) calloc(maior_comprimento, sizeof(int));
    for (int i = 0; i < maior_comprimento; i++) {
        sequencia[i] = lista[maior_index_inicio + i];
    }

    imprimir_lista(sequencia, maior_comprimento);

    free(sequencia);
}

int main() {
    int n, *lista;
    scanf("%d", &n);

    lista = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", lista + i);
    }

    imprimir_maior_sequencia(lista, n);

    free(lista);

    return EXIT_SUCCESS;
}