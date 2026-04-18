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

int dijkstra(int n, int source, int target, const vector<vector<pair<int,int>>>& adj) {
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

        // stop loop if we find the target
        if (u == target) break;

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

    if (dist[target] == INF) {
        cout << "No path from Node " << source << " to Node " << target << "\n";
    } else {
        cout << "Shortest distance from Node " << source 
            << " to Node " << target 
            << " = " << dist[target] << "\n";
    }

    return dist[target];
}
