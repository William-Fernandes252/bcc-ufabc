#include <stdio.h>

typedef struct Disco Disco;
struct Disco {
   int codigo;
   double preco;
};

void swap (Disco* a, Disco* b) {
    Disco temp = *a;

    *a = *b;
    *b = temp;
}

int partition(
    Disco *list,
    const int start,
    const int end,
    int (*compare)(Disco*, Disco*),
    int *comparisons
) {
    int p = end;
    int j = start - 1; // posição das cópias
    
    for (int i = start; i <= end - 1; i++) {
        *comparisons += 1;
        if ((*compare)(list + i, list + p)) {
            j += 1;
            swap(list + i, list + j);
        }
    }

    swap(list + j + 1, list + p);

    return j + 1;
}

void sort(
    Disco *list,
    const int start,
    const int end,
    int (*compare)(Disco*, Disco*),
    int *comparisons
) {
    if (start >= end) return;

    int p = partition(list, start, end, compare, comparisons);
    sort(list, start, end - 1, compare, comparisons);
    sort(list, p + 1, end, compare, comparisons);
}

int compare_by_chip_code (Disco* a, Disco* b) {
    return a->codigo <= b->codigo;
}

int compare_by_reverse_chip_code (Disco* a, Disco* b) {
    return a->codigo >= b->codigo;
}

int compare_by_price_and_code (Disco* a, Disco* b) {
    if (a->preco > b->preco) return 0;
    if (a->preco == b->preco) return compare_by_chip_code(a, b);
}

int quicksort(Disco *v, int n, int tipo) {
    int comparisons = 0;
    
    int (*compare)(Disco*, Disco*);
    if (tipo == 1) compare = &compare_by_chip_code;
    else if (tipo == 2) compare = &compare_by_reverse_chip_code;
    else compare = &compare_by_price_and_code;

    sort(v, 0, n - 1, compare, &comparisons);

    return comparisons;
}