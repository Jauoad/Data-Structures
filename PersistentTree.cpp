// ﷽
// PersistentTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class PersistentTreeNode {
public:
    int data;
    PersistentTreeNode* left;
    PersistentTreeNode* right;

    PersistentTreeNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

class PersistentTree {
private:
    std::vector<PersistentTreeNode*> versions;

    PersistentTreeNode* insert(PersistentTreeNode* root, int data) {
        if (!root) return new PersistentTreeNode(data);

        PersistentTreeNode* newNode = new PersistentTreeNode(root->data);
        if (data < root->data) {
            newNode->left = insert(root->left, data);
            newNode->right = root->right;
        } else {
            newNode->right = insert(root->right, data);
            newNode->left = root->left;
        }
        return newNode;
    }

public:
    PersistentTree() {}

    void insert(int data) {
        if (versions.empty()) {
            versions.push_back(new PersistentTreeNode(data));
        } else {
            versions.push_back(insert(versions.back(), data));
        }
    }

    void inOrder(PersistentTreeNode* root) {
        if (root) {
            inOrder(root->left);
            std::cout << root->data << " ";
            inOrder(root->right);
        }
    }

    void printVersion(int version) {
        if (version < versions.size()) {
            inOrder(versions[version]);
            std::cout << std::endl;
        } else {
            std::cout << "Invalid version!" << std::endl;
        }
    }
};

int main() {
    PersistentTree tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    std::cout << "In-order traversal of version 0: ";
    tree.printVersion(0);

    std::cout << "In-order traversal of version 1: ";
    tree.printVersion(1);

    std::cout << "In-order traversal of version 2: ";
    tree.printVersion(2);

    std::cout << "In-order traversal of version 3: ";
    tree.printVersion(3);

    return 0;
}

/*
    
    Persistant tree after each insertion:

        Version 0:
            10

        Version 1:
            10
              \
               20

        Version 2:
              10
             /  \
            5    20

        Version 3:
              10
             /  \
            5    20
                 /
                15

*/
