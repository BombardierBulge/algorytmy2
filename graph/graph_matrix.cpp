#ifndef GRAPH_MATRIX_CPP
#define GRAPH_MATRIX_CPP

#include "graph_matrix.hpp"

template<typename T>
GraphMatrix<T>::GraphMatrix(int V, T default_weight)
    : V(V), matrix(V, std::vector<T>(V, default_weight)), INF(default_weight) {}

template<typename T>
void GraphMatrix<T>::addEdge(int u, int v, T weight) {
    matrix[u][v] = weight;
}

template<typename T>
const std::vector<T>& GraphMatrix<T>::neighbors(int u) const {
    return matrix[u];
}

template<typename T>
void GraphMatrix<T>::print() const {
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (matrix[i][j] == INF)
                std::cout << "INF ";
            else
                std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

template<typename T>
int GraphMatrix<T>::vertices() const {
    return V;
}

template class GraphMatrix<int>;
template class GraphMatrix<float>;

#endif
