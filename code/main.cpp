#include "graph_generator.cpp"

// Extra Libraries
#include <chrono>
#include <cstdlib>
#include <iomanip>

// Included Algorithms . . .
#include "dijkstra.cpp"
#include "Astar.cpp"
#include "bellman_ford.cpp"

int main() {

    // Seed random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    // Set graph parameters
    int V = 1000;
    int E = 5000;
    int source = 0;
    int target = 666;

    // Makes the graph with V & E parameters
    auto graph = generateGraph(V,E);
    cout << endl << endl;


    /*
        Dijkstra Algorithm
        Goal: Find shortest path to specific node
    */

    cout << "Dijkstra Algorithm Test" << "\nOutput: Time it takes to find the shortest path to Node " 
                                     << target << " from Node " << source << "\n\n";
    
    auto start1 = std::chrono::high_resolution_clock::now();
    int cost1 = dijkstra(V, source, target, graph);
    auto end1 = std::chrono::high_resolution_clock::now();
    double ms1 = chrono::duration<double, milli>(end1-start1).count();


    /*
        A* Algorithm
        Goal: Find shortest path to specific node
    */

    cout << "A* Algorithm Test" << "\nOutput: Time it takes to find the shortest path to Node " 
                                      << target << " from Node " << source << "\n\n";

    // Heuristics
    auto heuristic = [](astar::NodeID a, astar::NodeID b) -> astar::Cost {
    return abs((int)a - (int)b); // or 0
    };

    astar::AdjacencyList adjList;
    for (int u = 0; u < V; u++) {
        for (auto& edge : graph[u]) {
            adjList[u][edge.first] = static_cast<astar::Cost>(edge.second);
        }
    }

    auto start2 = std::chrono::high_resolution_clock::now();
    astar::Result result = astar::a_star(adjList, source, target, heuristic);
    auto end2 = std::chrono::high_resolution_clock::now();
    double ms2 = chrono::duration<double, milli>(end2-start2).count();

    if (result.path.empty()) {
        cout << "No path found\n";
    } else {
        cout << "Shortest distance from Node " << source << " to Node " << target 
             << " = " << result.cost << "\n";

        cout << "Path: ";
        for (auto node : result.path) {
            cout << node << " ";
        }
        cout << endl;
    }


    
    /*
        Bellman-Ford Algorithm
        Goal: Find shortest path to specific node
    */ 

    vector<bellmanford::Edge> bfGraph;
    for (int u = 0; u < V; u++) {
        for (auto& edge : graph[u]) {
            bfGraph.push_back({u, edge.first, edge.second});
        }
    }
    
    cout << "Bellman-Ford Algorithm Test" << "\nOutput: Time it takes to find the shortest path to Node " 
                                      << target << " from Node " << source << "\n\n";

    auto start3 = std::chrono::high_resolution_clock::now();
    vector<int> dist = bellmanford::bellmanFord(bfGraph, V, source);
    auto end3 = std::chrono::high_resolution_clock::now();
    double ms3 = chrono::duration<double, milli>(end3-start3).count();;




    /*
        OUTPUTS
    */

    cout << "\n===================== ALGORITHM =======================\n";
    cout << left << setw(15) << "Algorithm"
         << setw(15) << "Time (ms)"
         << setw(15) << "Cost" << "\n";

    cout << "--------------------------------------------------------\n";
    cout << left << setw(15) << "Dijkstra"
         << setw(15) << ms1
         << setw(15) << cost1 << "\n";
    cout << left << setw(15) << "A*"
         << setw(15) << ms2
         << setw(15) << result.cost << "\n";
    cout << left << setw(15) << "Bellman-Ford"
         << setw(15) << ms3
         << setw(15) << dist[target] << "\n\n\n";


    return 0;
}
