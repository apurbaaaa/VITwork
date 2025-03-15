#include <iostream>
#include <cstdlib>
#include <climits>
#include <map>
using namespace std;

struct Edge {
    char startVertex, endVertex;
    int edgeWeight;
};

struct Graph {
    int numVertices, numEdges;
    struct Edge* edges;
};

struct Graph* initializeGraph(int vertices, int edges) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->numEdges = edges;
    graph->edges = (struct Edge*)malloc(graph->numEdges * sizeof(struct Edge));
    return graph;
}

void displayFinalDistances(map<char, int>& distanceMap) {
    cout << "\nVertex\tMinimum Distance from Source" << endl;
    for (auto& entry : distanceMap) {
        cout << entry.first << "\t\t" << entry.second << endl;
    }
}

void bellmanFord(struct Graph* graph, char sourceVertex) {
    int vertices = graph->numVertices;
    int edges = graph->numEdges;
    map<char, int> shortestDistances;

    for (int i = 0; i < edges; i++) {
        shortestDistances[graph->edges[i].startVertex] = INT_MAX;
        shortestDistances[graph->edges[i].endVertex] = INT_MAX;
    }

    shortestDistances[sourceVertex] = 0;
    
    for (int i = 1; i <= vertices - 1; i++) {
        for (int j = 0; j < edges; j++) {
            char u = graph->edges[j].startVertex;
            char v = graph->edges[j].endVertex;
            int weight = graph->edges[j].edgeWeight;
            
            if (shortestDistances[u] != INT_MAX && shortestDistances[u] + weight < shortestDistances[v]) {
                shortestDistances[v] = shortestDistances[u] + weight;
            }
        }
    }
    
    for (int i = 0; i < edges; i++) {
        char u = graph->edges[i].startVertex;
        char v = graph->edges[i].endVertex;
        int weight = graph->edges[i].edgeWeight;
        
        if (shortestDistances[u] != INT_MAX && shortestDistances[u] + weight < shortestDistances[v]) {
            cout << "\nWarning: The graph contains a negative weight cycle!" << endl;
            return;
        }
    }
    
    displayFinalDistances(shortestDistances);
}

int main() {
    int vertices, edges;
    char source;
    
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;
    cout << "Enter the source vertex: ";
    cin >> source;
    
    struct Graph* graph = initializeGraph(vertices, edges);
    
    for (int i = 0; i < edges; i++) {
        cout << "\nEnter properties for edge " << i + 1 << " (Start Vertex, End Vertex, Weight): ";
        cin >> graph->edges[i].startVertex >> graph->edges[i].endVertex >> graph->edges[i].edgeWeight;
    }
    
    bellmanFord(graph, source);
    
    return 0;
}