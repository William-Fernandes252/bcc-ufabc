#include "hash.h"

// Funcao hash. Retorna o indice de uma chave na tabela. Nao alterar!
int hash(char chave[STR_SIZE], int tamanho, int tentativa)
{
    int h = chave[0];
    for (int i = 1; chave[i] != '\0'; i++)
        h = (h * 251 * chave[i]) % tamanho;
    return (h + tentativa) % tamanho;
}

tipoHash criar(modoHash m, int t)
{
    tipoHash h;
    h.tamanho = t;
    switch (h.modo = m)
    {
    case semColisao:
        h.tabela.aberto = (hashAberto *)malloc(sizeof(hashAberto) * t);
        for (int i = 0; i < t; i++)
            h.tabela.aberto[i].chave[0] = h.tabela.aberto[i].valor[0] = '\0';
        break;

    case encadeamento:
        h.tabela.encadeada = (hashEncadeada *)malloc(sizeof(hashEncadeada) * t);
        for (int i = 0; i < t; i++)
            h.tabela.encadeada[i].primeiro = NULL;
        break;

    case aberto:
        h.tabela.aberto = (hashAberto *)malloc(sizeof(hashAberto) * t);
        for (int i = 0; i < t; i++)
        {
            h.tabela.aberto[i].excluido = false;
            h.tabela.aberto[i].chave[0] = h.tabela.aberto[i].valor[0] = '\0';
        }
        break;
    }
    return h;
}

void freeListaEncadeada(listaEncadeada *l)
{
    if (l == NULL)
    {
        return;
    }
    freeListaEncadeada(l->proximo);
    free(l);
}

void destruir(tipoHash h)
{
    switch (h.modo)
    {
    case semColisao:
    case aberto:
        free(h.tabela.aberto);
        h.tabela.aberto = NULL;
        break;

    case encadeamento:
        // IMPLEMENTAR!!!
        // Dica: Nao esquecer de desalocar toda a lista ligada!
        for (int i = 0; i < h.tamanho; i++)
        {
            freeListaEncadeada(h.tabela.encadeada[i].primeiro);
        }
        free(h.tabela.encadeada);
        h.tabela.encadeada = NULL;
        break;
    }
}

void inserir(tipoHash h, char c[STR_SIZE], char v[STR_SIZE])
{
    int idx = hash(c, h.tamanho, 0);
    switch (h.modo)
    {
    case semColisao:
        strcpy(h.tabela.aberto[idx].chave, c);
        strcpy(h.tabela.aberto[idx].valor, v);
        break;

    case encadeamento:
        // IMPLEMENTAR!!!
        // Eh preciso alocar a estrutura listaEncadeada para cada elemento inserido.
        // Sugiro incluir no final da lista, mas pode ser inserido em qualquer ponto.
        if (h.tabela.encadeada[idx].primeiro == NULL)
        {
            h.tabela.encadeada[idx].primeiro = (listaEncadeada *)malloc(sizeof(listaEncadeada));
            h.tabela.encadeada[idx].primeiro->proximo = NULL;
            strcpy(h.tabela.encadeada[idx].primeiro->chave, c);
            strcpy(h.tabela.encadeada[idx].primeiro->valor, v);
        }
        for (listaEncadeada *p = h.tabela.encadeada[idx].primeiro; p != NULL; p = p->proximo)
        {
            if (strcmp(p->chave, c) == 0)
            {
                break;
            }
            if (p->proximo == NULL)
            {
                p->proximo = (listaEncadeada *)malloc(sizeof(listaEncadeada));
                p->proximo->proximo = NULL;
                strcpy(p->proximo->chave, c);
                strcpy(p->proximo->valor, v);
            }
        }
        break;

    case aberto:
        // IMPLEMENTAR!!!
        // DICA: Eh utilizado encadeamento aberto linear. Utilize as tentativas conforme mostrado abaixo.
        for (int tentativa = 0; tentativa < h.tamanho; tentativa++)
        {
            idx = hash(c, h.tamanho, tentativa);
            // DICA: Use uma verificacao como h.tabela.aberto[idx].chave[0] == '\0' para saber se a celula esta vazia
            // DICA: Nao esquecer de atualizar o atributo excluido
            if (h.tabela.aberto[idx].chave[0] == '\0' || h.tabela.aberto[idx].excluido)
            {
                strcpy(h.tabela.aberto[idx].chave, c);
                strcpy(h.tabela.aberto[idx].valor, v);
                h.tabela.aberto[idx].excluido = false;
                break;
            }
        }
        break;
    }
}

char *buscar(tipoHash h, char c[STR_SIZE])
{
    int idx = hash(c, h.tamanho, 0);
    switch (h.modo)
    {
    case semColisao:
        return strcmp(h.tabela.aberto[idx].chave, c) == 0 ? h.tabela.aberto[idx].valor : NULL;

    case encadeamento:
        // IMPLEMENTAR!!!
        // Retornar nulo se a chave nao for encontrada!
        for (listaEncadeada *p = h.tabela.encadeada[idx].primeiro; p != NULL; p = p->proximo)
        {
            if (strcmp(p->chave, c) == 0)
            {
                return p->valor;
            }
        }
        return NULL;

    case aberto:
        // IMPLEMENTAR!!!
        // Retornar nulo se a chave nao for encontrada!
        for (int tentativa = 0; tentativa < h.tamanho; tentativa++)
        {
            idx = hash(c, h.tamanho, tentativa);
            if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
            {
                return h.tabela.aberto[idx].valor;
            }
        }
        return NULL;
    }
    return NULL;
}

void apagar(tipoHash h, char c[STR_SIZE])
{
    int idx = hash(c, h.tamanho, 0);
    switch (h.modo)
    {
    case semColisao:
        if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
        {
            h.tabela.aberto[idx].chave[0] = h.tabela.aberto[idx].valor[0] = '\0';
        }
        break;

    case encadeamento:
        // IMPLEMENTAR!!!
        for (listaEncadeada *atual = h.tabela.encadeada[idx].primeiro, *anterior = NULL; atual != NULL;
             anterior = atual, atual = atual->proximo)
        {
            if (strcmp(atual->chave, c) == 0)
            {
                if (anterior == NULL)
                {
                    h.tabela.encadeada[idx].primeiro = atual->proximo;
                }
                else
                {
                    anterior->proximo = atual->proximo;
                }
                free(atual);
            }
        }
        break;

    case aberto:
        // IMPLEMENTAR!!!
        // DICA: Nao esquecer de atribuir true para excluido. Caso contrario, uma chave podera ser localizada.
        for (int tentativa = 0; tentativa < h.tamanho; tentativa++)
        {
            idx = hash(c, h.tamanho, tentativa);
            if (strcmp(h.tabela.aberto[idx].chave, c) == 0)
            {
                h.tabela.aberto[idx].chave[0] = h.tabela.aberto[idx].valor[0] = '\0';
                h.tabela.aberto[idx].excluido = true;
            }
        }
        break;
    }
}

int quantidade(tipoHash h)
{
    int qtd = 0;
    switch (h.modo)
    {
    case semColisao:
    case aberto: // Igual ao semColisao, portanto, jah implementado!!!
        for (int i = 0; i < h.tamanho; i++)
        {
            if (h.tabela.aberto[i].chave[0] != '\0')
            {
                qtd++;
            }
        }
        break;

    case encadeamento:
        for (int i = 0; i < h.tamanho; i++)
        {
            for (listaEncadeada *p = h.tabela.encadeada[i].primeiro; p != NULL; p = p->proximo)
            {
                qtd++;
            }
        }
        break;
    }
    return qtd;
}
