// ﷽
// Octree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

// Structure to represent a three-dimensional point
struct Point {
    int x, y, z;
    Point(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

// Class to represent the Octree
class Octree {
private:
    // Structure of a node in the Octree
    struct Node {
        Point point; // Coordinates of the point representing the node
        std::vector<Node*> children; // Array of children nodes
        Node(Point p) : point(p), children(8, nullptr) {} // Constructor initializing children to nullptr
    };

    Node* root; // Root of the Octree

public:
    // Constructor initializing the root to nullptr
    Octree() : root(nullptr) {}

    // Method to insert a point into the Octree
    void insert(Point p) {
        root = insert(root, p, 0, 0, 0, 100); // Call the recursive insertion method
    }

    // Recursive method to insert a point into a node of the Octree
    Node* insert(Node* node, Point p, int x0, int y0, int z0, int length) {
        // If the node is null, create a new node with the given point
        if (node == nullptr) {
            node = new Node(p);
        } else {
            // Otherwise, determine the index of the child corresponding to the coordinates of the point
            int index = getIndex(p, x0, y0, z0, length);
            // If the corresponding child is null, create and insert it recursively
            if (node->children[index] == nullptr) {
                int newX0 = x0 + length * (index & 1);
                int newY0 = y0 + length * ((index >> 1) & 1);
                int newZ0 = z0 + length * ((index >> 2) & 1);
                node->children[index] = insert(nullptr, p, newX0, newY0, newZ0, length / 2);
            } else {
                // Otherwise, insert the point into the corresponding child
                insert(node->children[index], p, x0, y0, z0, length / 2);
            }
        }
        return node;
    }

    // Method to get the index of the child corresponding to the coordinates of the point
    int getIndex(Point p, int x0, int y0, int z0, int length) {
        int index = 0;
        if (p.x >= x0 + length) index |= 1;
        if (p.y >= y0 + length) index |= 2;
        if (p.z >= z0 + length) index |= 4;
        return index;
    }

    // Method to print the Octree
    void print() {
        if (root != nullptr) {
            print(root, 0); // Start printing from the root with depth 0
        } else {
            std::cout << "Octree is empty." << std::endl;
        }
    }

    // Recursive method to print the Octree starting from a specific node
    void print(Node* node, int depth) {
        // Print the coordinates of the point representing the node
        std::cout << "Depth " << depth << ": Point (" << node->point.x << ", " << node->point.y << ", " << node->point.z << ")" << std::endl;
        
        // Recursively print the children nodes
        for (int i = 0; i < 8; ++i) {
            if (node->children[i] != nullptr) {
                print(node->children[i], depth + 1);
            }
        }
    }
};

int main() {
    // Creation of the Octree
    Octree octree;

    // Insertion of some points into the Octree
    octree.insert(Point(10, 20, 30));
    octree.insert(Point(40, 50, 60));
    octree.insert(Point(70, 80, 90));

    // Print the Octree
    octree.print();

    return 0;
}


/* Visual Schema:

                                Root
                                 |
            +------------+-------+-------+--------------+
            |            |               |              |
         Child[0]     Child[1]       Child[2]       Child[3]
            |            |               |              |
         Depth 0       Depth 0        Depth 0         Depth 0
      (0, 0, 0)     (0, 0, 50)     (50, 0, 0)      (50, 0, 50)
          /|\            |               |              |
         / | \           |               |              |
   Depth 1| | Depth 1   |               |              |
   (0, 0, 0) | (0, 0, 100)               |              |
            |            +--------------+--------------+
            |            |              |              |
         Child[4]     Child[5]       Child[6]       Child[7]
            |            |              |              |
         Depth 0       Depth 0        Depth 0         Depth 0
      (0, 50, 0)    (0, 50, 50)    (50, 50, 0)     (50, 50, 50)

 

 Depth 0: Point (0, 0, 0)           (Root)
        / | \                      (Children)
Depth 1: Point (10, 20, 30)        (Child[0])
        / | \
Depth 2: Point (40, 50, 60)        (Child[1])
        / | \
Depth 3: Point (70, 80, 90)        (Child[2])


*/

