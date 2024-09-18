#include <stdlib.h>
#include <string.h>

#include "huffman.h"

void criarAlfabeto(char *texto, int tamanho_texto, char *alfabeto[], int *frequencia[], int *tamanho)
{
    // IMPLEMENTAR
    //   - texto: texto original com tamanho_texto caracteres
    //   - tamanho_texto: tamanho do texto (quantidade de caracteres)
    //   - alfabeto: parametro de saida. Vetor tipo char com os carecteres existentes. Exemplo: para o texto "banana", o
    //   vetor seria "{'a', 'b', 'n'}.
    //               Importante: Deve estar ordenado, de acordo com a tabela ASCII.
    //               Importante: Deve ser alocado (malloc) de acordo com a variedade de caracteres encontradas no texto.
    //               Por exemplo, para o texto "ABCABCAB", o tamanho seria de 3. Importante: Considerar quebra de linha,
    //               pontuacao e espaco como caractere valido. Distinguir caractere maiuscula de minuscula.
    //   - frequenca: parametro de saida. Vetor de inteiros, complementar ao vetor alfabeto, contendo a quantidade de
    //   ocorrencias.
    //   - tamanho: tamanho do vetor alfabeto e frequencia, referente a variedade de caracteres.
    // EXEMPLO: texto:    "Bom dia, tudo bem?"
    //          alfabeto:  {' ', ',', '?', 'B', 'a', 'b', 'd', 'e', 'i', 'm', 'o', 't', 'u' }
    //          frequencia:{ 3 ,  1 ,  1 ,  1 ,  1 ,  1 ,  2 ,  1 ,  1 ,  2 ,  2 ,  1 ,  1  }
    //          tamanho:   13
    // DICA:
    //  - Crie uma variavel caracteres tipo vetor de inteiro com tamanho 255 (tipos maximos de caractere), com todos
    //  valores em zero
    //  - Faca um laco percorrendo todo o texto, incrementando este vetor em cada ocorrencia de caractere
    //  - Aproveite o mesmo laco para calcular a variavel de saida tamanho (tipos distintos de caracteres presente no
    //  texto)
    //  - Alocar as variaveis de saida alfabeto e frequencia
    //  - Percorra todos os caracteres em um novo laco e insira no alfabeto e frequencia o caractere e a quantidade de
    //  ocorrencias respectivamente

    int caracteres[255] = {0};

    // Contagem de caracteres e inicialização do vetor de contagem
    for (int i = 0; i < tamanho_texto; i++)
    {
        caracteres[(int)texto[i]]++;
    }

    // Contagem do número de caracteres distintos
    *tamanho = 0;
    for (int i = 0; i < 255; i++)
    {
        if (caracteres[i] > 0)
        {
            (*tamanho)++;
        }
    }

    // Alocar memória para alfabeto e frequencia
    *alfabeto = (char *)malloc((*tamanho) * sizeof(char));
    *frequencia = (int *)malloc((*tamanho) * sizeof(int));

    // Preencher alfabeto e frequencia
    int index = 0;
    for (int i = 0; i < 255; i++)
    {
        if (caracteres[i] > 0)
        {
            (*alfabeto)[index] = (char)i;
            (*frequencia)[index] = caracteres[i];
            index++;
        }
    }

    // Ordenar alfabeto (usando o algoritmo de ordenação de bolha para simplificar)
    for (int i = 0; i < (*tamanho) - 1; i++)
    {
        for (int j = 0; j < (*tamanho) - i - 1; j++)
        {
            if ((*alfabeto)[j] > (*alfabeto)[j + 1])
            {
                // Trocar caracteres
                char temp_char = (*alfabeto)[j];
                (*alfabeto)[j] = (*alfabeto)[j + 1];
                (*alfabeto)[j + 1] = temp_char;

                // Trocar frequências correspondentes
                int temp_freq = (*frequencia)[j];
                (*frequencia)[j] = (*frequencia)[j + 1];
                (*frequencia)[j + 1] = temp_freq;
            }
        }
    }
}

