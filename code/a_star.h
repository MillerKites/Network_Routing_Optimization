// a_star.h
#pragma once
#include <functional>
#include <map>
#include <unordered_map>
#include <vector>

namespace astar {
    typedef size_t NodeID;
    typedef float Cost;
    typedef std::pair<const NodeID, Cost> Edge;
    typedef std::unordered_map<NodeID, std::unordered_map<NodeID, Cost>> AdjacencyList;
    typedef std::vector<NodeID> Path;
    typedef const std::function<Cost(NodeID, NodeID)> HeuristicFn;

    Path a_star(AdjacencyList& adjacency,
                NodeID start,
                NodeID target,
                HeuristicFn& heuristic);
}
