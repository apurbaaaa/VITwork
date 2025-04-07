#include <iostream>
#include <climits>  
#include <queue>
#include <string.h>
using namespace std;
bool bfs(int rGraph[][7], int s, int t, int parent[]) {
    bool visited[7];
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < 7; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    return visited[t];
}
int fordFulkerson(int graph[7][7], int s, int t) {
    int u, v;
    int rGraph[7][7];

    for (u = 0; u < 7; u++)
        for (v = 0; v < 7; v++)
            rGraph[u][v] = graph[u][v];

    int parent[7];
    int max_flow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}
int main() {
    int graph[7][7] = { {0, 7, 0, 0, 10, 0, 0},  
                        {0, 0, 5, 0, 1, 3, 0},   
                        {0, 0, 0, 2, 0, 0, 10},  
                        {0, 0, 0, 0, 0, 0, 4},  
                        {0, 0, 0, 7, 0, 2, 0},  
                        {0, 0, 3, 2, 0, 0, 0},  
                        {0, 0, 0, 0, 0, 0, 0} };

    cout << "The maximum flow: " << fordFulkerson(graph, 0, 6)<<endl;
    return 0;
}

