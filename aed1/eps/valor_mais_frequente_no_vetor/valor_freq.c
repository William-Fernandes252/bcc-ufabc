#include <assert.h>

int valor_frequente(int v[], int n) {
    int ocorrencias[n], mais_frequente_id = 0, max_ocorrencias = 0; 

    for (int i = 0; i < n; i++) {
        ocorrencias[i] = 0;
        for (int j = 0; j < n; j++) {
            if (v[j] == v[i]) ocorrencias[i] += 1;
        }
    }

    for (int i = 0; i < n; i++) {
        if (ocorrencias[i] > max_ocorrencias) {
            max_ocorrencias = ocorrencias[i];
            mais_frequente_id = i;
        }
    }

    return v[mais_frequente_id];
}

int main() {
    int v[5] = {1, 1, 2, 3, 2, 2, 2};
    assert(valor_frequente(v, 5) == 2);
    return 0;
}