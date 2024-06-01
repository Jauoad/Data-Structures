// ﷽
// EulerianGraph.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adjMatrix;

public:
    Graph(int V) : V(V), adjMatrix(V, std::vector<int>(V, 0)) {}

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1; // for undirected graph
    }

    int degree(int v) {
        int deg = 0;
        for (int i = 0; i < V; ++i) {
            deg += adjMatrix[v][i];
        }
        return deg;
    }

    bool isEulerian() {
        for (int i = 0; i < V; ++i) {
            if (degree(i) % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool isSemiEulerian() {
        int oddDegreeCount = 0;
        for (int i = 0; i < V; ++i) {
            if (degree(i) % 2 != 0) {
                oddDegreeCount++;
            }
        }
        return oddDegreeCount == 2;
    }
};

int main() {
    // Example 1: Eulerian Graph
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(4, 0);

    /*
        
                0 ----- 1
               /       /
              /       /
             /       /
            4 ----- 3

    */

    std::cout << "Example 1:" << std::endl;
    if (g1.isEulerian()) {
        std::cout << "Graph is Eulerian" << std::endl;
    } else {
        std::cout << "Graph is not Eulerian" << std::endl;
    }

    // Example 2: Semi-Eulerian Graph
    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 0);
    g2.addEdge(1, 3);

     /*
        
                    0 ----- 1
                   /       / \
                  /       /   \
                 /       /     \
                4 ----- 3       2
    */

    std::cout << "\nExample 2:" << std::endl;
    if (g2.isSemiEulerian()) {
        std::cout << "Graph is Semi-Eulerian" << std::endl;
    } else {
        std::cout << "Graph is not Semi-Eulerian" << std::endl;
    }

    // Example 3: Non-Eulerian Graph
    Graph g3(5);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 3);
    g3.addEdge(3, 4);
    g3.addEdge(4, 0);
    g3.addEdge(1, 3);
    g3.addEdge(2, 4);

    /*


            0 ----- 1
           /       / \
          /       /   \
         /       /     \
        4 ----- 3 ----- 2


    */

    std::cout << "\nExample 3:" << std::endl;
    if (g3.isEulerian()) {
        std::cout << "Graph is Eulerian" << std::endl;
    } else {
        std::cout << "Graph is not Eulerian" << std::endl;
    }

    return 0;
}


/* Visual Schema:


                Eulerian Graph

                    0 ----- 1
                   /       /
                  /       /
                 /       /
                4 ----- 3

                
                Semi-Eulerian Graph

                    0 ----- 1
                   /       / \
                  /       /   \
                 /       /     \
                4 ----- 3       2

                
                Non-Eulerian Graph

                    0 ----- 1
                   /       / \
                  /       /   \
                 /       /     \
                4 ----- 3 ----- 2


*/
