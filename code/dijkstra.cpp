#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

/*
- n = V
- source = Node 0
- graph
*/

// Infinity constant to initialize distances
const int INF = numeric_limits<int>::max();

// Structure to represent an edge (neighbor node and weight)
struct Edge {
    int to;
    int weight;
};

void dijkstra(int n, int source, const vector<vector<pair<int,int>>>& adj) {
    vector<int> dist(n, INF);
    dist[source] = 0;

    priority_queue<
        pair<int, int>, 
        vector<pair<int, int>>, 
        greater<pair<int, int>>
    > pq;
    
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // skip outdated entries
        if (d > dist[u]) continue;

        // relax edges
        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print shortest distances
    int minDist = INF;

for (int i = 0; i < n; i++) {
    if (i != source) {
        minDist = min(minDist, dist[i]);
    }
}

if (minDist == INF) {
    cout << "No reachable nodes\n";
} else {
    cout << "Smallest distance from Node " << source << " = " << minDist << "\n";
}
}
