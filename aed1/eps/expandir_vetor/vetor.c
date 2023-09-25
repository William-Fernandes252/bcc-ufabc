#include <stdlib.h>
#include <stdio.h>

int *expandir_vetor(const int *vetor, int n_compactado, int *n_expandido) {
    int *vetor_expandido = malloc(sizeof(int));
    int valor_para_expandir, n_expandido_antigo;

    *n_expandido = 0;
    for (int i = 0; i < n_compactado; i++) {
        if (i % 2 == 0) {
            valor_para_expandir = vetor[i];
            continue;
        } 

        n_expandido_antigo = *n_expandido;
        *n_expandido = *n_expandido + vetor[i];
        vetor_expandido = realloc(vetor_expandido, *n_expandido * sizeof(int));
        for (int j = n_expandido_antigo; j < *n_expandido; j++) {
            vetor_expandido[j] = valor_para_expandir;
        }
    }

    return vetor_expandido;
}

int main() {
    int v[] = {10, 5, 50, 2, 10, 3, 90, 1}, n_expandido;
    int *ev = expandir_vetor(v, 8, &n_expandido);
    for(int i = 0; i < n_expandido; i++) {
        printf("%d\n", ev[i]);
    }
    return EXIT_SUCCESS;
}