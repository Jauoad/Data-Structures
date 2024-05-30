// ﷽
// MinimumSpanningTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<pair<int, pair<int, int>>> edges;

public:
    Graph(int V);
    void addEdge(int u, int v, int w);
    int kruskalMST();
    int findSet(int i, vector<int>& parent);
    void unionSets(int u, int v, vector<int>& parent, vector<int>& rank);
};

Graph::Graph(int V) {
    this->V = V;
}

void Graph::addEdge(int u, int v, int w) {
    edges.push_back({w, {u, v}});
}

int Graph::findSet(int i, vector<int>& parent) {
    if (i == parent[i]) {
        return i;
    } else {
        return parent[i] = findSet(parent[i], parent);
    }
}

void Graph::unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int Graph::kruskalMST() {
    int mstWeight = 0;
    sort(edges.begin(), edges.end());

    vector<int> parent(V);
    vector<int> rank(V, 0);
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    for (auto edge : edges) {
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;

        if (findSet(u, parent) != findSet(v, parent)) {
            mstWeight += w;
            unionSets(u, v, parent, rank);
        }
    }

    return mstWeight;
}

int main() {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    cout << "Weight of the minimum spanning tree is " << g.kruskalMST() << endl;

    return 0;
}

/*

Minimum spanning tree using Kruskal's algorithm:

       10
    0 -----> 1
    |       /
    6      /15
    |     /
    2 -----> 3
    |      /
    4     /5



*/
