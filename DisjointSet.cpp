// ﷽
// DisjointSet.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class DisjointSet {
private:
    std::vector<int> parent, rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find the root of the set of element x
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    // Union of two sets
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    // Print the sets
    void printSets(int n) {
        for (int i = 0; i < n; ++i) {
            std::cout << "Element: " << i << " -> Set: " << find(i) << std::endl;
        }
    }
};

int main() {
    DisjointSet ds(5);
    ds.unionSets(0, 2);
    ds.unionSets(4, 2);
    ds.unionSets(3, 1);
    ds.printSets(5);
    return 0;
}

/* Visual Schema:

Initial:
0   1   2   3   4
|   |   |   |   |
0   1   2   3   4

After union(0, 2):
0   1   2   3   4
|       |   |   |
0       0   3   4

After union(4, 2):
0   1   2   3   4
|       |   |   |
0       0   3   0

After union(3, 1):
0   1   2   3   4
|   |   |       |
0   1   0       0


*/
