#include <stdio.h>
#include <limits.h>

#define V 6

int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int n) {
    printf("22BCE3799 \nApurba Koirala\n\n");
    printf("The minimum distances for each routers from the mentioned source router A is as follows: \n\n");
    for (int i = 1; i < V; i++)
        printf("%c \t %d\n", i + 'A', dist[i]);
    printf("\n");
    printf("Understanding that distance from A to A is 0.");
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    int sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = 1;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist, V);
}

int main() {
    int graph[V][V] = {
        {0, 4, 5, 0, 0, 0},
        {4, 0, 0, 3, 0, 5},
        {5, 0, 0, 6, 2, 0},
        {0, 3, 6, 0, 0, 5},
        {0, 0, 2, 0, 0, 3},
        {0, 5, 0, 5, 3, 0},
    };

    dijkstra(graph, 0); // source node (router) A as per the question, if B was to be the source node, (graph, 1) was to be passed

    return 0;
}
