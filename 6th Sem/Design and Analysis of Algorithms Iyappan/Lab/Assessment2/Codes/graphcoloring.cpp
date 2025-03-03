#include <iostream>
#include <vector>
using namespace std;

bool isSafe(int v, vector<vector<int>> &graph, vector<int> &color, int c, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c) 
            return false;
    }
    return true;
}

bool graphColoringUtil(vector<vector<int>> &graph, int m, vector<int> &color, int v, int V) {
    if (v == V) 
        return true;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1, V)) 
                return true;
            color[v] = 0; 
        }
    }
    return false;
}

bool graphColoring(vector<vector<int>> &graph, int m, int V) {
    vector<int> color(V, 0);
    if (!graphColoringUtil(graph, m, color, 0, V)) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    cout << "Solution Exists: Assigned Colors: ";
    for (int i = 0; i < V; i++) 
        cout << color[i] << " ";
    cout << endl;
    return true;
}

int main() {
    int V, m;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "Enter the adjacency matrix (" << V * V << " values row-wise):" << endl;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    cout << "Enter the number of colors: ";
    cin >> m;

    graphColoring(graph, m, V);
    return 0;
}
