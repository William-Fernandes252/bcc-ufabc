int Parent(int i)
{
    return i / 2;
}

void MinHeapify(int A[], int m, int i)
{
    // IMPLEMENTAR
    // DICA: Igual ao MaxHeapify, mas com os sinais invertidos
    int indiceFilhoEsquerdo = 2 * i;
    int indiceFilhoDireito = 2 * i + 1;

    int menor;
    if (indiceFilhoEsquerdo <= m && A[indiceFilhoEsquerdo] < A[i])
    {
        menor = indiceFilhoEsquerdo;
    }
    else
    {
        menor = i;
    }
    if (indiceFilhoDireito <= m && A[indiceFilhoDireito] < A[menor])
    {
        menor = indiceFilhoDireito;
    }

    if (menor != i)
    {
        int aux = A[i];
        A[i] = A[menor];
        A[menor] = aux;
        MinHeapify(A, m, menor);
    }
}

void BuildMinHeap(int A[], int n)
{
    // IMPLEMENTAR
    // DICA: Igual ao BuildMaxHeap, mas chama o MinHeapify
    for (int i = Parent(n); i >= 1; i--)
    {
        MinHeapify(A, n, i);
    }
}

void PartialHeapSortInverse(int A[], int n, int k)
{
    // IMPLEMENTAR
    // IMPORTANTE: Considere que o A[0] contem o tamanho da lista, e os elementos estao nas posicoes de 1 ate n
    // (inclusive) DICA: Construa o MinHeap e insira os menores elementos no fim da lista (muito similar ao HeapSort,
    // mas com os menores elementos)
    //       Lembre-se de parar com k elementos!
    //       A LISTA FICARA INVERTIDA, ou seja, o menor elemento eh o ultimo, depois o penultimo... e assim por
    //       diante...
    BuildMinHeap(A, n);
    int tamanhoAtual = A[0];
    for (int i = A[0]; i > n - k; i--)
    {
        int aux = A[1];
        A[1] = A[i];
        A[i] = aux;
        A[0]--;
        MinHeapify(A, A[0], 1);
    }
    A[0] = tamanhoAtual;
}

void PartialHeapSort(int A[], int n, int k)
{
    // IMPLEMENTAR
    // IMPORTANTE: Diferente das funcoes anteriores, os elementos comecam na posicao 0, e a saida nao sera invertida
    // DICA: 1) Crie um novo array com tamanho n+1
    //       2) Copie todos os elementos deslocado em um para o novo array
    //       3) Chame o PartialHeapSortInverse
    //       4) Copie novamente os elementso para o array original, invertendo a ordem e iniciando na posicao 0
    int aux[n + 1];
    for (int i = 0; i < n; i++)
    {
        aux[i + 1] = A[i];
    }
    aux[0] = n;
    PartialHeapSortInverse(aux, n, k);
    for (int i = 0, j = n; i < n; i++, j--)
    {
        A[i] = aux[j];
    }
}
