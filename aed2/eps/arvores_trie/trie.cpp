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
    // IMPLEMENTAR !!!
    // Dica 1: Use um laco iterativo de 0 ate strlen(palavra)
    // Dica 2: Criar o no com a funcao criarNo (caso nao existir)
    // Dica 3: Utilize a macro CHAR_TO_INDEX (ver trie.h) para converter o caractere para o indice filho
    // Dica 4: Nao esqueca de mudar o tipo para 'P' no ultimo noh que representa o ultimo caractere
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

int buscaPalavra(char *palavra, no *raiz)
{
    // IMPLEMENTAR !!!
    // Dica 1: Funcao similar ao adicionarPalavra
    // Dica 2: Se o ultimo noh que representa o ultimo caractere for do tipo 'I', a palavra nao existe
    // IMPORTANTE:
    //   retorne 0 se a palavra nao exite
    //   retorne 1 se a palavra existir
    if (raiz == NULL)
    {
        return 0;
    }

    no *aux = raiz;
    for (int i = 0, len = strlen(palavra); i < len; i++)
    {
        if (aux->filho[CHAR_TO_INDEX(palavra[i])] == NULL)
        {
            return 0;
        }
        aux = aux->filho[CHAR_TO_INDEX(palavra[i])];
    }
    return aux->tipo == 'P';
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
    if (r == NULL)
    {
        return 0;
    }

    int n = 0;
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        n += numeroDePalavras(r->filho[i]) + (int)(r->tipo == 'P');
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
        alturaSubArvore = altura(r->filho[i]);
        if (alturaSubArvore > alturaMaiorSubArvore)
        {
            alturaMaiorSubArvore = alturaSubArvore;
        }
    }

    return alturaMaiorSubArvore;
}

int contagemFilhos(no *c)
{
    if (c == NULL)
    {
        return -1;
    }

    int contagem = 0;
    for (int i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (c->filho[i] != NULL)
        {
            contagem += 1;
        }
    }

    return contagem;
}

void removerPalavra(char *palavra, no *raiz)
{
    // IMPLEMENTAR !!!
    // Nota: Esta funcao eh a mais elaborada. Recomendo criar funcoes auxiliares e utilizar recursao
    if (raiz == NULL)
    {
        return;
    }

    no *aux = raiz;
    for (int i = 0, len = strlen(palavra); i < len; i++)
    {
        if (buscaPalavra(&palavra[i], aux))
        {
            aux = aux->filho[CHAR_TO_INDEX(palavra[i])];
            if (strlen(&palavra[i]) > 1)
            {
                removerPalavra(&palavra[i], aux);
            }
            else
            {
                if (contagemFilhos(aux) == 0)
                {
                    apagarArvore(aux);
                }
            }
        }
    }
}