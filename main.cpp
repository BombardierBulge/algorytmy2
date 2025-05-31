#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "graph/graph_list.hpp"
#include "graph/graph_matrix.hpp"
#include "graph/generator.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/bellman_ford.hpp"

void test_structures() {
    std::cout << "Graf jako lista sąsiedztwa:\n";
    GraphList<int> g_list(5);
    g_list.addEdge(0, 1, 10);
    g_list.addEdge(0, 2, 3);
    g_list.addEdge(1, 2, 1);
    g_list.addEdge(2, 1, 4);
    g_list.addEdge(2, 3, 2);
    g_list.addEdge(3, 4, 7);
    g_list.print();

    std::cout << "\nGraf jako macierz sąsiedztwa:\n";
    GraphMatrix<int> g_mat(5);
    g_mat.addEdge(0, 1, 10);
    g_mat.addEdge(0, 2, 3);
    g_mat.addEdge(1, 2, 1);
    g_mat.addEdge(2, 1, 4);
    g_mat.addEdge(2, 3, 2);
    g_mat.addEdge(3, 4, 7);
    g_mat.print();
}
void benchmark_dijkstra_list() {
    std::ofstream file("dijkstra_list_benchmark.csv");
    file << "vertices,density,average_time_ms\n";
    std::vector<int> sizes = {10, 50, 100, 500, 1000};
    std::vector<double> densities = {0.25, 0.5, 0.75, 1.0};
    const int INSTANCES = 100;
    for (int V : sizes) {
        for (double d : densities) {
            std::cout << "Dijkstra (lista): Badanie dla V=" << V << ", density=" << d << "...\n";
            double total = 0.0;
            for (int i = 0; i < INSTANCES; ++i) {
                auto adj = generateRandomGraph(V, d);
                // Konwersja do GraphList
                GraphList<int> g_list(V);
                for (int u = 0; u < V; ++u)
                    for (auto& [v, w] : adj[u])
                        g_list.addEdge(u, v, w);
                // Konwersja do formatu Dijkstry
                std::vector<std::vector<std::pair<int, int>>> adj_dijkstra(V);
                for (int u = 0; u < V; ++u)
                    for (const auto& n : g_list.neighbors(u))
                        adj_dijkstra[u].emplace_back(n.target, n.weight);

                auto start = std::chrono::high_resolution_clock::now();
                Dijkstra<int>::shortestPaths(V, adj_dijkstra, 0);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                total += elapsed.count();
            }
            double avg = total / INSTANCES;
            file << V << "," << std::fixed << std::setprecision(4) << d << "," << avg << "\n";
        }
    }
    file.close();
    std::cout << "Benchmark Dijkstra (lista) zakończony.\n";
}

void benchmark_dijkstra_matrix() {
    std::ofstream file("dijkstra_matrix_benchmark.csv");
    file << "vertices,density,average_time_ms\n";
    std::vector<int> sizes = {10, 50, 100, 500, 1000};
    std::vector<double> densities = {0.25, 0.5, 0.75, 1.0};
    const int INSTANCES = 100;
    for (int V : sizes) {
        for (double d : densities) {
            std::cout << "Dijkstra (macierz): Badanie dla V=" << V << ", density=" << d << "...\n";
            double total = 0.0;
            for (int i = 0; i < INSTANCES; ++i) {
                auto adj = generateRandomGraph(V, d);
                GraphMatrix<int> g_mat(V);
                for (int u = 0; u < V; ++u)
                    for (auto& [v, w] : adj[u])
                        g_mat.addEdge(u, v, w);
                // Konwersja do formatu Dijkstry
                std::vector<std::vector<std::pair<int, int>>> adj_dijkstra(V);
                for (int u = 0; u < V; ++u) {
                    const auto& row = g_mat.neighbors(u);
                    for (int v = 0; v < V; ++v) {
                        if (row[v] != std::numeric_limits<int>::max())
                            adj_dijkstra[u].emplace_back(v, row[v]);
                    }
                }
                auto start = std::chrono::high_resolution_clock::now();
                Dijkstra<int>::shortestPaths(V, adj_dijkstra, 0);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                total += elapsed.count();
            }
            double avg = total / INSTANCES;
            file << V << "," << std::fixed << std::setprecision(4) << d << "," << avg << "\n";
        }
    }
    file.close();
    std::cout << "Benchmark Dijkstra (macierz) zakończony.\n";
}

