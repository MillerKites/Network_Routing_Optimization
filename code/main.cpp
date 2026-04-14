#include "graph_generator.cpp"
#include <chrono>

// Included Algorithms . . .
#include "dijkstra.cpp"

int main() {
    // Set graph parameters
    int V = 1000;
    int E = 5000;

    // Makes the graph with V & E parameters
    auto graph = generateGraph(V,E);
    printGraph(graph);
    cout << endl << endl;


    // Dijkstra Algorithm
    auto start1 = std::chrono::high_resolution_clock::now();
    
    dijkstra(V, 0, graph);
    cout << endl;

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1-start1;
    cout << "Dijkstra Elapsed Time: " << duration1.count() * 1000 << "ms" << endl;

    // Algorithm #...
    // Algorithm #...
    // Algorithm #...
    
    
    return 0;
}
