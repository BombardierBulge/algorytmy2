#include "generator.hpp"
#include <set>
#include <cstdlib>
#include <ctime>

std::vector<std::vector<std::pair<int, int>>> generateRandomGraph(int V, double density) {
    std::vector<std::vector<std::pair<int, int>>> adj(V);
    std::set<std::pair<int, int>> edges;
    int maxEdges = V * (V - 1) / 2;
    int E = static_cast<int>(density * maxEdges);

    srand(static_cast<unsigned>(time(nullptr)));

    while (static_cast<int>(edges.size()) < E) {
        int u = rand() % V;
        int v = rand() % V;
        if (u == v || edges.count({u, v}) || edges.count({v, u})) continue;

        int weight = rand() % 100 + 1;
        adj[u].emplace_back(v, weight);  // skierowany
        edges.insert({u, v});
    }

    return adj;
}
