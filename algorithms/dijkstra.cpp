#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP

#include "dijkstra.hpp"

template<typename T>
std::vector<T> Dijkstra<T>::shortestPaths(int V,
    const std::vector<std::vector<std::pair<int, T>>>& adj, int start) {

    const T INF = std::numeric_limits<T>::max();
    std::vector<T> dist(V, INF);
    dist[start] = 0;

    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto& [v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

template class Dijkstra<int>;
template class Dijkstra<float>;

#endif
