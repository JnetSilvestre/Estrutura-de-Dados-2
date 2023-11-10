//Alunos: João Victor da Cruz Silvestre    RA:2144263
//        Paulo Mitsi                      RA:2410362

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 15
#define MAX_ARESTAS 14

// Estrutura para representar os nós
typedef struct No {
    int vertice;
    struct No* proximo;
} No;

// Estrutura para representar o grafo
typedef struct Grafo {
    No* listaAdjacencia[MAX_VERTICES];
} Grafo;

void adicionarAresta(Grafo* grafo, int origem, int destino) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = destino;
    novoNo->proximo = grafo->listaAdjacencia[origem];              // Função para adicionar uma aresta ao grafo
    grafo->listaAdjacencia[origem] = novoNo;
}

void buscaEmLargura(Grafo* grafo, int verticeInicial) {           // Função para a busca em largura

    int visitado[MAX_VERTICES] = {0};

    // Fila para a BFS
    int fila[MAX_VERTICES];
    int frente = -1, tras = -1;

    visitado[verticeInicial] = 1;
    fila[++tras] = verticeInicial;

    printf("Busca em Largura a partir do vertice %d:\n", verticeInicial);

    while (frente != tras) {
        // Desenfileira um vértice e o exibe
        int verticeAtual = fila[++frente];
        printf("%d ", verticeAtual);

        No* temp = grafo->listaAdjacencia[verticeAtual];
        while (temp != NULL) {
            int verticeAdjacente = temp->vertice;

            if (!visitado[verticeAdjacente]) {
                visitado[verticeAdjacente] = 1;
                fila[++tras] = verticeAdjacente;
            }

            temp = temp->proximo;
        }
    }

    printf("\n");
}

void buscaEmProfundidadeUtil(Grafo* grafo, int vertice, int visitado[MAX_VERTICES]) {      // Função para a busca em profundidade (DFS)

    visitado[vertice] = 1;
    printf("%d ", vertice);

    No* temp = grafo->listaAdjacencia[vertice];
    while (temp != NULL) {
        int verticeAdjacente = temp->vertice;

        if (!visitado[verticeAdjacente]) {
            buscaEmProfundidadeUtil(grafo, verticeAdjacente, visitado);
        }

        temp = temp->proximo;
    }
}

void buscaEmProfundidade(Grafo* grafo, int verticeInicial) {           // Função principal para a busca em profundidade
    int visitado[MAX_VERTICES] = {0};

    printf("Busca em Profundidade a partir do vértice %d:\n", verticeInicial);
    buscaEmProfundidadeUtil(grafo, verticeInicial, visitado);

    printf("\n");
}

int main() {
    // Inicializa o grafo
    Grafo grafo;
    for (int i = 0; i < MAX_VERTICES; i++) {
        grafo.listaAdjacencia[i] = NULL;
    }

    // Comçando exercicio 1
    adicionarAresta(&grafo, 0, 1);
    adicionarAresta(&grafo, 0, 2);
    adicionarAresta(&grafo, 1, 3);
    adicionarAresta(&grafo, 1, 4);
    adicionarAresta(&grafo, 1, 5);
    adicionarAresta(&grafo, 3, 6);
    adicionarAresta(&grafo, 3, 7);
    adicionarAresta(&grafo, 5, 8);
    adicionarAresta(&grafo, 5, 9);
    adicionarAresta(&grafo, 7, 10);
    adicionarAresta(&grafo, 7, 11);
    adicionarAresta(&grafo, 7, 12);
    adicionarAresta(&grafo, 9, 13);
    adicionarAresta(&grafo, 9, 14);

    // Exibe o rastreamento da BFS a partir do vértice 1 | EX1
    buscaEmLargura(&grafo, 1);

    // Reinicializa o grafo para utiliza-lo no exercício 2
    for (int i = 0; i < MAX_VERTICES; i++) {
        grafo.listaAdjacencia[i] = NULL;
    }

    // Começando exercicio 2
    adicionarAresta(&grafo, 0, 1);
    adicionarAresta(&grafo, 1, 2);
    adicionarAresta(&grafo, 1, 4);
    adicionarAresta(&grafo, 2, 3);
    adicionarAresta(&grafo, 2, 4);
    adicionarAresta(&grafo, 2, 9);
    adicionarAresta(&grafo, 3, 4);
    adicionarAresta(&grafo, 4, 5);
    adicionarAresta(&grafo, 4, 6);
    adicionarAresta(&grafo, 4, 7);
    adicionarAresta(&grafo, 5, 6);
    adicionarAresta(&grafo, 7, 8);
    adicionarAresta(&grafo, 7, 9);

    // Exibe o rastreamento da DFS a partir do vértice 0 | EX2
    buscaEmProfundidade(&grafo, 0);

    return 0;
}
