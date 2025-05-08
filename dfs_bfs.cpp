#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Recursive DFS
    void DFSUtil(int node, vector<bool>& visited, int level) {
        visited[node] = true;
        cout << "Visited Node: " << node << " at Level: " << level << endl;

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited, level + 1);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "\n--- Depth First Search (DFS) ---\n";
        DFSUtil(start, visited, 0);
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<pair<int, int>> q; // pair of node and level

        q.push({start, 0});
        visited[start] = true;

        cout << "\n--- Breadth First Search (BFS) ---\n";

        while (!q.empty()) {
            int node = q.front().first;
            int level = q.front().second;
            q.pop();

            cout << "Visited Node: " << node << " at Level: " << level << endl;

            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, level + 1});
                }
            }
        }
    }
};

int main() {
    Graph g(7);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    int startNode = 0;
    g.DFS(startNode);
    g.BFS(startNode);

    return 0;
}
