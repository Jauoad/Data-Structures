// ﷽
// HamiltonianGraph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adjMatrix;

    bool isSafe(int v, std::vector<int>& path, int pos) {
        if (adjMatrix[path[pos - 1]][v] == 0) {
            return false;
        }

        for (int i = 0; i < pos; ++i) {
            if (path[i] == v) {
                return false;
            }
        }

        return true;
    }

    bool hamiltonianCycleUtil(std::vector<int>& path, int pos) {
        if (pos == V) {
            if (adjMatrix[path[pos - 1]][path[0]] == 1) {
                return true;
            } else {
                return false;
            }
        }

        for (int v = 1; v < V; ++v) {
            if (isSafe(v, path, pos)) {
                path[pos] = v;
                if (hamiltonianCycleUtil(path, pos + 1)) {
                    return true;
                }
                path[pos] = -1;
            }
        }

        return false;
    }

public:
    Graph(int V) : V(V), adjMatrix(V, std::vector<int>(V, 0)) {}

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // for undirected graph
    }

    bool hamiltonianCycle() {
        std::vector<int> path(V, -1);
        path[0] = 0;
        if (!hamiltonianCycleUtil(path, 1)) {
            return false;
        }

        std::cout << "Hamiltonian Cycle:\n";
        for (int i = 0; i < V; ++i) {
            std::cout << path[i] << " ";
        }
        std::cout << path[0] << std::endl;

        return true;
    }
};

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    if (!g.hamiltonianCycle()) {
        std::cout << "No Hamiltonian Cycle exists" << std::endl;
    }

    return 0;
}

/* Visual Schema:

Hamiltonian Cycle:
0 1 2 4 3 0

*/
