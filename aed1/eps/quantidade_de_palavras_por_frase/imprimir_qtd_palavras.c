#include <assert.h>
#include <stdio.h>

void imprimir_qtd_palavras(char texto[]) {
    int palavras = 0, i = 0;
    char caractere;

    if (texto[0] == '\0') {
        printf("%d\n", palavras);
    }

    palavras = 1;
    while ((caractere = texto[i]) != '\0') {
        if (caractere == ' ') {
            do {
                i += 1;
            } while ((caractere = texto[i]) == ' ');

            if (caractere != '.') {
                palavras += 1;
            }
        }

        if (caractere == '.') {
            printf("%d\n", palavras);
            palavras = 0;
        }
        
        i += 1;
    }
}

int main() {
    char texto[10000];
    fgets(texto, 10000, stdin);
    imprimir_qtd_palavras(texto);
    return 1;
}