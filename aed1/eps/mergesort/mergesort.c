#include <stdio.h>
#include <stdlib.h>

void merge(int *data, int *aux, int l, int m, int r, int* comparisons) {
    for (int i = l; i <= r; i++) {
        aux[i] = data[i];
    }

    int li = l;
    int ri = m + 1;

    for (int i = l; i <= r; i++) {
        if (li > m) {
            data[i] = aux[ri];
            ri += 1;
        } else if (ri > r) {
            data[i] = aux[li];
            li += 1;
        } else if (aux[li] < aux[ri]) {
            *comparisons += 1;
            data[i] = aux[li];
            li += 1;
        } else {
            *comparisons += 1;
            data[i] = aux[ri];
            ri += 1;
        }
    }
}

void mergesort(int* data, int* aux, int l, int r, int* comparisons) {
    if (l >= r) { // array of size 1
        return;
    }
    
    int m = (r - l) / 2 + l;
    
    mergesort(data, aux, l, m, comparisons);
    mergesort(data, aux, m + 1, r, comparisons);
    merge(data, aux, l, m, r, comparisons);
}

int main() {
    int *array, *aux,  n, comparisons;

    scanf("%d", &n);
    array = malloc(n * sizeof(int));
    aux = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", array + i);
    }

    comparisons = 0;
    mergesort(array, aux, 0, n - 1, &comparisons);

    for (int i = 0; i < n; i++) {
        printf("%d%c", array[i], i < n - 1 ? ' ' : '\n');
    }
    printf("Comparacoes: %d\n", comparisons);

    free(array);
    free(aux);

    return 0;
}