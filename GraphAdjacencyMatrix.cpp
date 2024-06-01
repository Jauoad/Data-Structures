// ﷽
// GraphAdjacencyMatrix.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad


#include <iostream>
#include <vector>
#include <queue>
#include <stack>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adjMatrix;

public:
    Graph(int vertices) : V(vertices), adjMatrix(vertices, std::vector<int>(vertices, 0)) {}

    void addEdge(int src, int dest) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1;
    }

    void BFS(int startVertex) {
        std::vector<bool> visited(V, false);
        std::queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            std::cout << current << " ";

            for (int i = 0; i < V; ++i) {
                if (adjMatrix[current][i] && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }

    void DFSUtil(int vertex, std::vector<bool>& visited) {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (int i = 0; i < V; ++i) {
            if (adjMatrix[vertex][i] && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS(int startVertex) {
        std::vector<bool> visited(V, false);
        DFSUtil(startVertex, visited);
    }

    void shortestPath(int startVertex) {
        std::vector<int> distance(V, INT_MAX);
        distance[startVertex] = 0;

        std::queue<int> q;
        q.push(startVertex);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int i = 0; i < V; ++i) {
                if (adjMatrix[current][i] && distance[i] == INT_MAX) {
                    distance[i] = distance[current] + 1;
                    q.push(i);
                }
            }
        }

        std::cout << "Vertex   Distance from Source\n";
        for (int i = 0; i < V; ++i) {
            std::cout << i << "        " << distance[i] << std::endl;
        }
    }

    void findConnectedComponents() {
        std::vector<bool> visited(V, false);
        int componentCount = 0;

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                componentCount++;
                std::cout << "Connected component " << componentCount << ": ";
                DFSUtil(i, visited);
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(4, 6);
    g.addEdge(5, 6);

    std::cout << "BFS starting from vertex 0:" << std::endl;
    g.BFS(0);
    std::cout << std::endl;

    std::cout << "DFS starting from vertex 0:" << std::endl;
    g.DFS(0);
    std::cout << std::endl;

    std::cout << "Shortest paths from vertex 0:" << std::endl;
    g.shortestPath(0);
    std::cout << std::endl;

    std::cout << "Connected components in the graph:" << std::endl;
    g.findConnectedComponents();

    return 0;
}
