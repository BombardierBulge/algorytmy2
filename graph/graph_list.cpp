#ifndef GRAPH_LIST_CPP
#define GRAPH_LIST_CPP

#include "graph_list.hpp"

template<typename T>
GraphList<T>::GraphList(int V) : V(V), adj(V) {}

template<typename T>
void GraphList<T>::addEdge(int u, int v, T weight) {
    Neighbor<T> neighbor = {v, weight};
    adj[u].push_back(neighbor);
}

template<typename T>
const std::vector<Neighbor<T>>& GraphList<T>::neighbors(int u) const {
    return adj[u];
}

template<typename T>
void GraphList<T>::print() const {
    for (int i = 0; i < V; ++i) {
        std::cout << i << ": ";
        for (const auto& neighbor : adj[i]) {
            std::cout << "(" << neighbor.target << ", w=" << neighbor.weight << ") ";
        }
        std::cout << "\n";
    }
}

template<typename T>
int GraphList<T>::vertices() const {
    return V;
}

template class GraphList<int>;
template class GraphList<float>;

#endif
