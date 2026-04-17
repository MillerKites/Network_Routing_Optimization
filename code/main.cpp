#include "graph_generator.cpp"
#include <chrono>

// Included Algorithms . . .
#include "dijkstra.cpp"
#include "Astar.cpp"
#include "bellman_ford.cpp"

int main() {
    // Set graph parameters
    
    // Small
    //int V = 1000;
    //int E = 5000;
    
    // Medium
    
    //int V = 5000;
    //int E = 25000;
    
    
    // Large
    int V = 10000;
    int E = 50000;
    
    
    // Makes the graph with V & E parameters
    auto graph = generateGraph(V,E);
    // printGraph(graph);
    cout << endl << endl;
    
    auto heuristic = [](astar::NodeID a, astar::NodeID b) -> astar::Cost {
    return 0;
    };

   astar::AdjacencyList adjList;
    for (int u = 0; u < V; u++) {
        for (auto& edge : graph[u]) {
                adjList[u][edge.first] = (astar::Cost)edge.second;
            }
        }

    // Dijkstra Algorithm
    auto start1 = std::chrono::high_resolution_clock::now();
    
    dijkstra(V, 0, graph);
    cout << endl;

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1-start1;
    cout << "Dijkstra Elapsed Time: " << duration1.count() * 1000 << "ms" << endl;

    // A* search Algorithm
    auto start2 = std::chrono::high_resolution_clock::now();

    astar::Path result = astar::a_star(adjList, 0, V - 1, heuristic);
    cout << endl;

    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;
    cout << "A* Elapsed Time: " << duration2.count() * 1000 << "ms" << endl;
    

    cout << endl;

    // Bellman-Ford Algorithm
    vector<bellmanford::Edge> bfEdges;
    for (int u = 0; u < V; u++) {
        for (auto& edge : graph[u]) {
            bfEdges.push_back({u, edge.first, edge.second});
        }
    }
    auto start3 = std::chrono::high_resolution_clock::now();

     bellmanford::bellmanFord(bfEdges, V, 0);

    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3 = end3 - start3;
    cout << "Bellman-Ford Elapsed Time: " << duration3.count() * 1000 << "ms" << endl;

    cout << endl;

    // Algorithm #...
    
    
    return 0;
}
