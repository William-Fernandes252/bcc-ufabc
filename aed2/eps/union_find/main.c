#include "uf.h"
#include <stdio.h>

int main()
{
    grafo *g = criarGrafo(100, 200);
    for (int i = 0; i < g->E; i++)
    {
        g->VetorDeArestas[i] = (aresta){i, 0, i};
    }
    MaiorComponenteConexa(g);

    return 0;
}
