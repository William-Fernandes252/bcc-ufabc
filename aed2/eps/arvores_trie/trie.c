#include "trie.h"

// DICA: Estude o arquivo trie.h antes de iniciar a sua implementacao!

no *criarNo(void)
{
    no *novoNo = (no *)malloc(sizeof(no));
    novoNo->tipo = 'I';
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        novoNo->filho[i] = NULL;
    }
    return novoNo;
}

void apagarArvore(no *raiz)
{
    if (raiz == NULL)
    {
        return;
    }
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        apagarArvore(raiz->filho[i]);
    }
    free(raiz);
}

void adicionarPalavra(char *palavra, no *raiz)
{
    no *aux = raiz;
    for (int i = 0, len = strlen(palavra); i < len; i++)
    {
        if (aux->filho[CHAR_TO_INDEX(palavra[i])] == NULL)
        {
            aux->filho[CHAR_TO_INDEX(palavra[i])] = criarNo();
        }
        aux = aux->filho[CHAR_TO_INDEX(palavra[i])];
    }
    aux->tipo = 'P';
}

no *ultimoNoPalavra(char *palavra, no *raiz)
{
    if (raiz == NULL)
    {
        return NULL;
    }

    no *aux = raiz;
    for (int i = 0, len = strlen(palavra); i < len; i++)
    {
        if (aux->filho[CHAR_TO_INDEX(palavra[i])] == NULL)
        {
            return NULL;
        }
        aux = aux->filho[CHAR_TO_INDEX(palavra[i])];
    }

    return aux;
}

int buscaPalavra(char *palavra, no *raiz)
{
    if (raiz == NULL)
    {
        return 0;
    }

    no *ultimoNo = ultimoNoPalavra(palavra, raiz);
    return ultimoNo != NULL && ultimoNo->tipo == 'P';
}

int numeroDeNos(no *r)
{
    if (r == NULL)
    {
        return 0;
    }

    int n = 1;
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        n += numeroDeNos(r->filho[i]);
    }

    return n;
}

int numeroDePalavras(no *r)
{
    int n = 0;
    if (r->tipo == 'P')
    {
        n += 1;
    }

    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (r->filho[i] != NULL)
        {
            n += numeroDePalavras(r->filho[i]);
        }
    }

    return n;
}

int altura(no *r)
{
    if (r == NULL)
    {
        return 0;
    }

    int alturaMaiorSubArvore = 0, alturaSubArvore;
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        alturaSubArvore = r->filho[i] != NULL ? altura(r->filho[i]) + 1 : 0;
        if (alturaSubArvore > alturaMaiorSubArvore)
        {
            alturaMaiorSubArvore = alturaSubArvore;
        }
    }

    return alturaMaiorSubArvore;
}

int possuiFilhos(no *r)
{
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (r->filho[i] != NULL)
        {
            return 1;
        }
    }
    return 0;
}

void deletarNos(no *r, char *palavra, int profundidade, int tamanhoPalavra)
{
    if (profundidade == tamanhoPalavra)
    {
        return;
    }

    deletarNos(r->filho[CHAR_TO_INDEX(palavra[profundidade])], palavra, profundidade + 1, tamanhoPalavra);
    if (!buscaPalavra(palavra, r->filho[CHAR_TO_INDEX(palavra[profundidade])]) &&
        possuiFilhos(r->filho[CHAR_TO_INDEX(palavra[profundidade])]))
    {
        free(r->filho[CHAR_TO_INDEX(palavra[profundidade])]);
        r->filho[CHAR_TO_INDEX(palavra[profundidade])] = NULL;
    }
}

int removerRecursivo(no *raiz, char *palavra, int profundidade)
{
    if (profundidade == strlen(palavra))
    {
        if (raiz->tipo == 'P')
        {
            raiz->tipo = 'I';
            return !possuiFilhos(raiz);
        }
        return 0;
    }

    if (!raiz->filho[CHAR_TO_INDEX(palavra[profundidade])])
    {
        return 0;
    }

    int ret = removerRecursivo(raiz->filho[CHAR_TO_INDEX(palavra[profundidade])], palavra, profundidade + 1);
    if (ret)
    {
        free(raiz->filho[CHAR_TO_INDEX(palavra[profundidade])]);
        raiz->filho[CHAR_TO_INDEX(palavra[profundidade])] = NULL;
        return !possuiFilhos(raiz);
    }

    return 0;
}

void removerPalavra(char *palavra, no *raiz)
{
    removerRecursivo(raiz, palavra, 0);
}
