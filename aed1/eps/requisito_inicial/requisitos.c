#include <stdlib.h>

typedef struct Disciplina Disciplina;
struct Disciplina {
    int cod;
    char *nome;
    int creditos;
    Disciplina *requisito;
};

Disciplina *requisito_inicial(Disciplina *disciplina, int *qtd) {
    *qtd = 0;
    Disciplina* requisito; 
    while (1) {
        requisito = disciplina;
        disciplina = disciplina->requisito;
        if (disciplina == NULL) break;

        *qtd += 1;
    }

    if (*qtd == 0) return NULL;
    return requisito;
}