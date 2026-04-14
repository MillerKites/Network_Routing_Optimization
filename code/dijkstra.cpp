#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Infinity constant to initialize distances
const int INF = numeric_limits<int>::max();

// Structure to represent an edge (neighbor node and weight)
struct Edge {
    int to;
    int weight;
};

void dijkstra(int n, int source, const vector<vector<Edge>>& adj) {
    // 1. Initialize distances to infinity and source to 0
    vector<int> dist(n, INF);
    dist[source] = 0;

    // 2. Min-priority queue: stores {distance, vertex}
    // Greater comparison makes it a min-heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Skip if we already found a shorter path to u
        if (d > dist[u]) continue;

        // 3. Relax neighbors
        for (auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest distances
    for (int i = 0; i < n; i++) {
        cout << "Distance from " << source << " to " << i << ": ";
        if (dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}
