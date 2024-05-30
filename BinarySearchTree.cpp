// ﷽
// BinarySearchTree.cpp
// Source: https://github.com/Jauoad
// © 2024 Jauoad

#include <iostream>
#include <memory>

// Structure of a node in the Binary Search Tree (BST)
struct Node {
    int data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    // Constructor
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Class representing the Binary Search Tree (BST)
class BinarySearchTree {
private:
    std::shared_ptr<Node> root;

    // Method to insert an element into the BST
    std::shared_ptr<Node> insert(std::shared_ptr<Node> node, int val) {
        if (!node) {
            return std::make_shared<Node>(val);
        }

        if (val < node->data) {
            node->left = insert(node->left, val);
        } else {
            node->right = insert(node->right, val);
        }

        return node;
    }

    // Method to print the BST (inorder traversal)
    void printTree(std::shared_ptr<Node> node) const {
        if (!node) return;
        printTree(node->left);
        std::cout << node->data << " ";
        printTree(node->right);
    }

public:
    // Constructor
    BinarySearchTree() : root(nullptr) {}

    // Method to insert an element into the BST (user interface)
    void insert(int val) {
        root = insert(root, val);
    }

    // Method to print the BST (user interface)
    void print() const {
        printTree(root);
        std::cout << std::endl;
    }
};

int main() {
    // Create the Binary Search Tree (BST)
    BinarySearchTree bst;

    // Insert elements into the BST
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    // Print the BST
    std::cout << "Binary Search Tree (BST): ";
    bst.print();

    return 0;
}
/*

    Binary Search Tree (BST):
          5
        /   \
       3     7
      / \   / \
     2   4 6   8


*/
