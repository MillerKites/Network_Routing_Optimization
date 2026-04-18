#include "a_star.h"

#include <memory>
#include <queue>
#include <set>
#include <algorithm>

namespace astar {

    struct PathNode {
        NodeID node;
        Cost total_cost;
        Cost estimated_cost;
        std::shared_ptr<PathNode> previous;
    };

    bool operator>(const PathNode& left, const PathNode& right) {
        return left.estimated_cost > right.estimated_cost;
    }

    Result backtrace(PathNode current) {
        std::vector<NodeID> path;
        Cost cost = current.total_cost;

        while (true) {
            path.push_back(current.node);
            if (current.previous == nullptr) break;
            current = *current.previous;
        }

        std::reverse(path.begin(), path.end());
        return { path, cost };
    }

    Result a_star(AdjacencyList& adjacency,
                  NodeID start,
                  NodeID target,
                  HeuristicFn& heuristic) {

        std::set<NodeID> visited;

        std::priority_queue<
            PathNode,
            std::vector<PathNode>,
            std::greater<>
        > boundary;

        boundary.push({
            start,
            0,
            heuristic(start, target),
            nullptr
        });

        while (!boundary.empty()) {

            PathNode current = boundary.top();
            boundary.pop();

            // skip already processed nodes
            if (visited.find(current.node) != visited.end())
                continue;

            visited.insert(current.node);

            // goal check
            if (current.node == target) {
                return backtrace(current);
            }

            // expand neighbors
            for (auto& edge : adjacency[current.node]) {

                NodeID neighbor = edge.first;
                Cost weight = edge.second;

                if (visited.find(neighbor) != visited.end())
                    continue;

                Cost new_cost = current.total_cost + weight;
                Cost priority = new_cost + heuristic(neighbor, target);

                boundary.push({
                    neighbor,
                    new_cost,
                    priority,
                    std::make_shared<PathNode>(current)
                });
            }
        }

        return { {}, 0 }; // no path found
    }

}
