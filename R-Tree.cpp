// ﷽
// R-Tree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Rectangle {
    int x_min, y_min, x_max, y_max;

    bool contains(const Rectangle& other) const {
        return x_min <= other.x_min && x_max >= other.x_max &&
               y_min <= other.y_min && y_max >= other.y_max;
    }
};

class RTreeNode {
public:
    std::vector<Rectangle> entries;
    std::vector<RTreeNode*> children;
    bool isLeaf;

    RTreeNode(bool isLeaf) : isLeaf(isLeaf) {}

    ~RTreeNode() {
        for (auto child : children) {
            delete child;
        }
    }
};

class RTree {
private:
    RTreeNode* root;
    int maxEntries;

    void insertNonFull(RTreeNode* node, const Rectangle& r) {
        if (node->isLeaf) {
            node->entries.push_back(r);
        } else {
            int bestChild = chooseSubtree(node, r);
            insertNonFull(node->children[bestChild], r);
            adjustBounds(node, bestChild);
        }
    }

    int chooseSubtree(RTreeNode* node, const Rectangle& r) {
        int bestChild = 0;
        int minEnlargement = std::numeric_limits<int>::max();
        for (size_t i = 0; i < node->children.size(); ++i) {
            int enlargement = computeEnlargement(node->entries[i], r);
            if (enlargement < minEnlargement) {
                minEnlargement = enlargement;
                bestChild = i;
            }
        }
        return bestChild;
    }

    int computeEnlargement(const Rectangle& original, const Rectangle& r) {
        int enlargedArea = (std::max(original.x_max, r.x_max) - std::min(original.x_min, r.x_min)) *
                           (std::max(original.y_max, r.y_max) - std::min(original.y_min, r.y_min));
        int originalArea = (original.x_max - original.x_min) * (original.y_max - original.y_min);
        return enlargedArea - originalArea;
    }

    void adjustBounds(RTreeNode* node, int childIndex) {
        Rectangle& childBounds = node->entries[childIndex];
        RTreeNode* childNode = node->children[childIndex];

        for (const auto& entry : childNode->entries) {
            if (!childBounds.contains(entry)) {
                childBounds.x_min = std::min(childBounds.x_min, entry.x_min);
                childBounds.y_min = std::min(childBounds.y_min, entry.y_min);
                childBounds.x_max = std::max(childBounds.x_max, entry.x_max);
                childBounds.y_max = std::max(childBounds.y_max, entry.y_max);
            }
        }
    }

public:
    RTree(int maxEntries) : root(new RTreeNode(true)), maxEntries(maxEntries) {}

    ~RTree() {
        delete root;
    }

    void insert(const Rectangle& r) {
        insertNonFull(root, r);
        if (root->entries.size() > maxEntries) {
            RTreeNode* newRoot = new RTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
    }

    void splitChild(RTreeNode* parent, int i, RTreeNode* fullChild) {
        RTreeNode* newChild = new RTreeNode(fullChild->isLeaf);
        int mid = fullChild->entries.size() / 2;

        newChild->entries.assign(fullChild->entries.begin() + mid, fullChild->entries.end());
        fullChild->entries.erase(fullChild->entries.begin() + mid, fullChild->entries.end());

        if (!fullChild->isLeaf) {
            newChild->children.assign(fullChild->children.begin() + mid, fullChild->children.end());
            fullChild->children.erase(fullChild->children.begin() + mid, fullChild->children.end());
        }

        parent->entries.insert(parent->entries.begin() + i, newChild->entries[0]);
        parent->children.insert(parent->children.begin() + i + 1, newChild);
    }

    void traverse() const {
        traverse(root, 0);
    }

    void traverse(RTreeNode* node, int level) const {
        std::cout << "Level " << level << ": ";
        for (const auto& entry : node->entries) {
            std::cout << "[" << entry.x_min << "," << entry.y_min << "," << entry.x_max << "," << entry.y_max << "] ";
        }
        std::cout << std::endl;

        if (!node->isLeaf) {
            for (auto child : node->children) {
                traverse(child, level + 1);
            }
        }
    }
};

int main() {
    RTree tree(3);

    tree.insert({0, 0, 2, 2});
    tree.insert({1, 1, 3, 3});
    tree.insert({2, 2, 4, 4});
    tree.insert({3, 3, 5, 5});
    tree.insert({4, 4, 6, 6});

    std::cout << "Traversal of R-Tree:" << std::endl;
    tree.traverse();

    return 0;
}

/*

Structure of the R-Tree after inserting rectangles:

Level 0: [0,0,6,6]
Level 1: [0,0,2,2] [1,1,3,3] [2,2,4,4] [3,3,5,5] [4,4,6,6]

*/
