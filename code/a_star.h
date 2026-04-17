// Source - https://codereview.stackexchange.com/q/285421
// Posted by Green 绿色, modified by community. See post 'Timeline' for change history
// Retrieved 2026-04-16, License - CC BY-SA 4.0

#include <functional>
#include <map>
#include <vector>

typedef size_t NodeID;
typedef float Cost;
typedef std::pair<const NodeID, Cost> Edge;
typedef std::map<const NodeID, std::map<const NodeID, Cost>> AdjacencyList;
typedef std::vector<NodeID> Path;
typedef const std::function<Cost(NodeID, NodeID)> HeuristicFn;


Path a_star(AdjacencyList& adjacency,
            NodeID         start,
            NodeID         target,
            HeuristicFn&   heuristic);
