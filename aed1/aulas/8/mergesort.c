#include <stdio.h>
#include <stdlib.h>

void merge(int *data, int *aux, int l, int m, int r) {
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
            data[i] = aux[li];
            li += 1;
        } else {
            data[i] = aux[ri];
            ri += 1;
        }
    }
}

void mergesort(int* data, int* aux, int l, int r) {
    if (l >= r) { // array of size 1
        return;
    }
    
    int m = (r - l) / 2 + l;
    
    mergesort(data, aux, l, m);
    mergesort(data, aux, m + 1, r);
    merge(data, aux, l, m, r);
}

void print_array(int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    puts("");
}

int main() {
    int size;

    scanf("%d", &size);
    int *data = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        scanf("%d", data + i);
    }

    int *aux = malloc(size * sizeof(int));

    mergesort(data, aux, 0, size - 1);

    print_array(data, size);

    return 0;
}