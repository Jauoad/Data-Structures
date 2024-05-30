// ﷽
// RedBlackTree.cpp
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <memory>

// Structure of a Red-Black tree node
struct Node {
    int data; // Value of the node
    bool isRed; // Indicates if the node is red or black
    std::shared_ptr<Node> left; // Pointer to the left subtree
    std::shared_ptr<Node> right; // Pointer to the right subtree
    std::shared_ptr<Node> parent; // Pointer to the parent

    // Constructor
    Node(int val) : data(val), isRed(true), left(nullptr), right(nullptr), parent(nullptr) {}
};

// Function to perform a left rotation
std::shared_ptr<Node> rotateLeft(std::shared_ptr<Node> root, std::shared_ptr<Node> x) {
    std::shared_ptr<Node> y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return root;
}

// Function to perform a right rotation
std::shared_ptr<Node> rotateRight(std::shared_ptr<Node> root, std::shared_ptr<Node> y) {
    std::shared_ptr<Node> x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nullptr) {
        root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return root;
}

// Function to restore Red-Black tree properties after insertion
std::shared_ptr<Node> fixInsert(std::shared_ptr<Node> root, std::shared_ptr<Node> z) {
    while (z != nullptr && z != root && z->parent->isRed) {
        if (z->parent == z->parent->parent->left) {
            std::shared_ptr<Node> y = z->parent->parent->right;
            if (y != nullptr && y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    root = rotateLeft(root, z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                root = rotateRight(root, z->parent->parent);
            }
        } else {
            std::shared_ptr<Node> y = z->parent->parent->left;
            if (y != nullptr && y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    root = rotateRight(root, z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                root = rotateLeft(root, z->parent->parent);
            }
        }
    }
    root->isRed = false;
    return root;
}

// Function to insert a node into the Red-Black tree
std::shared_ptr<Node> insert(std::shared_ptr<Node> root, int val) {
    std::shared_ptr<Node> z = std::make_shared<Node>(val);
    std::shared_ptr<Node> y = nullptr;
    std::shared_ptr<Node> x = root;
    while (x != nullptr) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    return fixInsert(root, z);
}

// Inorder traversal of the Red-Black tree (for verification)
void inorderTraversal(std::shared_ptr<Node> root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        std::cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

int main() {
    // Creating the Red-Black tree
    std::shared_ptr<Node> root = nullptr;

    // Inserting elements into the Red-Black tree
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    // Displaying the Red-Black tree (inorder traversal)
    std::cout << "Inorder Traversal of Red-Black Tree: ";
    inorderTraversal(root);
    std::cout << std::endl;

    return 0;
}

/* Visual Representation:
                    
             Red-Black Tree

                     20(B)
                   /       \
               10(R)       40(R)
                           /     \
                        30(B)   50(B)


            In this schema:

            (B) represents a black node.
            (R) represents a red node.
            Each node is followed by its children. Black and red nodes are alternated to ensure that every path from the root to a leaf contains the same number of black nodes.

*/


