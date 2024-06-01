// ﷽
// PlanarGraph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <list>
#include <vector>

class Graph {
private:
    int V;
    std::vector<std::list<int>> adjList;

public:
    Graph(int V) : V(V), adjList(V) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // for undirected graph
    }

    bool isCyclicUtil(int v, std::vector<bool>& visited, int parent) {
        visited[v] = true;

        for (auto i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i]) {
                if (isCyclicUtil(*i, visited, v)) {
                    return true;
                }
            } else if (*i != parent) {
                return true;
            }
        }
        return false;
    }

    bool isCyclic() {
        std::vector<bool> visited(V, false);
        for (int i = 0; i < V; ++i) {
            if (!visited[i] && isCyclicUtil(i, visited, -1)) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    // Non-Planar Graph
    Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 0);

    std::cout << "Example 1:" << std::endl;
    if (g1.isCyclic()) {
        std::cout << "Graph is not planar" << std::endl;
    } else {
        std::cout << "Graph is planar" << std::endl;
    }

    // Planar Graph
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);

    std::cout << "\nExample 2:" << std::endl;
    if (g2.isCyclic()) {
        std::cout << "Graph is not planar" << std::endl;
    } else {
        std::cout << "Graph is planar" << std::endl;
    }

    return 0;
}

/* 

    First graph: *

    Graph is not planar

    Visual Representation:

        0 ----- 1
       /       /
      /       /
     /       /
    3 ----- 2
    
        This graph contains a cycle (0 -> 1 -> 2 -> 3 -> 0), making it non-planar.
        Each vertex is represented by a number, and edges are depicted by lines connecting vertices.
        The graph is visualized with the vertices connected by edges forming a cycle.


    Second graph : **

    Graph is planar

    Visual Representation:

        0 ----- 1
                |
                |
                |
                3
        
        This graph is planar as it does not contain any cycles.
        Vertices are connected in a way that no cycles are formed.
        The visual representation shows vertices connected by edges forming a linear structure without any cycles.
*/
