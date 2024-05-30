// ﷽
// SegmentTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <cmath>

class SegmentTree {
private:
    std::vector<int> tree;
    int n;

    // Method to recursively build the segment tree
    void buildTree(const std::vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
            return;
        }
        int mid = start + (end - start) / 2;
        buildTree(nums, 2 * node + 1, start, mid);
        buildTree(nums, 2 * node + 2, mid + 1, end);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

public:
    // Constructor taking an array of integers as input
    SegmentTree(const std::vector<int>& nums) {
        n = nums.size();
        int height = (int)(ceil(log2(n))); // Height of the tree
        int maxSize = 2 * (int)pow(2, height) - 1; // Maximum size of the tree
        tree.resize(maxSize);
        buildTree(nums, 0, 0, n - 1); // Building the segment tree
    }

    // Method to perform a query on a given interval
    int query(int node, int start, int end, int left, int right) {
        if (left > end || right < start) return 0; // Query interval is outside of current interval
        if (left <= start && right >= end) return tree[node]; // Current interval is completely within query interval
        int mid = start + (end - start) / 2;
        return query(2 * node + 1, start, mid, left, right) + query(2 * node + 2, mid + 1, end, left, right);
    }

    // Method to perform a query on a given interval (user interface)
    int rangeSum(int left, int right) {
        return query(0, 0, n - 1, left, right);
    }
};

int main() {
    std::vector<int> nums = {1, 3, 5, 7, 9, 11};

    // Creating segment tree from the array of integers
    SegmentTree st(nums);

    // Query to compute the sum of elements in the interval [1, 4]
    int sum = st.rangeSum(1, 4);
    std::cout << "Sum of elements in the interval [1, 4]: " << sum << std::endl;

    return 0;

    /*
    Visual Representation:

    Input Array: [1, 3, 5, 7, 9, 11]

    Segment Tree:

                  [36]
                 /    \
              [9]      [27]
              / \      /   \
           [4]  [5]  [16]  [11]
           / \  / \  / \   / \
          1   3 5  7 9  0 0  11

          In this step, we build the segment tree from the input array [1, 3, 5, 7, 9, 11].

          Step 2: Query to compute the sum of elements in the interval [1, 4]

                Query Interval: [1, 4]

                Sum of elements in the interval [1, 4]: 24

         In this step, we perform a query to compute the sum of elements in the interval [1, 4] from the segment tree built previously. The sum of elements in this interval is equal to 24.
    */
}

