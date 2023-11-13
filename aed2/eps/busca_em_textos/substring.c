#include "substring.h" // typedef unsigned char *bytes;

// Use 0 se o vetor a e b (palavra e texto) inicia em 0 (a[0..m-1] e b[0..n-1])
//  ou 1 se o vetor a e b (palavra e texto) inicia em 1 (a[1..m]   e b[1..n])
int inicia_em = 1;

// Funcao que verifica se existe a ocorrencia da palavra 'a' no texto 'b', alinhado pelo último caractere da palavra.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// pos_ult_carac    Posição do texto b[pos_ult_carac+inicia_em-1] alinhado com a última letra da palavra
// (a[m+inicia_em-1]) RETORNO  Verdadeiro se exisitr a ocorrêncai da palavra 'a' no texto 'b' na posição
// 'pos_ult_carac'. Falso caso contrário.
bool verifica_ocorrencia(char *a, int m, char *b, int n, int pos_ult_carac)
{
    if (pos_ult_carac <= n)
    {
        int i = m, j = pos_ult_carac;
        while (i >= 1 && a[i] == b[j])
        {
            --i;
            --j;
        }
        if (i < 1)
        {
            return true;
        }
    }
    return false;
}

// Funcao que calcula a quantidade de ocorrencias de 'a' em 'b'.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// RETORNO  Quantidade de ocorrências de a em b.
int ocorrencias(char *a, int m, char *b, int n)
{
    int ocorrencias = 0;
    int k = m;
    while (k <= n)
    {
        if (verifica_ocorrencia(a, m, b, n, k))
        {
            ocorrencias += 1;
        }
        k += 1;
    }
    return ocorrencias;
}

// Funcao que retorna a posicao do primeiro caractere de 'a' em 'b' durante a primeira ocorrencia de 'a'.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// RETORNO  A posicao do primeiro caractere da palavra 'a' em 'b' iniciado em 'inicia_em'. Caso nao houver ocorrencias,
// retornar -1.
int primeira_ocorrencia(char *a, int m, char *b, int n)
{
    int index_primeira_ocorrencia = 1;
    int k = m;
    while (k <= n)
    {
        if (verifica_ocorrencia(a, m, b, n, k))
        {
            return index_primeira_ocorrencia;
        }
        k += 1;
        index_primeira_ocorrencia += 1;
    }
    return -1;
}

// Funcao que retorna a posicao do primeiro caractere de 'a' em 'b' durante a ultima ocorrecnai de 'a'.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// RETORNO  A posicao do primeiro caractere da palavra 'a' em 'b' iniciado em 'inicia_em'. Caso nao houver ocorrencias,
// retornar -1.
int ultima_ocorrencia(char *a, int m, char *b, int n)
{
    int index_ultima_ocorrencia = -1;
    int k = m;
    while (k <= n)
    {
        if (verifica_ocorrencia(a, m, b, n, k))
        {
            index_ultima_ocorrencia = k - m + 1;
        }
        k += 1;
    }
    return index_ultima_ocorrencia;
}

// Funcao que constroi o vetor 'ultimo', ja alocado com o tamanho 'tamanho_alfabeto', contendo a posicao da ultima
// ocorrencia do respectivo caractere na palavra 'a'. a                Vetor com a palavra que inicia em 'inicia_em'
// (a[inicia_em..m+inicia_em-1]) m                Tamanho de 'a' (palavra) ultimo           Vetor tipo inteiro dos
// indice de cada caractere contendo a ultimoa ocorrencia em 'a'.
//                    Obs.1: O vetor ja esta alocado com o tamanho 'tamanho_alfabeto'.
//                    Obs.2: Eh preciso zerar todo o vetor. Caracteres inexistentes devem conter o valor 0.
//                    Obs.3: O primeiro caractere tem a posicao 1, iniciado da esquerda para a direita.
// tamanho_alfabeto Tamanho do alfabeto e, consequentemente, o tamanho do vetor 'ultimo'.
void caractere_errado(char *a, int m, int *ultimo, int tamanho_alfabeto)
{
    // IMPLEMENTAR !!!
    // Zerar 'ultimo' (jah alocado)
    // Preencher 'ultimo' com a ocorrencia do ultimo caractere em 'a'
    for (int i = 0; i < tamanho_alfabeto; i++)
    {
        ultimo[i] = 0;
    }
    for (int i = 1; i <= m; i++)
    {
        ultimo[(int)a[i]] = i;
    }
}

// Funcao que constroi o vetor 'jump', ja alocado com o tamanho 'm' da palavra 'a', contendo o ultimo sufixo da palavra
// 'a'. a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1]) m Tamanho de 'a'
// (palavra) jump           Vetor tipo inteiro que contem a ocorrencia do sufixo na propria palavra 'a'.
void sufixo_correto(char *a, int m, int *jump)
{
    // IMPLEMENTAR !!!
    // Preencher 'jump' (jah alocado) com as ocorrencias de sufixos
    int h = m;
    int k = m - 1;
    while (h >= 1 && k >= 1)
    {
        int i = m, j = k;
        while (i >= h && j >= 1)
        {
            if (a[i] == a[j])
            {
                --i;
                --j;
            }
            else
            {
                i = m;
                k -= 1;
                j = k;
            }
        }
        jump[h--] = k;
    }
    while (h >= 0)
    {
        jump[h--] = k;
    }
}

