#include <stdio.h>
#include <limits.h>
#define NODES 4

struct Connection {
    int start, end, cost;
};

void displayTable(int distances[], int size) {
    printf("Node \t Distance from Source\n");
    for (int i = 0; i < size; i++) {
        printf("%c \t %d\n", i + 'A', distances[i]);
    }
}

void calculatePaths(struct Connection connections[], int numConnections, int source) {
    int distances[NODES];
    for (int i = 0; i < NODES; i++)
        distances[i] = INT_MAX;
    distances[source] = 0;

    for (int i = 0; i < NODES - 1; i++) {
        for (int j = 0; j < numConnections; j++) {
            int startNode = connections[j].start;
            int endNode = connections[j].end;
            int connectionCost = connections[j].cost;
            if (distances[startNode] != INT_MAX && distances[startNode] + connectionCost < distances[endNode])
                distances[endNode] = distances[startNode] + connectionCost;
        }
    }
    displayTable(distances, NODES);
}

int main() {
    //constructing the graph given in the question
    struct Connection connections[] = {
        {0, 1, 2}, {1, 0, 2}, {0, 3, 1}, {3, 0, 1}, {1, 2, 3},
        {2, 1, 3}, {2, 3, 11}, {3, 2, 11}, {3, 1, 7}, {1, 3, 7}
    };
    int numConnections = sizeof(connections) / sizeof(connections[0]);
    printf("22BCE3799\nApurba Koirala\n");
    //printing final routing table for each node.
    for (int i = 0; i < NODES; i++) {
        printf("Routing table for node %c:\n", i + 'A');
        calculatePaths(connections, numConnections, i);
        printf("\n");
    }
    return 0;
}
