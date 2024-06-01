// ﷽
// PersistentSegmentTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class Node {
public:
    int sum;
    Node* left;
    Node* right;

    Node(int sum) : sum(sum), left(nullptr), right(nullptr) {}
    Node(int sum, Node* left, Node* right) : sum(sum), left(left), right(right) {}
};

class PersistentSegmentTree {
private:
    std::vector<Node*> versions;
    int size;

    Node* buildTree(std::vector<int>& nums, int start, int end) {
        if (start == end) {
            return new Node(nums[start]);
        }
        int mid = start + (end - start) / 2;
        return new Node(0, buildTree(nums, start, mid), buildTree(nums, mid + 1, end));
    }

    Node* updateTree(Node* root, int start, int end, int index, int diff) {
        if (!root) return nullptr;
        if (index < start || index > end) return new Node(root->sum);
        if (start == end) {
            return new Node(root->sum + diff);
        }
        int mid = start + (end - start) / 2;
        return new Node(root->sum + diff, updateTree(root->left, start, mid, index, diff),
                        updateTree(root->right, mid + 1, end, index, diff));
    }

    int queryTree(Node* root, int start, int end, int left, int right) {
        if (!root || start > right || end < left) return 0;
        if (start >= left && end <= right) return root->sum;
        int mid = start + (end - start) / 2;
        return queryTree(root->left, start, mid, left, right) +
               queryTree(root->right, mid + 1, end, left, right);
    }

public:
    PersistentSegmentTree(std::vector<int>& nums) : size(nums.size()) {
        versions.push_back(buildTree(nums, 0, size - 1));
    }

    void update(int version, int index, int value) {
        versions.push_back(updateTree(versions[version], 0, size - 1, index, value));
    }

    int query(int version, int left, int right) {
        return queryTree(versions[version], 0, size - 1, left, right);
    }
};

int main() {
    std::vector<int> nums = {1, 3, 5, 7, 9};
    PersistentSegmentTree pst(nums);

    std::cout << "Original array:" << std::endl;
    for (int num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "Query 1 to 3 in version 0: " << pst.query(0, 1, 3) << std::endl;

    pst.update(0, 2, 6);
    std::cout << "Query 1 to 3 in version 1 after updating index 2 to 6: " << pst.query(1, 1, 3) << std::endl;

    return 0;
}

/*

Original array:
1 3 5 7 9

Query 1 to 3 in version 0: 15
Query 1 to 3 in version 1 after updating index 2 to 6: 16

        Tree Structure (Version 0):

                   [25]
                  /    \
               [9]      [16]
              /  \      /  \
            [4]  [5]  [7]  [9]

        Tree Structure (Version 1):

                   [25]
                  /    \
               [9]      [16]
              /  \      /  \
            [4]  [6]  [7]  [9]



*/