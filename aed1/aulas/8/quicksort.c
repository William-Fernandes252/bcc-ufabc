#include <stdio.h>
#include <stdlib.h>

void swap (int* data, int i, int j) {
    int temp = data[i];

    data[i] = data[j];
    data[j] = temp;
}

int partition(int* data, int low, int high) {
    int p =  high;
    int j = low; // posição das cópias
    
    for (int i = low; i <= high - 1; i++) {
        if (data[i] <= data[p]) {
            swap(data, j, i);
            j += 1;
        }
    }
    swap(data, p, j);

    return p;
}

void quicksort(int* data, int low, int high) {
    if (low >= high) {
        return;
    }

    int p = partition(data, low, high);
    quicksort(data, low, p - 1);
    quicksort(data, p + 1, high);
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

    quicksort(data, 0, size - 1);

    print_array(data, size);

    return 0;
}
