// ATENCAO: NAO ALTERAR ESTE ARQUIVO !!!
// ATENCAO: NAO ALTERAR ESTE ARQUIVO !!!
// ATENCAO: NAO ALTERAR ESTE ARQUIVO !!!

#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 32 // Tamanho maximo da chave e do valor (que eh do tipo string)

// Tres tipos de hash, o primeiro jah esta implementado
typedef enum
{
    semColisao,
    encadeamento,
    aberto
} modoHash;

// Estrutura utilizada no hash semColisao e aberto
typedef struct hashAberto
{
    char chave[STR_SIZE];
    char valor[STR_SIZE];
    bool excluido; // Utilizado para encontrar uma chave em hash com encadeamento aberto
} hashAberto;

// Estrutura da lista ligada
typedef struct listaEncadeada
{
    char chave[STR_SIZE];
    char valor[STR_SIZE];
    struct listaEncadeada *proximo;
} listaEncadeada;

// Estrutura utilizada no hash com encadeamento externo
typedef struct hashEncadeada
{
    listaEncadeada *primeiro;
} hashEncadeada;

// Estrutura principal do hash
typedef struct tipoHash
{
    union { // A estrutura union permite 'selecionar' a estrutura da tabela que sera utilizada
        hashEncadeada *encadeada;
        hashAberto *aberto;
    } tabela;
    int tamanho;   // Tamanho da tabela hash
    modoHash modo; // Modo de operacao da tabela hash: semColisao, encadeamento, aberto
} tipoHash;

// Funcao que transforma a chave em um indice da tabela
int hash(char chave[STR_SIZE], int tamanho, int tentativa);

tipoHash criar(modoHash modo, int tamanho); // Inicializa uma tabela hash
void destruir(tipoHash hash);               // Libera da memoria toda a tabela

void inserir(tipoHash hash, char chave[STR_SIZE], char valor[STR_SIZE]);
char *buscar(tipoHash hash, char chave[STR_SIZE]);
void apagar(tipoHash hash, char chave[STR_SIZE]);
int quantidade(tipoHash hash); // Retorna a quantidade de elementos

#endif
