// ﷽
// BipartiteGraph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <unordered_map>


// Function to convert color name to corresponding string
std::string colorToString(char color) {
    std::unordered_map<char, std::string> colorMap = {{'R', "Red"}, {'B', "Blue"}, {'G', "Green"}};
    return colorMap[color];
}

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

    bool isBipartiteUtil(int src, std::vector<char>& color) {
        std::queue<int> q;
        q.push(src);
        color[src] = 'R'; // Start with Red color for the source vertex

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto i = adjList[u].begin(); i != adjList[u].end(); ++i) {
                if (*i == u) return false; // Self-loop found

                if (color[*i] == ' ') { // If the vertex is not colored
                    color[*i] = (color[u] == 'R') ? 'B' : 'R'; // Assign the opposite color to the neighbor
                    q.push(*i);
                } else if (color[*i] == color[u]) { // If the neighbor has the same color
                    return false;
                }
            }
        }
        return true;
    }

    bool isBipartite() {
        std::vector<char> color(V, ' '); // Initialize all vertices with no color
        for (int i = 0; i < V; ++i) {
            if (color[i] == ' ') {
                if (!isBipartiteUtil(i, color)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    // Graph 1
    Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 3);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);

    std::cout << "Graph 1 *:" << std::endl;
    if (g1.isBipartite()) {
        std::cout << "Graph is Bipartite" << std::endl;
    } else {
        std::cout << "Graph is not Bipartite" << std::endl;
    }

    /*

     Nodes are labeled with colors in parentheses: Red (R), Blue (B), and Green (G)

    Graph is Bipartite

    0(R) --- 1(B)
     |         |
     |         |
    3(R) --- 2(B)
    */

    // Graph 2
    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 3);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);

    std::cout << "\nGraph 2 **:" << std::endl;
    if (g2.isBipartite()) {
        std::cout << "Graph is Bipartite" << std::endl;
    } else {
        std::cout << "Graph is not Bipartite" << std::endl;
    }

    /*

    Graph is Bipartite

       0(R) --- 1(B)
      /  |      |
    (G) (G)     |
      \   |     |
       2(B) --- 4(R)
    */

    // Graph 3
    Graph g3(5);
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(0, 3);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(2, 4);
    g3.addEdge(3, 4);

    std::cout << "\nGraph 3 ***:" << std::endl;
    if (g3.isBipartite()) {
        std::cout << "Graph is Bipartite" << std::endl;
    } else {
        std::cout << "Graph is not Bipartite" << std::endl;
    }

    /* 
       

    Graph is not Bipartite

       0(R) --- 1(B)
      /  |      |
    (G) (G)     |
      \   |     |
       2(B) --- 4(R)
           \   /
            3(R)
    */

    return 0;
}
