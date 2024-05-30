// ﷽
// SplayTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <unordered_map>
#include <vector>

class SplayTreeNode {
public:
    int data;
    SplayTreeNode* left;
    SplayTreeNode* right;

    SplayTreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class SplayTree {
public:
    SplayTreeNode* root;

    SplayTree() : root(nullptr) {}

    // Helper function to perform rotation for Zig operation
    SplayTreeNode* rotateRight(SplayTreeNode* node) {
        SplayTreeNode* newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        return newRoot;
    }

    // Helper function to perform rotation for Zag operation
    SplayTreeNode* rotateLeft(SplayTreeNode* node) {
        SplayTreeNode* newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        return newRoot;
    }

    // Splay operation to move the given key to the root
    SplayTreeNode* splay(SplayTreeNode* root, int key) {
        if (root == nullptr || root->data == key)
            return root;

        if (root->data > key) {
            if (root->left == nullptr)
                return root;
            // Zig-Zig (left-left)
            if (root->left->data > key) {
                root->left->left = splay(root->left->left, key);
                root = rotateRight(root);
            }
            // Zig-Zag (left-right)
            else if (root->left->data < key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = rotateLeft(root->left);
            }
            // Zig (left)
            return (root->left == nullptr) ? root : rotateRight(root);
        } else {
            if (root->right == nullptr)
                return root;
            // Zag-Zag (right-right)
            if (root->right->data < key) {
                root->right->right = splay(root->right->right, key);
                root = rotateLeft(root);
            }
            // Zag-Zig (right-left)
            else if (root->right->data > key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rotateRight(root->right);
            }
            // Zag (right)
            return (root->right == nullptr) ? root : rotateLeft(root);
        }
    }

    // Function to insert a key into the tree
    void insert(int key) {
        root = insertUtil(root, key);
    }

    // Recursive utility function to insert a key into the tree
    SplayTreeNode* insertUtil(SplayTreeNode* root, int key) {
        // If the tree is empty, create a new node
        if (root == nullptr)
            return new SplayTreeNode(key);

        // Splay the node to the root if it is already present
        root = splay(root, key);

        // If key is already present, return root
        if (root->data == key)
            return root;

        // Create a new node
        SplayTreeNode* newNode = new SplayTreeNode(key);

        // If key is smaller than root's key, make the new node as root
        // of the left subtree
        if (root->data > key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        }
        // If key is greater than root's key, make the new node as root
        // of the right subtree
        else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }

        // Return the new root
        return newNode;
    }

    // Function to print the tree
    void printTree(SplayTreeNode* root, std::string indent = "", bool last = true) {
        if (root != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "   ";
            } else {
                std::cout << "L----";
                indent += "|  ";
            }
            std::cout << root->data << std::endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }
};

int main() {
    SplayTree splayTree;
    splayTree.insert(10);
    splayTree.insert(5);
    splayTree.insert(15);
    splayTree.insert(3);
    splayTree.insert(8);
    splayTree.insert(12);
    splayTree.insert(18);
    splayTree.insert(1);
    splayTree.insert(9);
    splayTree.insert(20);

    // Print the tree
    splayTree.printTree(splayTree.root);

    // Display visualization
    /* 

         10
        /  \
       5    15
      / \   / \
     3   8 12  18
    /     \     \
   1       9     20

   */

    return 0;
}
