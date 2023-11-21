//Alunos: João Victor da Cruz Silvestre     RA:2144263
//        Paulo Mitsi                          2410362

#include <stdio.h>
#define NUM_VERTICES 6
#define INFINITO 99999

void imprimirSolucao(int distancia[], int n){
    printf("Vertice   Distancia da Origem\n");
    for (int i = 0; i < NUM_VERTICES; i++)
        printf("%d \t\t %d\n", i, distancia[i]);
}

void dijkstra(int grafo[NUM_VERTICES][NUM_VERTICES], int origem){
    int distancia[NUM_VERTICES];
    int conjuntoSPT[NUM_VERTICES];
    for (int i = 0; i < NUM_VERTICES; i++){
        distancia[i] = INFINITO;
        conjuntoSPT[i] = 0;
    }
    distancia[origem] = 0;
    for (int contador = 0; contador < NUM_VERTICES-1; contador++){
        int minimo = INFINITO, indiceMinimo;
        for (int vertice = 0; vertice < NUM_VERTICES; vertice++)
            if (conjuntoSPT[vertice] == 0 && distancia[vertice] <= minimo)
                minimo = distancia[vertice], indiceMinimo = vertice;
        int u = indiceMinimo;
        conjuntoSPT[u] = 1;
        for (int vertice = 0; vertice < NUM_VERTICES; vertice++)
            if (!conjuntoSPT[vertice] && grafo[u][vertice] && distancia[u] != INFINITO && distancia[u]+grafo[u][vertice] < distancia[vertice])
                distancia[vertice] = distancia[u] + grafo[u][vertice];
    }
    imprimirSolucao(distancia, NUM_VERTICES);
}

int main(){
    int grafo[NUM_VERTICES][NUM_VERTICES] = {{0, 1, 4, 0, 0, 0},
                                             {1, 0, 4, 2, 7, 0},
                                             {4, 4, 0, 3, 5, 0},
                                             {0, 2, 3, 0, 4, 6},
                                             {0, 7, 5, 4, 0, 7},
                                             {0, 0, 0, 6, 7, 0}
                                            };
    dijkstra(grafo, 0);
    return 0;
}
