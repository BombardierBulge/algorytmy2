#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

#include <vector>
#include <iostream>
#include <limits>

template<typename T>
class GraphMatrix {
    int V;
    std::vector<std::vector<T>> matrix;
    T INF;

public:
    GraphMatrix(int V, T default_weight = std::numeric_limits<T>::max());
    void addEdge(int u, int v, T weight);
    const std::vector<T>& neighbors(int u) const;
    void print() const;
    int vertices() const;
};

#include "graph_matrix.cpp"

#endif
