#include "heap.h"

// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// --- CONSIDERE O INDICE ZERO (A[0]) A QUANTIDADE DE ELEMENTOS
// --- CONSIDERE QUE O VETOR VAI DE 1 ATE N (E NAO DE 0 ATE N-1)
// --- CONSIDERE QUE O VETOOR JA TEM UM TAMANHO SUFICIENTEMENTE GRANDE PARA A INSERCAO

int Parent(int i)
{
    return i / 2;
}

void MaxHeapify(tipoChave A[], int i)
{
    // IMPLEMENTAR
    // OBS.: O indice i vai de 1 ate A[0]
    int indice_filho_esquerdo = 2 * i;
    int indice_filho_direito = 2 * i + 1;

    tipoChave maior;
    if (indice_filho_esquerdo <= A[0] && A[indice_filho_esquerdo] > A[i])
    {
        maior = indice_filho_esquerdo;
    }
    else
    {
        maior = i;
    }
    if (indice_filho_direito <= A[0] && A[indice_filho_direito] > A[maior])
    {
        maior = indice_filho_direito;
    }

    if (maior != i)
    {
        tipoChave aux = A[i];
        A[i] = A[maior];
        A[maior] = aux;
        MaxHeapify(A, maior);
    }
}

void BuildMaxHeap(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Chamar a funcao MaxHeapify
    for (int i = Parent(A[0]); i >= 1; i--)
    {
        MaxHeapify(A, i);
    }
}

void HeapSort(tipoChave A[])
{
    // IMPLEMENTAR
    // DICA: Como a funcao MaxHeapify nao tem o argumento tamanho (como nos slides),
    //       armazene o tamanho atual (t = A[0]), decremente A[0] antes de chamar
    //       MaxHeapify, entao restaure o valor A[0] = t no final.
    BuildMaxHeap(A);
    int tamanhoAtual = A[0];
    for (int i = A[0]; i >= 2; i--)
    {
        tipoChave aux = A[1];
        A[1] = A[i];
        A[i] = aux;
        A[0] -= 1;
        MaxHeapify(A, 1);
    }
    A[0] = tamanhoAtual;
}

tipoChave HeapMaximum(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Nao esqueca que o primeiro elemento eh o A[1]
    return A[1];
}

tipoChave HeapExtractMax(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Nao precisa tratar o caso do vetor vazio!
    tipoChave max = HeapMaximum(A);
    A[1] = A[A[0]];
    A[0] -= 1;
    MaxHeapify(A, 1);
    return max;
}

void HeapIncreaseKey(tipoChave A[], int i, tipoChave key)
{
    // IMPLEMENTAR
    // OBS.: Nao precisa tratar o caso da chave alterada for menor que a chave atual!
    A[i] = key;
    while (i > 1 && A[Parent(i)] < A[i])
    {
        tipoChave aux = A[i];
        A[i] = A[Parent(i)];
        A[Parent(i)] = aux;
        i = Parent(i);
    }
}

void MaxHeapInsert(tipoChave A[], tipoChave key)
{
    // IMPLEMENTAR
    // OBS.: Nao esquecer de aumentar a quantidade de elementos, ou seja, A[0]++
    A[0] += 1;
    A[A[0]] = (unsigned long int)-1;
    HeapIncreaseKey(A, A[0], key);
}