struct MinHeapNode *buildHuffmanTree(char alfabeto[], int frequencia[], int tamanho)
{
    // Passo 1: Criar e construir MinHeap com capacidade igual ao tamanho passando alfabeto, frequencia e tamanho como
    // argumento Criar um laco, enquanto houver dois elementos na heap
    //     Passo 2: Extrair os dois caracteres/nos com menor frequencia da heap
    //       ATENCAO: o menor elemento deve ser insirido no noh esquerdo, e o segundo menor no noh direito
    //       DICA: Use a funcao extractMin, jah implementado
    //     Passo 3: Criar um novo noh interno com frequencia igual a soma dos nos extraidos da heap.
    //       ATENCAO: utilize '$' como um valor especial utilizado em nos intermediarios
    //       DICA: Utilize a funcao newNode (jah implementado), passe a soma das frquencias dos filhos esquerdo e direto
    //       como valor DICA: Nao esqeuca de atribuir os filhos esquerdo e direito, obtido no passo 2 LEMBRE-SE: insira
    //       este noh novamente na heap, usando a funcao insertMinHeap, jah implementado
    // Passo 4: Extrair o no raiz, que representa a raiz da arvore de huffman! Retorno o noh raiz.
    //   LEMBRE-SE: Chame o destroyMinHeap para liberar a estrutura heap.
    struct MinHeap *heap = createAndBuildMinHeap(alfabeto, frequencia, tamanho);
    struct MinHeapNode *esquerdo = extractMin(heap);
    struct MinHeapNode *direito = extractMin(heap);
    struct MinHeapNode *root = newNode('$', esquerdo->frequencia + direito->frequencia);
    root->esquerda = esquerdo;
    root->direita = direito;
    insertMinHeap(heap, root);
    struct MinHeapNode *huffmanRoot = extractMin(heap);
    destroyMinHeap(heap);
    return huffmanRoot;
}

void destroyHuffmanTree(struct MinHeapNode *root)
{
    // IMPLEMENTAR: Libera da memoria toda a arvore de Huffman
    if (root != NULL)
    {
        destroyHuffmanTree(root->esquerda);
        destroyHuffmanTree(root->direita);
        free(root);
    }
}

void generateCodesArrayHelper(struct MinHeapNode *root, codes_t codes, char *code, int depth)
{
    if (root == NULL)
        return;

    if (isLeaf(root))
    {
        code[depth] = '\0'; // Adiciona o terminador de string
        strcpy(codes[root->conteudo], code);
    }

    // Percorre a árvore para a esquerda (0) e a direita (1)
    code[depth] = '0';
    generateCodesArrayHelper(root->esquerda, codes, code, depth + 1);

    code[depth] = '1';
    generateCodesArrayHelper(root->direita, codes, code, depth + 1);
}

void generateCodesArray(struct MinHeapNode *root, codes_t codes)
{
    // IMPLEMENTAR: Gerar o vetor codes de acordo com a arvore de huffman
    // IMPORTANTE: Atribuir 0 para os filhos esquerdos, e 1 para os filhos direitos
    // DICA: A estrutura codes_t esta descrita no arquivo huffman.h
    char code[MAX_TREE_HT];
    generateCodesArrayHelper(root, codes, code, 0);
}

long sizeOfTextCompressed(char *texto, long tamanho, codes_t codes)
{
    // IMPLEMENTAR: Utilizando o dicionario (codes), calcular o tamnho do texto apos a codificacao
    // IMPORTANTE: Considerar o tamnho em bits
    // DICA: Percorra o texto e obtenha a quantidade de bits de cada caractere (codes[texto[i]][0])
    long tamanhoComprimido = 0;

    for (long i = 0; i < tamanho; i++)
    {
        // Obtem a quantidade de bits de cada caractere e acumula no tamanhoComprimido
        tamanhoComprimido += codes[texto[i]][0];
    }

    return tamanhoComprimido;
}
