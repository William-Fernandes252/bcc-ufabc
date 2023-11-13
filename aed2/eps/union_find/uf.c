#include "uf.h"
#include <stdio.h>

grafo *criarGrafo(int V, int E)
{
    grafo *g = (grafo *)malloc(sizeof(grafo));
    g->V = V;
    g->E = E;
    g->VetorDeArestas = (aresta *)malloc(g->E * sizeof(aresta));
    return g;
}

void destruirGrafo(grafo *g)
{
    free(g->VetorDeArestas);
    free(g);
}

subset *Make_Subset(int tamanho)
{
    subset *subconjuntos = (subset *)malloc(tamanho * sizeof(subset));
    for (int i = 0; i < tamanho; i++)
    {
        Make_Set(subconjuntos, i);
    }
    return subconjuntos;
}

void Destroy_Subset(subset *s)
{
    free(s);
}

void Make_Set(subset subconjuntos[], int i)
{
    subconjuntos[i].pai = i;
    subconjuntos[i].rank = 0;
}

// Funcao que procura o representante (pai) do elemento i com compressao de caminho.
int Find_Set(subset subconjuntos[], int i)
{
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // DICA: Pseudo-codigo disponivel no Slide. Nao esquecer da compressao de caminhos.
    if (i != subconjuntos[i].pai)
    {
        subconjuntos[i].pai = Find_Set(subconjuntos, subconjuntos[i].pai);
    }
    return subconjuntos[i].pai;
}

// Funcao que junta os conjuntos de x e y com uniao ponderada.
void Union(subset subconjuntos[], int x, int y)
{
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // DICA: Pseudo-codigo disponivel no Slide. Nao esquecer da uniao ponderada.
    x = Find_Set(subconjuntos, x);
    y = Find_Set(subconjuntos, y);
    if (subconjuntos[x].rank > subconjuntos[y].rank)
    {
        subconjuntos[y].pai = x;
    }
    else
    {
        subconjuntos[x].pai = y;
        if (subconjuntos[x].rank == subconjuntos[y].rank)
        {
            subconjuntos[y].rank += 1;
        }
    }
}

// Funcao utilizada para verificar se o grafo tem ou nao ciclo
bool TemCiclo(grafo *g)
{
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    bool tem_ciclo = false;
    subset *s = Make_Subset(g->V);

    // DICA: Faca um laco de 0 ate g->E unindo os vertices.
    //       Caso os verticies ja pertencerem ao memso componente conexo (usar Find_Set),
    //       significa que o grafo tem um ciclo.
    for (int i = 0; i < g->E; i++)
    {
        if (Find_Set(s, g->VetorDeArestas[i].origem) == Find_Set(s, g->VetorDeArestas[i].destino))
        {
            tem_ciclo = true;
            break;
        }
        Union(s, g->VetorDeArestas[i].origem, g->VetorDeArestas[i].destino);
    }

    Destroy_Subset(s);

    return tem_ciclo;
}

subset *GetComponentesEmConjuntos(grafo *g)
{
    subset *s = Make_Subset(g->V);
    for (int i = 0; i < g->E; i++)
    {
        int rx = Find_Set(s, g->VetorDeArestas[i].origem);
        int ry = Find_Set(s, g->VetorDeArestas[i].destino);
        if (rx != ry)
            Union(s, rx, ry);
    }
    return s;
}

int QuantidadeComponentesConexas(grafo *g)
{
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    subset *s = GetComponentesEmConjuntos(g);
    int nc = 0;
    // DICA: Quando o elemento i for o mesmo que o pai[i] (se representante), significa que representa um componente
    // conexo.
    //       Basta contar a quantidade de vertices nesta situacao...
    for (int i = 0; i < g->V; i++)
    {
        if (i == s[i].pai)
        {
            nc += 1;
        }
    }

    Destroy_Subset(s);

    return nc;
}

int MaiorComponenteConexa(grafo *g)
{
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // DICA: Inicio similar a funcao anterior, mas eh preciso contar quantos vertices tem cada
    //       componente conexo para descobrir qual eh de maior quantidade.
    //       Tente criar um vetor auxiliar (tamanho g->V), percorrer todos os vertices e
    //       incrementar o no representante (pai) para cada vertice. Assim, basta buscar a maior contagem.
    subset *s = GetComponentesEmConjuntos(g);

    int *contagemVerticesPorComponente = (int *)calloc(g->V, sizeof(int));
    for (int i = 0; i < g->V; i++)
    {
        contagemVerticesPorComponente[Find_Set(s, i)] += 1;
    }

    int maximo = 0;
    for (int i = 0; i < g->V; i++)
    {
        if (contagemVerticesPorComponente[i] > maximo)
        {
            maximo = contagemVerticesPorComponente[i];
        }
    }

    Destroy_Subset(s);
    free(contagemVerticesPorComponente);

    return maximo;
}

aresta *ordenarArestas(aresta *vetorDeArestas, int n)
{
    aresta *vetorOrdenado = (aresta *)malloc(n * sizeof(aresta));
    for (int i = 0; i < n; i++)
    {
        vetorOrdenado[i] = (aresta){
            .origem = vetorDeArestas[i].origem, .destino = vetorDeArestas[i].destino, .peso = vetorDeArestas[i].peso};
    }

    int trocas;
    do
    {
        trocas = 0;
        for (int i = 0; i < n - 1; i++)
        {
            if (vetorOrdenado[i].peso > vetorOrdenado[i + 1].peso)
            {
                aresta aux = vetorOrdenado[i];
                vetorOrdenado[i] = vetorOrdenado[i + 1];
                vetorOrdenado[i + 1] = aux;
                trocas++;
            }
        }
    } while (trocas);

    return vetorOrdenado;
}

int SomaPesoArestasDaArvoreGeradoraMinima(grafo *g)
{
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // DICA: Use o algoritmo de Kruskal (disponivel no slide):
    //       Ordene as arestas por peso e crie um contador que soma todos os pesos
    //       utilizados na formacao da Arvore Geradora Minima.
    subset *s = Make_Subset(g->V);
    aresta *vetorDeArestasOrdenado = ordenarArestas(g->VetorDeArestas, g->E);

    int soma = 0;
    for (int i = 0; i < g->E; i++)
    {
        printf("%d %d %d\n", vetorDeArestasOrdenado[i].origem, vetorDeArestasOrdenado[i].destino,
               vetorDeArestasOrdenado[i].peso);
        if (Find_Set(s, vetorDeArestasOrdenado[i].origem) != Find_Set(s, vetorDeArestasOrdenado[i].destino))
        {
            Union(s, vetorDeArestasOrdenado[i].origem, vetorDeArestasOrdenado[i].destino);
            soma += vetorDeArestasOrdenado[i].peso;
        }
    }

    Destroy_Subset(s);
    free(vetorDeArestasOrdenado);

    return soma;
}