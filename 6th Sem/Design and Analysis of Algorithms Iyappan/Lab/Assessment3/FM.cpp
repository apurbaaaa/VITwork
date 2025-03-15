#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

void floydWarshall(map<char, map<char, int> > &graph, vector<char> &vertices) {
    int numVertices = vertices.size();
    
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                char start = vertices[i], end = vertices[j], intermediate = vertices[k];
                
                if (graph[start][intermediate] != INT_MAX && graph[intermediate][end] != INT_MAX &&
                    (graph[start][end] == INT_MAX || graph[start][end] > graph[start][intermediate] + graph[intermediate][end])) {
                    graph[start][end] = graph[start][intermediate] + graph[intermediate][end];
                }
            }
        }
    }
}

int main() {
    int numVertices, numEdges;
    
    cout << "Enter the number of vertices: ";
    cin >> numVertices;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<char> vertices(numVertices);
    map<char, map<char, int> > graph;

    cout << "Enter the vertex labels: ";
    for (int i = 0; i < numVertices; i++) {
        cin >> vertices[i];
        for (int j = 0; j < numVertices; j++) {
            graph[vertices[i]][vertices[j]] = (i == j) ? 0 : INT_MAX;
        }
    }

    cout << "Enter edges in format (source destination weight):" << endl;
    for (int i = 0; i < numEdges; i++) {
        char source, destination;
        int weight;
        cin >> source >> destination >> weight;
        graph[source][destination] = weight;
    }

    floydWarshall(graph, vertices);

    cout << "\nAll-Pairs Shortest Paths:\n   ";
    for (char vertex : vertices) {
        cout << vertex << "\t";
    }
    cout << "\n-------------------------------------------------\n";

    for (char start : vertices) {
        cout << start << " | ";
        for (char end : vertices) {
            if (graph[start][end] == INT_MAX)
                cout << "INF\t";
            else
                cout << graph[start][end] << "\t";
        }
        cout << endl;
    }

    return 0;
}
