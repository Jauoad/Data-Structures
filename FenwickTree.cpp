// ﷽
// FenwickTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class FenwickTree {
private:
    std::vector<int> tree;

public:
    FenwickTree(int size) : tree(size + 1, 0) {}

    // Add a value at the given index
    void add(int index, int value) {
        while (index < tree.size()) {
            tree[index] += value;
            index += index & -index;
        }
    }

    // Get the sum of elements up to the given index
    int sum(int index) {
        int result = 0;
        while (index > 0) {
            result += tree[index];
            index -= index & -index;
        }
        return result;
    }
};

int main() {
    FenwickTree fenwick(8);
    fenwick.add(1, 5);
    fenwick.add(3, 2);
    fenwick.add(5, 7);
    std::cout << "Sum from index 1 to 5: " << fenwick.sum(5) - fenwick.sum(0) << std::endl; // Expected output: 14
    return 0;
}

/* Visual Representation:
// Bismillah visuelle

             1       2       3       4       5       6       7       8
        +-------+-------+-------+-------+-------+-------+-------+-------+
  Value |   5   |   0   |   2   |   0   |   7   |   0   |   0   |   0   |
        +-------+-------+-------+-------+-------+-------+-------+-------+

*/

