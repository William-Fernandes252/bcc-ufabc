#include "btree.h"
#include <stdlib.h>
#include <string.h>

int binarySearch(const int size, const int *array, const int key)
{
    int low, high, mid;

    low = -1;
    high = size;
    while (low + 1 < high)
    {
        mid = (low + high) / 2;
        if (array[mid] == key)
        {
            return mid;
        }
        else if (array[mid] < key)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
    }

    return high;
}

int intMax(int a, int b)
{
    return a > b ? a : b;
}

int getIndexUltimaChave(btNo *no)
{
    return no->numChaves - 1;
}

btNo *btCriarNo(const unsigned char maxChaves)
{
    btNo *no = (btNo *)malloc(sizeof(btNo));

    int nFilhos = maxChaves + 1;
    no->ehFolha = true;
    no->filhos = (btNo **)malloc(nFilhos * sizeof(btNo *));
    no->chaves = (int *)malloc(maxChaves * sizeof(int));
    no->numChaves = 0;
    return no;
}

bTree btCriar(const unsigned char ordem)
{
    bTree b;
    // IMPLEMENTAR!
    // DICA 1: Crie uma funcao auxiliar
    // DICA 2: Alem do no, nao esqueca de alocar a lista de chaves e filhos, de acordo com a ordem:
    //           A lista de chaves tem o tamanho da ordem (um a mais, utilizado como auxiliar)
    //           A lista de filhos tem o tamanho da ordem + 1 (um a mais, utilizado como auxiliar)
    // DICA 3: Nao esqueca de inicializar todos atributos (ver btree.h)
    b.raiz = btCriarNo(ordem);
    b.ordem = ordem;
    return b;
}

void btDestruirNo(btNo *no)
{
    if (no == NULL)
    {
        return;
    }

    if (!no->ehFolha)
    {
        for (int i = 0; i < no->numChaves + 1; i++)
        {
            btDestruirNo(no->filhos[i]);
        }
    }
    free(no->chaves);
    free(no->filhos);
    free(no);
}

void btDestruir(bTree b)
{
    if (b.raiz != NULL)
    {
        btDestruirNo(b.raiz);
    }
}

btNo *inserirInterno(btNo *raiz, const int chave, int *const mediana, const int ordem)
{
    int pos, mid;
    btNo *b2;

    pos = binarySearch(raiz->numChaves, raiz->chaves, chave);
    if (pos < raiz->numChaves && raiz->chaves[pos] == chave)
    {
        return NULL;
    }

    if (raiz->ehFolha)
    {
        for (int i = raiz->numChaves; i > pos; i--)
        {
            raiz->chaves[i] = raiz->chaves[i - 1];
        }
        raiz->chaves[pos] = chave;
        raiz->numChaves += 1;
    }
    else
    {
        b2 = inserirInterno(raiz->filhos[pos], chave, &mid, ordem);
        if (b2)
        {
            for (int i = raiz->numChaves; i > pos; i--)
            {
                raiz->chaves[i] = raiz->chaves[i - 1];
                raiz->filhos[i + 1] = raiz->filhos[i];
            }
            raiz->chaves[pos] = mid;
            raiz->filhos[pos + 1] = b2;
            raiz->numChaves += 1;
        }
    }

    if (raiz->numChaves >= ordem)
    {
        mid = raiz->numChaves / 2;
        *mediana = raiz->chaves[mid];
        b2 = btCriarNo(ordem);
        b2->numChaves = raiz->numChaves - mid - 1;
        b2->ehFolha = raiz->ehFolha;

        for (int i = mid + 1; i < raiz->numChaves; i++)
        {
            b2->chaves[i - (mid + 1)] = raiz->chaves[i];
        }
        if (!raiz->ehFolha)
        {
            for (int i = mid + 1; i < raiz->numChaves + 1; i++)
            {
                b2->filhos[i - (mid + 1)] = raiz->filhos[i];
            }
        }
        raiz->numChaves = mid;
        return b2;
    }
    else
    {
        return NULL;
    }
}

void btInserir(bTree b, int chave)
{
    btNo *b1;    // Novo nó da esquerda
    btNo *b2;    // Novo nó da direita
    int mediana; // Elemento do meio (que irá subir)

    b2 = inserirInterno(b.raiz, chave, &mediana, b.ordem);
    if (b2 != NULL) // A raiz precisa ser dividida?
    {
        // Criar nova raiz
        b1 = btCriarNo(b.ordem);
        for (int i = 0; i < b.ordem + 1; i++)
        {
            b1->filhos[i] = b.raiz->filhos[i];
            if (i < b.ordem)
            {
                b1->chaves[i] = b.raiz->chaves[i];
            }
        }
        b1->ehFolha = b.raiz->ehFolha;
        b1->numChaves = b.raiz->numChaves;
        b.raiz->ehFolha = false;
        b.raiz->numChaves = 1;
        b.raiz->chaves[0] = mediana;
        b.raiz->filhos[0] = b1;
        b.raiz->filhos[1] = b2;
    }
}

int btNoBuscar(btNo *no, int chave)
{
    if (no->numChaves < 1)
    {
        return 0;
    }

    int pos = binarySearch(no->numChaves, no->chaves, chave);
    if (pos < no->numChaves && no->chaves[pos] == chave)
    {
        return 1;
    }
    return (!no->ehFolha && btNoBuscar(no->filhos[pos], chave));
}

int btBuscar(bTree b, int chave)
{
    return btNoBuscar(b.raiz, chave);
}

int btNoAltura(btNo *no)
{
    if (no->ehFolha)
    {
        return 1;
    }

    for (int i = 0; i < no->numChaves; i++)
    {
        if (no->filhos[i] != NULL)
        {
            return 1 + btNoAltura(no->filhos[i]);
        }
    }

    return 0;
}

int btAltura(bTree b)
{
    return btNoAltura(b.raiz);
}

int btNoContaNos(btNo *no)
{
    if (no->ehFolha)
    {
        return 1;
    }

    int count = 0;
    for (int i = 0; i < no->numChaves + 1; i++)
    {
        count += btNoContaNos(no->filhos[i]);
    }

    return count + 1;
}

int btContaNos(bTree b)
{
    // IMPLEMENTAR!
    // DICA: Implemente de modo recursivo
    return btNoContaNos(b.raiz);
}

int btNoContaChaves(btNo *no)
{
    if (no == NULL)
    {
        return 0;
    }

    int count = no->numChaves;
    for (int i = 0; i < no->numChaves + 1; i++)
    {
        count += btNoContaChaves(no->filhos[i]);
    }

    return count;
}

int btContaChaves(bTree t)
{
    // IMPLEMENTAR!
    // DICA: Muito similar a funcao btContaNos
    return btNoContaChaves(t.raiz);
}
