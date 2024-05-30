// ﷽
// KDTree.cpp
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

class KDTree {
private:
    struct Node {
        Point point;
        Node* left;
        Node* right;
        Node(Point p) : point(p), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    KDTree() : root(nullptr) {}

    // Insert a point into the tree
    void insert(Point p) {
        root = insert(root, p, 0);
    }

    // Recursive method to insert a point
    Node* insert(Node* node, Point p, int depth) {
        if (node == nullptr) {
            return new Node(p);
        }

        int cd = depth % 2;
        if (cd == 0) {
            if (p.x < node->point.x) {
                node->left = insert(node->left, p, depth + 1);
            } else {
                node->right = insert(node->right, p, depth + 1);
            }
        } else {
            if (p.y < node->point.y) {
                node->left = insert(node->left, p, depth + 1);
            } else {
                node->right = insert(node->right, p, depth + 1);
            }
        }
        return node;
    }
};

int main() {
    KDTree kdtree;
    kdtree.insert(Point(3, 6));
    kdtree.insert(Point(17, 15));
    kdtree.insert(Point(13, 15));
    kdtree.insert(Point(6, 12));
    kdtree.insert(Point(9, 1));
    kdtree.insert(Point(2, 7));
    return 0;
}

/* Visualization

                     (9,1)
                    /     \
               (3,6)       (13,15)
              /    \       /       \
         (2,7)     (6,12)          (17,15)


*/
