#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void quantidade_discos(char **discos, int n_discos, int **quantidade_por_fabricante) {
    char c;
    int *q = malloc(4 * sizeof(int));

    for (int i = 0; i < n_discos; i++) {
        int j = 0;
        while ((c = discos[i][j]) != '\0') {
            if (c == '_') {
                q[discos[i][j + 1] - 'A'] += 1;
            }

            j += 1;
        }
    }

    *quantidade_por_fabricante = q;
}

int main() {
    int *quantidade_por_fabricante;
    char **discos = malloc(4 * sizeof(char*));
    discos[0] = "Modelo_A1\0";
    discos[1] = "Modelo_B1\0";
    discos[2] = "Modelo_C1\0";
    discos[3] = "Modelo_D1\0";

    quantidade_discos(discos, 4, &quantidade_por_fabricante);
    for (int i = 0; i < 4; i++) {
        assert(quantidade_por_fabricante[i] == 1);
    }

    return EXIT_SUCCESS;
}