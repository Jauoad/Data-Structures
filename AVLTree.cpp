// ﷽
// AVLTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <memory>
#include <algorithm>

// Structure of a node in AVL tree
struct Node {
    int data; // Value of the node
    int height; // Height of the node in the tree
    std::shared_ptr<Node> left; // Pointer to the left subtree
    std::shared_ptr<Node> right; // Pointer to the right subtree

    // Constructor
    Node(int val) : data(val), height(1), left(nullptr), right(nullptr) {}
};

// Function to get the height of a node
int height(std::shared_ptr<Node> node) {
    return (node ? node->height : 0);
}

// Function to calculate the balance factor of a node
int balanceFactor(std::shared_ptr<Node> node) {
    return (node ? height(node->left) - height(node->right) : 0);
}

// Function to update the height of a node
void updateHeight(std::shared_ptr<Node> node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
}

// Left rotation
std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Right rotation
std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> node) {
    std::shared_ptr<Node> newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// Insertion of a node into AVL tree
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, int val) {
    if (!root) {
        return std::make_shared<Node>(val);
    }

    if (val < root->data) {
        root->left = insert(root->left, val);
    } else if (val > root->data) {
        root->right = insert(root->right, val);
    } else {
        return root; // No insertion for duplicate elements
    }

    // Update the height of the current node
    updateHeight(root);

    // Check and balance the tree
    int balance = balanceFactor(root);

    // Left imbalance case
    if (balance > 1 && val < root->left->data) {
        return rotateRight(root);
    }

    // Right imbalance case
    if (balance < -1 && val > root->right->data) {
        return rotateLeft(root);
    }

    // Left-Right imbalance case
    if (balance > 1 && val > root->left->data) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right-Left imbalance case
    if (balance < -1 && val < root->right->data) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Inorder traversal of AVL tree (for verification)
void inorderTraversal(std::shared_ptr<Node> root) {
    if (root) {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

int main() {
    // Creating AVL tree
    std::shared_ptr<Node> root = nullptr;

    // Inserting elements into AVL tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    // Displaying AVL tree (inorder traversal)
    std::cout << "Inorder Traversal of AVL Tree: ";
    inorderTraversal(root);
    std::cout << std::endl;

    return 0;

    /* Visual Representation:
    

        AVL TREE

           30
          /  \
        20    40
       /  \     \
     10   25    50


    */
}

