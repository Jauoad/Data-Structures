// ﷽
// DAG.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <list>
#include <stack>
#include <vector>

class Graph {
private:
    int V;
    std::vector<std::list<int>> adjList;

    void topologicalSortUtil(int v, std::vector<bool>& visited, std::stack<int>& Stack) {
        visited[v] = true;

        for (auto i = adjList[v].begin(); i != adjList[v].end(); ++i) {
            if (!visited[*i]) {
                topologicalSortUtil(*i, visited, Stack);
            }
        }

        Stack.push(v);
    }

public:
    Graph(int V) : V(V), adjList(V) {}

    void addEdge(int v, int w) {
        adjList[v].push_back(w);
    }

    void topologicalSort() {
        std::stack<int> Stack;
        std::vector<bool> visited(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                topologicalSortUtil(i, visited, Stack);
            }
        }

        while (!Stack.empty()) {
            std::cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};

int main() {
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    std::cout << "Topological sort of the given DAG:\n";
    g.topologicalSort();

    return 0;
}

/*

Topological sort of the given DAG:
    5 4 2 3 1 0

*/