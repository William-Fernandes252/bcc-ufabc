#include "trie.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
    no *raiz = criarNo();
    adicionarPalavra("aabb", raiz);
    printf("numero de nos: %d\n", numeroDeNos(raiz));
    printf("numero de palavras: %d\n", numeroDePalavras(raiz));
    printf("altura: %d\n", altura(raiz));
    return 0;
}
