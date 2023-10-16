#include "trie.h"
#include <stdio.h>

int main()
{
    no *raiz = criarNo();
    adicionarPalavra("aabb", raiz);
    printf("numero de nos: %d\n", numeroDeNos(raiz));
    printf("palavra %s\n", buscaPalavra("aabb", raiz) ? "existe" : "nao existe");
    printf("numero de palavras: %d\n", numeroDePalavras(raiz));
    printf("altura: %d\n", altura(raiz));
    return 0;
}
