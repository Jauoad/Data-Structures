// ﷽
// IntervalTree.cpp
// Source :  https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an interval
struct Interval {
    int start;
    int end;
    
    Interval(int s, int e) : start(s), end(e) {}
};

class IntervalTree {
private:
    // Node structure of the tree
    struct Node {
        int max;
        Interval interval;
        Node* left;
        Node* right;
        
        Node(Interval i) : max(i.end), interval(i), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Recursive function to insert an interval into the tree
    Node* insert(Node* node, Interval interval) {
        if (node == nullptr) {
            return new Node(interval);
        }
        
        if (interval.start < node->interval.start) {
            node->left = insert(node->left, interval);
        } else {
            node->right = insert(node->right, interval);
        }
        
        node->max = max(node->max, interval.end);
        return node;
    }
    
    // Recursive function to check if an interval overlaps with any of the intervals in the tree
    bool overlapsWithAny(Node* node, Interval interval) {
        if (node == nullptr) {
            return false;
        }
        
        if (overlaps(node->interval, interval)) {
            return true;
        }
        
        if (node->left != nullptr && node->left->max >= interval.start) {
            return overlapsWithAny(node->left, interval);
        }
        
        return overlapsWithAny(node->right, interval);
    }

public:
    IntervalTree() : root(nullptr) {}
    
    // Public method to insert an interval into the tree
    void insert(Interval interval) {
        root = insert(root, interval);
    }
    
    // Public method to check if an interval overlaps with any interval in the tree
    bool hasOverlap(Interval interval) {
        return overlapsWithAny(root, interval);
    }

private:
    // Utility function to check if two intervals overlap
    bool overlaps(Interval a, Interval b) {
        return max(a.start, b.start) <= min(a.end, b.end);
    }
};

int main() {
    // Example of using the interval tree
    IntervalTree tree;
    tree.insert(Interval(15, 20));
    tree.insert(Interval(10, 30));
    tree.insert(Interval(17, 19));
    tree.insert(Interval(5, 20));
    tree.insert(Interval(12, 15));
    tree.insert(Interval(30, 40));

    // Checking overlaps with certain intervals
    cout << "Overlaps with (14, 16): " << boolalpha << tree.hasOverlap(Interval(14, 16)) << endl;
    cout << "Overlaps with (21, 25): " << boolalpha << tree.hasOverlap(Interval(21, 25)) << endl;
    
    return 0;
}

/*
   Visual Schema:
   
              [10, 30]
               /    \
          [5, 20]  [15, 20]
            / \     /
       [12, 15] [17, 19]
       
*/
