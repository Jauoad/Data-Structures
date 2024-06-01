// ﷽
// NetworkFlowGraph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> capacity;
    vector<vector<int>> adj;

public:
    Graph(int V);
    void addEdge(int u, int v, int cap);
    int bfs(int s, int t, vector<int>& parent);
    int fordFulkerson(int s, int t);
};

Graph::Graph(int V) {
    this->V = V;
    capacity.resize(V, vector<int>(V, 0));
    adj.resize(V);
}

void Graph::addEdge(int u, int v, int cap) {
    capacity[u][v] = cap;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

int Graph::bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INT_MAX});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) {
                    return new_flow;
                }
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int Graph::fordFulkerson(int s, int t) {
    int flow = 0;
    vector<int> parent(V);
    int new_flow;

    while ((new_flow = bfs(s, t, parent)) != 0) {
        flow += new_flow;
        int cur = t;

        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int main() {
    Graph g(6);
    g.addEdge(0, 1, 16);
    g.addEdge(0, 2, 13);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 12);
    g.addEdge(2, 1, 4);
    g.addEdge(2, 4, 14);
    g.addEdge(3, 2, 9);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 3, 7);
    g.addEdge(4, 5, 4);

    cout << "Maximum flow: " << g.fordFulkerson(0, 5) << endl;

    return 0;
}

/*
            Network flow graph:

              (16)        (12)
          0 ------> 1 ----------> 3
          | \       |             /|
          |  \      |            / |
        (13) (10)  (4)          /  | (20)
          |    \    |          /   |
          |     \   |         /    |
          2 <-----> 4 <-----> 5
              (14)        (7)     (4)
*/
