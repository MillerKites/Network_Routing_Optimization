#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


// Testing if edge has been visited
bool edgeExists(const vector<vector<pair<int,int>>>& graph, int u, int v) {
    for (auto edge : graph[u]) {
        if (edge.first == v) return true;
    }
    return false;
}

// Function to generate a random weighted graph
vector<vector<pair<int, int>>> generateGraph(int V, int E) {
    vector<vector<pair<int, int>>> graph(V);
   
    int maxEdges = V * (V - 1) / 2;

    if (E > maxEdges) {
        cout << "Too many edges! Max possible is " << maxEdges << endl;
        E = maxEdges;
    }

    srand(time(0)); // seed for randomness
    
    for (int i = 0; i < E; i++) {
        int u = rand() % V;
        int v = rand() % V;

        // avoid self-loops
        if (u == v || edgeExists(graph, u, v)) continue;

        int weight = rand() % 30 + 1; // weights from 1 to 10

        graph[u].push_back({v, weight});
        graph[v].push_back({u, weight}); // remove this if directed graph
    }

    return graph;
}

// For testing graph generator
void printGraph(const vector<vector<pair<int, int>>>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        cout << "Node " << i << ": ";
        for (auto edge : graph[i]) {
            cout << "-> (" << edge.first << ", w=" << edge.second << ") ";
        }
        cout << endl;
    }
}