void benchmark_bellman_ford_list() {
    std::ofstream file("bellman_ford_list_benchmark.csv");
    file << "vertices,density,average_time_ms\n";
    std::vector<int> sizes = {10, 50, 100, 500, 1000};
    std::vector<double> densities = {0.25, 0.5, 0.75, 1.0};
    const int INSTANCES = 100;
    for (int V : sizes) {
        for (double d : densities) {
            std::cout << "Bellman-Ford (lista): Badanie dla V=" << V << ", density=" << d << "...\n";
            double total = 0.0;
            for (int i = 0; i < INSTANCES; ++i) {
                auto adj = generateRandomGraph(V, d);
                GraphList<int> g_list(V);
                for (int u = 0; u < V; ++u)
                    for (auto& [v, w] : adj[u])
                        g_list.addEdge(u, v, w);
                // Konwersja do listy krawędzi
                std::vector<EdgeBF> edges;
                for (int u = 0; u < V; ++u)
                    for (const auto& n : g_list.neighbors(u))
                        edges.push_back({u, n.target, n.weight});

                auto start = std::chrono::high_resolution_clock::now();
                BellmanFord::shortestPaths(V, edges, 0);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                total += elapsed.count();
            }
            double avg = total / INSTANCES;
            file << V << "," << std::fixed << std::setprecision(4) << d << "," << avg << "\n";
        }
    }
    file.close();
    std::cout << "Benchmark Bellman-Ford (lista) zakończony.\n";
}

void benchmark_bellman_ford_matrix() {
    std::ofstream file("bellman_ford_matrix_benchmark.csv");
    file << "vertices,density,average_time_ms\n";
    std::vector<int> sizes = {10, 50, 100, 500, 1000};
    std::vector<double> densities = {0.25, 0.5, 0.75, 1.0};
    const int INSTANCES = 100;
    for (int V : sizes) {
        for (double d : densities) {
            std::cout << "Bellman-Ford (macierz): Badanie dla V=" << V << ", density=" << d << "...\n";
            double total = 0.0;
            for (int i = 0; i < INSTANCES; ++i) {
                auto adj = generateRandomGraph(V, d);
                GraphMatrix<int> g_mat(V);
                for (int u = 0; u < V; ++u)
                    for (auto& [v, w] : adj[u])
                        g_mat.addEdge(u, v, w);
                // Konwersja do listy krawędzi
                std::vector<EdgeBF> edges;
                for (int u = 0; u < V; ++u) {
                    const auto& row = g_mat.neighbors(u);
                    for (int v = 0; v < V; ++v) {
                        if (row[v] != std::numeric_limits<int>::max())
                            edges.push_back({u, v, row[v]});
                    }
                }
                auto start = std::chrono::high_resolution_clock::now();
                BellmanFord::shortestPaths(V, edges, 0);
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = end - start;
                total += elapsed.count();
            }
            double avg = total / INSTANCES;
            file << V << "," << std::fixed << std::setprecision(4) << d << "," << avg << "\n";
        }
    }
    file.close();
    std::cout << "Benchmark Bellman-Ford (macierz) zakończony.\n";
}

int main() {
    std::cout << "Wybierz opcję:\n";
    std::cout << "1. Test struktur grafowych\n";
    std::cout << "2. Benchmark Dijkstra (lista i macierz)\n";
    std::cout << "3. Benchmark Bellman-Ford (lista i macierz)\n";
    std::cout << "Twój wybór: ";
    int wybor;
    std::cin >> wybor;

    if (wybor == 1) {
        test_structures();
    } else if (wybor == 2) {
        std::cout << "Rozpoczynam benchmark Dijkstra dla listy sąsiedztwa...\n";
        benchmark_dijkstra_list();
        std::cout << "Rozpoczynam benchmark Dijkstra dla macierzy sąsiedztwa...\n";
        benchmark_dijkstra_matrix();
    } else if (wybor == 3) {
        std::cout << "Rozpoczynam benchmark Bellman-Ford dla listy sąsiedztwa...\n";
        benchmark_bellman_ford_list();
        std::cout << "Rozpoczynam benchmark Bellman-Ford dla macierzy sąsiedztwa...\n";
        benchmark_bellman_ford_matrix();
    } else {
        std::cout << "Nieznany wybór.\n";
    }
    return 0;
}