// ﷽
// TopTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad


#include <iostream>
#include <vector>
#include <algorithm>

class TopTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;
    std::vector<int> sortedValues;

    // Builds a tree from a given interval of the sortedValues vector
    Node* buildTree(int start, int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        Node* node = new Node(sortedValues[mid]);
        node->left = buildTree(start, mid - 1);
        node->right = buildTree(mid + 1, end);
        return node;
    }

    // Performs a search in the binary tree
    bool search(Node* node, int val) {
        if (!node) return false;
        if (node->value == val) return true;
        if (val < node->value) return search(node->left, val);
        return search(node->right, val);
    }

public:
    TopTree(const std::vector<int>& values) {
        sortedValues = values;
        std::sort(sortedValues.begin(), sortedValues.end());
        root = buildTree(0, sortedValues.size() - 1);
    }

    // Search in the Top Tree
    bool search(int val) {
        return search(root, val);
    }
};

int main() {
    std::vector<int> values = {5, 2, 9, 1, 6};
    TopTree topTree(values);

    std::cout << "Search for the value 6 in the Top Tree: ";
    if (topTree.search(6)) {
        std::cout << "Found!" << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    return 0;
}

/*

            Top Tree
            
               5
              / \
             2   9
            /   /
            1   6


*/
