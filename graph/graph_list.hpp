#ifndef GRAPH_LIST_HPP
#define GRAPH_LIST_HPP

#include <vector>
#include <iostream>

template<typename T>
struct Neighbor {
    int target;
    T weight;
};

template<typename T>
class GraphList {
    int V;
    std::vector<std::vector<Neighbor<T>>> adj;

public:
    GraphList(int V);
    void addEdge(int u, int v, T weight);
    const std::vector<Neighbor<T>>& neighbors(int u) const;
    void print() const;
    int vertices() const;
};

#include "graph_list.cpp"

#endif