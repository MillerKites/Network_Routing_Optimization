// Source - https://codereview.stackexchange.com/q/285421
// Posted by Green 绿色, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-16, License - CC BY-SA 4.0

#include "a_star.h"

#include <memory>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <algorithm>

struct PathNode {
    NodeID node; // node
    Cost total_cost; // cost of reaching node from starting node
    Cost estimated_cost; // lower bound on the cost for any path from starting to target node through this node
    std::shared_ptr<PathNode> previous; // previous record
};

bool operator>(const PathNode& left, const PathNode& right) {
    return left.estimated_cost > right.estimated_cost;
}

Path backtrace(PathNode& last_record) {
    PathNode current = last_record;
    Path path {current.node};
    while (current.previous != nullptr) {
        current = *current.previous;
        path.emplace_back(current.node);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

Path a_star(AdjacencyList& adjacency,
            NodeID         start,
            NodeID         target,
            HeuristicFn&   heuristic) {
    std::set<NodeID> visited;
    std::priority_queue<PathNode, std::vector<PathNode>, std::greater<>> boundary;

    boundary.push({start, 0, heuristic(start, target), nullptr});
    visited.emplace(start);

    auto was_not_visited_yet = [visited] (Edge& entry) {
        return visited.find(entry.first) == visited.end();
    };

    for (; !boundary.empty(); boundary.pop()) {
        auto current = boundary.top();
        if (current.node == target) {
            return backtrace(current);
        }
        visited.emplace(current.node);

        auto edge_to_record = [current, heuristic, target] (Edge& edge) -> PathNode {
            Cost total_cost = current.total_cost + edge.second;
            Cost estimated_cost = total_cost + heuristic(current.node, target);
            return {edge.first, total_cost, estimated_cost, std::make_shared<PathNode>(current)};
        };

        for (auto& edge : adjacency[current.node]) {
            if (was_not_visited_yet(edge)) {
                boundary.push(edge_to_record(edge));
            }
        }
    }
    return {}; // no path to target
}

