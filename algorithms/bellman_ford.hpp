#ifndef BELLMAN_FORD_HPP
#define BELLMAN_FORD_HPP

#include <vector>
#include <limits>
#include <iostream>

struct EdgeBF {
    int u, v;
    int weight;
};

class BellmanFord {
public:
    static std::vector<int> shortestPaths(int V, const std::vector<EdgeBF>& edges, int start);
};

#endif
