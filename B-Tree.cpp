// ﷽
// B-Tree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class BTreeNode {
public:
    std::vector<int> keys;
    std::vector<BTreeNode*> children;
    bool isLeaf;

    BTreeNode(bool isLeaf) : isLeaf(isLeaf) {}

    void traverse() {
        for (size_t i = 0; i < keys.size(); ++i) {
            if (!isLeaf) {
                children[i]->traverse();
            }
            std::cout << " " << keys[i];
        }
        if (!isLeaf) {
            children[keys.size()]->traverse();
        }
    }
};

class BTree {
private:
    BTreeNode* root;
    int t;  // Minimum degree

    void insertNonFull(BTreeNode* node, int k) {
        int i = node->keys.size() - 1;

        if (node->isLeaf) {
            node->keys.resize(node->keys.size() + 1);
            while (i >= 0 && node->keys[i] > k) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = k;
        } else {
            while (i >= 0 && node->keys[i] > k) {
                i--;
            }
            if (node->children[i + 1]->keys.size() == 2 * t - 1) {
                splitChild(node, i + 1, node->children[i + 1]);
                if (node->keys[i + 1] < k) {
                    i++;
                }
            }
            insertNonFull(node->children[i + 1], k);
        }
    }

    void splitChild(BTreeNode* parent, int i, BTreeNode* fullChild) {
        BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);
        newChild->keys.resize(t - 1);

        for (int j = 0; j < t - 1; j++) {
            newChild->keys[j] = fullChild->keys[j + t];
        }

        if (!fullChild->isLeaf) {
            newChild->children.resize(t);
            for (int j = 0; j < t; j++) {
                newChild->children[j] = fullChild->children[j + t];
            }
        }

        fullChild->keys.resize(t - 1);
        parent->children.resize(parent->children.size() + 1);
        for (int j = parent->children.size() - 1; j > i + 1; j--) {
            parent->children[j] = parent->children[j - 1];
        }
        parent->children[i + 1] = newChild;

        parent->keys.resize(parent->keys.size() + 1);
        for (int j = parent->keys.size() - 1; j > i; j--) {
            parent->keys[j] = parent->keys[j - 1];
        }
        parent->keys[i] = fullChild->keys[t - 1];
    }

public:
    BTree(int t) : root(nullptr), t(t) {}

    void insert(int k) {
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->keys.push_back(k);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode* newRoot = new BTreeNode(false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0, root);
                int i = 0;
                if (newRoot->keys[0] < k) {
                    i++;
                }
                insertNonFull(newRoot->children[i], k);
                root = newRoot;
            } else {
                insertNonFull(root, k);
            }
        }
    }

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }
};

int main() {
    BTree t(3);
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    std::cout << "Traversal of B-Tree: ";
    t.traverse();
    std::cout << std::endl;

    return 0;
}

/*

Structure of the B-Tree after inserting the keys:

       [10, 20]
      /    |    \
  [5, 6, 7] [12, 17] [30]

*/
