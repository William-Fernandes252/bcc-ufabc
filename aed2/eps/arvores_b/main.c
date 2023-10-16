#include "btree.h"
#include <stdio.h>

void imprimirBTree(const btNo *raiz)
{
    if (raiz != NULL)
    {
        int i;
        for (i = 0; i < raiz->numChaves + 1; i++)
        {
            imprimirBTree(raiz->filhos[i]);
            if (i < raiz->numChaves)
            {
                printf("%d ", raiz->chaves[i]);
            }
        }

        if (!raiz->ehFolha)
        {
            printf("\n");
        }
    }
}

int main()
{
    bTree b = btCriar(3);
    btInserir(b, 10);
    btInserir(b, 10);
    btInserir(b, 9);
    btInserir(b, 8);
    btInserir(b, 7);
    btInserir(b, 6);
    btInserir(b, 5);
    btInserir(b, 4);
    btInserir(b, 3);
    btInserir(b, 2);
    btInserir(b, 1);

    printf("Altura: %d\n", btAltura(b));
    printf("Chaves: %d\n", btContaChaves(b));
    btDestruir(b);

    return 0;
}
