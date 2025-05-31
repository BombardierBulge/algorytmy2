#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <vector>
#include <queue>
#include <limits>

template<typename T>
class Dijkstra {
public:
    static std::vector<T> shortestPaths(int V,
        const std::vector<std::vector<std::pair<int, T>>>& adj, int start);
};

#include "dijkstra.cpp"

#endif