#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

class GreedyAlgorithms {
public:

    // 1. Selection Sort using Greedy approach
    static void selectionSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex])
                    minIndex = j;
            }
            swap(arr[i], arr[minIndex]);
        }
    }

    // 2. Job Scheduling Problem: returns maximum profit
    static int jobScheduling(vector<int>& profits, vector<int>& deadlines) {
        int n = profits.size();
        vector<pair<int, int>> jobs;
        for (int i = 0; i < n; ++i)
            jobs.push_back({profits[i], deadlines[i]});

        // Sort by profit descending
        sort(jobs.begin(), jobs.end(), greater<pair<int, int>>());

        int maxDeadline = 0;
        for (auto& job : deadlines)
            maxDeadline = max(maxDeadline, job);

        vector<bool> slot(maxDeadline + 1, false);
        int totalProfit = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = jobs[i].second; j > 0; --j) {
                if (!slot[j]) {
                    slot[j] = true;
                    totalProfit += jobs[i].first;
                    break;
                }
            }
        }
        return totalProfit;
    }

    // 3. Dijkstra's Algorithm: shortest path from src to all nodes
    static vector<int> dijkstra(int V, vector<vector<pair<int, int>>>& adj, int src) {
        vector<int> dist(V, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

int main() {
    // Test Selection Sort
    vector<int> arr = {29, 10, 14, 37, 14};
    GreedyAlgorithms::selectionSort(arr);
    cout << "Sorted Array: ";
    for (int i : arr) cout << i << " ";
    cout << endl;

    // Test Job Scheduling
    vector<int> profits = {100, 19, 27, 25, 15};
    vector<int> deadlines = {2, 1, 2, 1, 3};
    int maxProfit = GreedyAlgorithms::jobScheduling(profits, deadlines);
    cout << "Maximum Profit: " << maxProfit << endl;

    // Test Dijkstra's Algorithm
    int V = 5;
    vector<vector<pair<int, int>>> adj(V);
    adj[0].push_back({1, 10});
    adj[0].push_back({4, 5});
    adj[1].push_back({2, 1});
    adj[2].push_back({3, 4});
    adj[4].push_back({1, 3});
    adj[4].push_back({2, 9});
    adj[4].push_back({3, 2});

    vector<int> distances = GreedyAlgorithms::dijkstra(V, adj, 0);
    cout << "Shortest distances from node 0: ";
    for (int d : distances) cout << d << " ";
    cout << endl;

    return 0;
}