// Funcao que retorna o salto calculado atraves da tecnica caractere errado.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// ultimo           Vetor tipo inteiro dos indice de cada caractere contendo a ultimoa ocorrencia em 'a'.
// tamanho_alfabeto Tamanho do alfabeto e, consequentemente, o tamanho do vetor 'ultimo'.
// posicao_atual    Posicao atual do texto 'b' que inicia em 'inicia_em'.
// RETORNO  Valor do salto.
int salto_caractere_errado(char *a, int m, char *b, int n, int *ultimo, int tamanho_alfabeto, int posicao_atual)
{
    // IMPLEMENTAR !!!
    int salto = 1;
    int k = posicao_atual;
    if (k != n)
    {
        salto += m - ultimo[(int)b[k + 1]];
    }

    return salto;
}

// Funcao que retorna o salto calculado atraves da tecnica sufixo correto.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// jump             Vetor tipo inteiro que contem a ocorrencia do sufixo na propria palavra 'a'.
// posicao_atual    Posicao atual do texto 'b' que inicia em 'inicia_em'.
// RETORNO  Valor do salto.
int salto_sufixo_correto(char *a, int m, char *b, int n, int *jump, int posicao_atual)
{
    // IMPLEMENTAR !!!
    int k = posicao_atual;
    int i = m, j = k;
    while (i >= 1 && a[i] == b[j])
    {
        --i;
        --j;
    }
    if (i == m)
    {
        return 1;
    }
    return m - jump[i + 1];
}

// Funcao que retorna o salto calculado atraves das tecnicas caractere errado e sufixo correto.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// ultimo           Vetor tipo inteiro dos indice de cada caractere contendo a ultimoa ocorrencia em 'a'.
// tamanho_alfabeto Tamanho do alfabeto e, consequentemente, o tamanho do vetor 'ultimo'.
// jump             Vetor tipo inteiro que contem a ocorrencia do sufixo na propria palavra 'a'.
// posicao_atual    Posicao atual do texto 'b' que inicia em 'inicia_em'.
// RETORNO  Valor do melhor salto entre as duas tecnicas caractere errado e sufixo correto.
int melhor_salto_na_posicao(char *a, int m, char *b, int n, int *ultimo, int tamanho_alfabeto, int *jump,
                            int posicao_atual)
{
    // IMPLEMENTAR !!!
    // Eh preciso utilizar as funcoes salto_caractere_errado e salto_sufixo_correto
    // Retornar o maior salto
    int salto1 = salto_caractere_errado(a, m, b, n, ultimo, tamanho_alfabeto, posicao_atual);
    int salto2 = salto_sufixo_correto(a, m, b, n, jump, posicao_atual);
    return salto1 > salto2 ? salto1 : salto2;
}

// Funcao que conta ocorrencias da palavra 'a' no texto 'b' utilizando o algoritmo de Boyer-Moore.
// a                Vetor com a palavra que inicia em 'inicia_em' (a[inicia_em..m+inicia_em-1])
// m                Tamanho de 'a' (palavra)
// b                Vetor com o texto que inicia em 'inicia_em' (b[inicia_em..m+inicia_em-1])
// n                Tamanho de 'b' (texto)
// ultimo           Vetor tipo inteiro dos indice de cada caractere contendo a ultima ocorrencia em 'a' ja preenchido!
// tamanho_alfabeto Tamanho do alfabeto e, consequentemente, o tamanho do vetor 'ultimo'.
// jump             Vetor tipo inteiro que contem a ocorrencia do sufixo na propria palavra 'a' ja prenchido!
// RETORNO  Quantidade de ocorrências de a em b.
int boyer_moore(char *a, int m, char *b, int n, int *ultimo, int tamanho_alfabeto, int *jump)
{
    // IMPLEMENTAR !!!
    // Eh preciso utilizar a funcao melhor_salto_na_posicao
    caractere_errado(a, m, ultimo, tamanho_alfabeto);
    sufixo_correto(a, m, jump);

    int ocorrencias = 0;
    int k = m;
    while (k <= n)
    {
        int i = m, j = k;
        while (i >= 1 && a[i] == b[j])
        {
            --i;
            --j;
        }
        if (i < 1)
        {
            ocorrencias += 1;
        }
        if (k >= n)
        {
            k += 1;
        }
        else
        {
            k += melhor_salto_na_posicao(a, m, b, n, ultimo, tamanho_alfabeto, jump, k);
        }
    }

    return ocorrencias;
}
