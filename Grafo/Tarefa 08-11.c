//Alunos: João Victor da Cruz Silvestre - RA:2144263
//        Paulo Mitsi - RA:2410362  

#include <stdlib.h>
#include <stdio.h>
#define VERDADEIRO 1
#define FALSO 0
typedef int Booleano;
typedef int Peso;

typedef struct NoAdjacencia{
    int vertice;
    Peso peso;
    struct NoAdjacencia *proximo;
} NoAdjacencia;

typedef struct NoVertice{
    NoAdjacencia *inicio;
} NoVertice;

typedef struct Grafo{
    int numVertices;
    int numArestas;
    NoVertice *listaAdjacencia;
} Grafo;

Grafo *inicializarGrafo(int numVertices){
    int i;

    Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
    grafo -> numVertices = numVertices;
    grafo -> numArestas = 0;
    grafo -> listaAdjacencia = (NoVertice *)malloc(numVertices * sizeof(NoVertice));

    for (i = 0; i < numVertices; i++){
        grafo -> listaAdjacencia[i].inicio = NULL;
    }
    return grafo;
}

NoAdjacencia *criarNoAdjacencia(int vertice, Peso peso){
    NoAdjacencia *novoNo = (NoAdjacencia *)malloc(sizeof(NoAdjacencia));
    novoNo -> vertice = vertice;
    novoNo -> peso = peso;
    novoNo -> proximo = NULL;
    return novoNo;
}

Booleano adicionarAresta(Grafo *grafo, int verticeOrigem, int verticeDestino, Peso peso){
    if(!grafo) return FALSO;
    if((verticeDestino < 0) || (verticeDestino >= grafo->numVertices)) return FALSO;
    if((verticeOrigem < 0) || (verticeOrigem >= grafo->numVertices)) return FALSO;

    NoAdjacencia *novoNo = criarNoAdjacencia(verticeDestino, peso);
    novoNo->proximo = grafo->listaAdjacencia[verticeOrigem].inicio;
    grafo->listaAdjacencia[verticeOrigem].inicio = novoNo;
    grafo->numArestas++;
    return VERDADEIRO;
}

void exibirGrafo(Grafo *grafo){
    printf("Numero de Vertices: %i. Numero de Arestas: %i \n", grafo->numVertices, grafo->numArestas);
    int i;

    for(i = 0; i < grafo->numVertices; i++){
        printf("Vertice %d:", i + 1);
        NoAdjacencia *no = grafo->listaAdjacencia[i].inicio;
        while (no){
            printf(" Vertice %d (%d) ", no->vertice + 1, no->peso);
            no = no->proximo;
        }
        printf("\n");
    }
}

void exibirMatrizAdjacencia(Grafo *grafo){ 
    printf("\n\nMatriz de Adjacencia:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            int adjacencia = 0;
            NoAdjacencia *no = grafo->listaAdjacencia[i].inicio;
            while (no) {
                if (no->vertice == j) {
                    adjacencia = no->peso;
                }
                no = no->proximo;
            }
            printf("%i\t", adjacencia);
        }
        printf("\n");
    }
}

int calcularSomaCaminhoDFS(Grafo *grafo, int inicio, int destino, int *visitados) {
    if (inicio == destino) {
        return 0;
    }

    visitados[inicio] = 1;
    NoAdjacencia *no = grafo->listaAdjacencia[inicio].inicio;
    int somaCaminhos = 0;

    while (no != NULL) {
        int proximoVertice = no->vertice;
        int pesoAresta = no->peso;

        if (!visitados[proximoVertice]) {
            somaCaminhos += pesoAresta + calcularSomaCaminhoDFS(grafo, proximoVertice, destino, visitados);
        }

        no = no->proximo;
    }

    visitados[inicio] = 0;
    return somaCaminhos;
}

int calcularSomaCaminho(Grafo *grafo, int inicio, int destino) {
    int *visitados = (int *)malloc(grafo->numVertices * sizeof(int));
    for (int i = 0; i < grafo->numVertices; i++) {
        visitados[i] = 0;
    }
    int soma = calcularSomaCaminhoDFS(grafo, inicio, destino, visitados);
    free(visitados);
    return soma;
}

int main (){

Grafo *grafo1 = inicializarGrafo(5);

adicionarAresta(grafo1, 0, 0, 0);
adicionarAresta(grafo1, 0, 2, 0);
adicionarAresta(grafo1, 1, 2, 0);
adicionarAresta(grafo1, 1, 3, 0);            
adicionarAresta(grafo1, 1, 4, 0);
adicionarAresta(grafo1, 2, 3, 0);
adicionarAresta(grafo1, 3, 4, 0);

// Lista de adjacência
printf("\nGrafo Listado:\n");
exibirGrafo(grafo1);

// Matriz de adjacência
exibirMatrizAdjacencia(grafo1);

// Segundo Grafo
printf("\n");
for(int l = 0; l < 25; l++) if(l < 24) printf("-"); else printf("\n");

Grafo *grafo2 = inicializarGrafo(5);

adicionarAresta(grafo2, 0, 0, 2); 
adicionarAresta(grafo2, 0, 2, 7);
adicionarAresta(grafo2, 2, 1, 5);
adicionarAresta(grafo2, 2, 3, 10);
adicionarAresta(grafo2, 3, 1, 9);
adicionarAresta(grafo2, 3, 4, 1);
adicionarAresta(grafo2, 4, 1, 12);

printf("Lista de Adjacencia (Grafo Orientado e Ponderado):\n");
exibirGrafo(grafo2);
printf("\n");
exibirMatrizAdjacencia(grafo2);
printf("\n");

// Soma dos caminhos {1,5} | Pedido no exercício
exibirGrafo(grafo2);
printf("\nValor total do caminho: %d ", calcularSomaCaminho(grafo2, 0, 4));

return 0;
}
