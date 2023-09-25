#include <assert.h>

typedef struct DiscoVoador DiscoVoador;
struct DiscoVoador {
    char *modelo;
    char *planeta;
    int autonomia;
};

int verificar_ordem_lexicografica(char* texto1, char* texto2) {
    int i = 0;
    while (texto1[i] != '\0' && texto2[i] != '\0') {
        if (texto1[i] < texto2[i]) {
            return 1;
        } else if (texto1[i] > texto2[i]) {
            return -1;
        }

        i++;
    }

    return 0;
}

int verificar_ordenacao(DiscoVoador *discos, int n_discos) {
    int resultado, ordem = 0;

    ordem = 1;
    for (int i = 1; i < n_discos; i++) {
        resultado = verificar_ordem_lexicografica(discos[i - 1].modelo, discos[i].modelo);
        if (resultado == -1) {
            ordem = 0;
            break;
        }
    }
    if (ordem == 1) return 1;

    ordem = 2;
    for (int i = 1; i < n_discos; i++) {
        resultado = verificar_ordem_lexicografica(discos[i - 1].modelo, discos[i].modelo);
        if (resultado == 1) {
            ordem = 0;
            break;
        }
    }
    if (ordem == 2) return 2;

    ordem = 3;
    for (int i = 1; i < n_discos; i++) {
        resultado = verificar_ordem_lexicografica(discos[i - 1].planeta, discos[i].planeta);
        if (resultado == -1) {
            ordem = 0;
            break;
        } else if (resultado == 0) {
            if (discos[i - 1].autonomia < discos[i].autonomia) {
                ordem = 0;
                break;
            }
        }
    }
    if (ordem == 3) return 3;
    
    ordem = 4;
    for (int i = 1; i < n_discos; i++) {
        if (discos[i - 1].autonomia > discos[i].autonomia) {
            ordem = 0;
            break;
        } else if (discos[i - 1].autonomia == discos[i].autonomia) {
            resultado = verificar_ordem_lexicografica(discos[i - 1].planeta, discos[i].planeta);
            if (resultado == -1) {
                ordem = 0;
                break;
            } else if (resultado == 0) {
                resultado = verificar_ordem_lexicografica(discos[i - 1].modelo, discos[i].modelo);
                if (resultado == -1) {
                    ordem = 0;
                    break;
                }
            }
        }
    }
    if (ordem == 4) return 4;

    return ordem;
}
