#include "graph_generator.cpp"
#include <chrono>

int main() {
    // Set graph parameters
    int V = 2;
    int E = 10;

    // Makes the graph with V & E parameters
    auto graph = generateGraph(V,E);
    printGraph(graph);
    cout << endl << endl;


    // Algorithm 1
    auto start = std::chrono::high_resolution_clock::now();

    // * code *

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end-start;
    cout << "Algorithm 1 Elapsed Time: " << duration1.count() << " seconds" << endl;


    // Algorithm 2
    auto start = std::chrono::high_resolution_clock::now();

    // * code *

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end-start;
    cout << "Algorithm 2 Elapsed Time: " << duration1.count() << " seconds" << endl;

    // Algorithm #...
    // Algorithm #...
    // Algorithm #...
    
    
    return 0;
}
