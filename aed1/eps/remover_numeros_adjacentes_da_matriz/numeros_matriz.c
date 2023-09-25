#include <stdlib.h>
#include <stdio.h>

void remover_numeros_matriz(int l, int c, int n_linhas, int n_colunas, int m[n_linhas][n_colunas]) {
    int valor = m[l][c];

    m[l][c] = 0;
    if (c - 1 > 0 && m[l][c - 1] == valor) {
        remover_numeros_matriz(l, c - 1, n_linhas, n_colunas, m);
    }
    if (c + 1 < n_colunas && m[l][c + 1] == valor) {
        remover_numeros_matriz(l, c + 1, n_linhas, n_colunas, m);
    }
    if (l - 1 > 0 && m[l - 1][c] == valor) {
        remover_numeros_matriz(l - 1, c, n_linhas, n_colunas, m);
    }
    if (l + 1 < n_linhas && m[l + 1][c] == valor) {
        remover_numeros_matriz(l + 1, c, n_linhas, n_colunas, m);
    }
}

int main() {
    int m[5][5] = {
        {11, 22, 33, 22, 55},
        {22, 22, 22, 11, 11},
        {22, 22, 33, 44, 11},
        {11, 22, 22, 22, 22},
        {11, 11, 11, 22, 55}
    };

    remover_numeros_matriz(2, 0, 5, 5, m);
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", m[i][j]);
        }
        puts("");
    }

    return EXIT_SUCCESS;
}