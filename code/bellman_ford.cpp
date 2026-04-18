#include <iostream>
#include <vector>
#include <climits>

using namespace std;

namespace bellmanford {

    struct Edge {
        int source;
        int destination;
        int weight;
    };

    vector<int> bellmanFord(vector<Edge>& graph, int vertices, int source)
    {
        vector<int> distance(vertices, INT_MAX);
        distance[source] = 0;

        for (int i = 0; i < vertices - 1; i++) {
            for (const Edge& e : graph) {
                if (distance[e.source] != INT_MAX &&
                    distance[e.source] + e.weight < distance[e.destination]) {

                    distance[e.destination] =
                        distance[e.source] + e.weight;
                }
            }
        }

        for (const Edge& e : graph) {
            if (distance[e.source] != INT_MAX &&
                distance[e.source] + e.weight < distance[e.destination]) {
                cout << "Graph contains negative weight cycle\n";
                return {};
            }
        }

        return distance;
    }

}
