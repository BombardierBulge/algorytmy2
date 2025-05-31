#include "bellman_ford.hpp"

std::vector<int> BellmanFord::shortestPaths(int V, const std::vector<EdgeBF>& edges, int start) {
    const int INF = std::numeric_limits<int>::max();
    std::vector<int> dist(V, INF);
    dist[start] = 0;

    for (int i = 1; i < V; ++i) {
        for (const auto& e : edges) {
            if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.weight) {
                dist[e.v] = dist[e.u] + e.weight;
            }
        }
    }

    for (const auto& e : edges) {
        if (dist[e.u] != INF && dist[e.v] > dist[e.u] + e.weight) {
            std::cerr << "Ujemny cykl wykryty!\n";
            return {};
        }
    }

    return dist;
}
