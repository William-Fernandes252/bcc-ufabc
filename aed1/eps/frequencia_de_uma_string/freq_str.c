#include <assert.h>
#include <stdio.h>

void frequencia_string(const char *str, const char *texto, int *qtd) {
    #define TOLOWER(c) c >= 97 ? c : c + 32

    int comprimento_str = 0, i = 0, ocorrencia_encontrada = 0;
    while (1) {
        if (str[i] != '\0') {
            comprimento_str += 1;
            i += 1;
        } else {
            break;
        }
    }

    i = 0;
    *qtd = 0;
    char caractere_texto, caractere_str;
    while (texto[i] != '\0') {
        caractere_texto = TOLOWER(texto[i]);
        caractere_str = TOLOWER(str[0]);
        if (caractere_texto == caractere_str) {
            ocorrencia_encontrada = 1;
            for (int j = i, k = 0; j < comprimento_str + i && texto[j] != '\0'; j++, k++) {
                caractere_texto = TOLOWER(texto[j]);
                caractere_str = TOLOWER(str[k]);
                if (caractere_texto != caractere_str) ocorrencia_encontrada = 0;    
            }

            if (ocorrencia_encontrada) *qtd += 1;
        }

        i += 1;
    }
}

int main() {
    char texto[] = "texto, textos, TEXTO\0";
    char str[] = "Texto\0";
    int qtd;
    frequencia_string(str, texto, &qtd);
    assert(qtd == 3);
    return 0;
}