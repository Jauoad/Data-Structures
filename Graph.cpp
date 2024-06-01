// ﷽
// Graph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

class Graph {
private:
    int V; // Number of vertices
    std::vector<std::vector<int>> adj; // Adjacency list

public:
    // Constructor
    Graph(int V) : V(V), adj(V) {}

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add an edge from v to w
    }

    // Function to perform BFS traversal of the graph from a given vertex
    void BFS(int s) {
        std::vector<bool> visited(V, false); // Array to mark visited vertices
        std::queue<int> q; // Queue for BFS traversal

        visited[s] = true; // Mark the starting vertex as visited
        q.push(s); // Enqueue the starting vertex

        while (!q.empty()) {
            int u = q.front(); // Get the front vertex from the queue
            q.pop(); // Dequeue the front vertex

            std::cout << u << " "; // Print the current vertex

            // Traverse all adjacent vertices of the current vertex
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true; // Mark the adjacent vertex as visited
                    q.push(v); // Enqueue the adjacent vertex
                }
            }
        }
    }

    // Function to perform DFS traversal of the graph from a given vertex
    void DFS(int s) {
        std::vector<bool> visited(V, false); // Array to mark visited vertices
        std::stack<int> st; // Stack for DFS traversal

        visited[s] = true; // Mark the starting vertex as visited
        st.push(s); // Push the starting vertex onto the stack

        while (!st.empty()) {
            int u = st.top(); // Get the top vertex from the stack
            st.pop(); // Pop the top vertex from the stack

            std::cout << u << " "; // Print the current vertex

            // Traverse all adjacent vertices of the current vertex
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true; // Mark the adjacent vertex as visited
                    st.push(v); // Push the adjacent vertex onto the stack
                }
            }
        }
    }

    // Function to find the shortest path from a source vertex to all other vertices using BFS
    void shortestPath(int s) {
        std::vector<int> dist(V, -1); // Array to store the shortest distance from the source vertex
        std::queue<int> q; // Queue for BFS traversal

        dist[s] = 0; // Distance to the source vertex is 0
        q.push(s); // Enqueue the source vertex

        while (!q.empty()) {
            int u = q.front(); // Get the front vertex from the queue
            q.pop(); // Dequeue the front vertex

            // Traverse all adjacent vertices of the current vertex
            for (int v : adj[u]) {
                if (dist[v] == -1) { // If the distance is not yet calculated
                    dist[v] = dist[u] + 1; // Update the distance
                    q.push(v); // Enqueue the adjacent vertex
                }
            }
        }

        // Print the shortest distances
        std::cout << "Shortest distances from vertex " << s << ":" << std::endl;
        for (int i = 0; i < V; ++i) {
            std::cout << "Vertex " << i << ": " << dist[i] << std::endl;
        }
    }

    // Function to find the connected components in the graph using BFS
    void findConnectedComponents() {
        std::vector<bool> visited(V, false); // Array to mark visited vertices

        // Iterate through all vertices and perform BFS if not visited
        for (int v = 0; v < V; ++v) {
            if (!visited[v]) {
                std::cout << "Connected Component:";
                BFS(v);
                std::cout << std::endl;
            }
        }
    }
};

int main() {
    // Create a graph with 7 vertices
    Graph g(7);
    
    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
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

