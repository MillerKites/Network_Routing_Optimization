// C++ program for implementing the Bellman-Ford algorithm

#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

namespace bellmanford {
    // Structure to represent an edge in the graph
    struct Edge {
        int source, destination, weight;
    };

    // Function to run the Bellman-Ford algorithm
    void bellmanFord(vector<Edge>& graph, int vertices,
                    int source)
    {
        // Initialize distances from source to all vertices as
        // INFINITE
        vector<int> distance(vertices, INT_MAX);
        distance[source] = 0; // Distance to source itself is 0

        // Relax all edges |V| - 1 times (where |V| is the
        // number of vertices)
        for (int i = 0; i < vertices - 1; ++i) {
            // Iterate through all edges
            for (const Edge& e : graph) {
                // Update distances if a shorter path is found
                if (distance[e.source] != INT_MAX
                    && distance[e.source] + e.weight
                        < distance[e.destination]) {
                    distance[e.destination]
                        = distance[e.source] + e.weight;
                }
            }
        }

        // Check for negative-weight cycles by iterating through
        // all edges again
        for (const Edge& e : graph) {
            if (distance[e.source] != INT_MAX
                && distance[e.source] + e.weight
                    < distance[e.destination]) {
                cout
                    << "Graph contains negative weight cycle\n";
                return;
            }
        }

        // Print shortest distances from source to all vertices
        /*cout << "Vertex   Distance from Source\n";
        for (int i = 0; i < vertices; ++i) {
            cout << i << "\t\t" << distance[i] << "\n";
        }*/
    }
}
