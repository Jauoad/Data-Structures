// ﷽
// Filename: HuffmanEncodingTree.cpp
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

// Struct to represent nodes in the Huffman tree
struct HuffmanNode {
    char data;              // Character stored in the node
    int frequency;          // Frequency of the character
    HuffmanNode* left;      // Pointer to the left child node
    HuffmanNode* right;     // Pointer to the right child node

    // Constructor
    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Struct for comparing Huffman nodes based on frequency
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

// Class representing the Huffman Tree
class HuffmanTree {
private:
    HuffmanNode* root;      // Pointer to the root of the Huffman tree

    // Recursive function to print Huffman codes
    void printCodes(HuffmanNode* root, std::string str) {
        if (!root) return;
        if (root->data != '$') {
            std::cout << root->data << ": " << str << std::endl;  // Print character and its code
        }
        printCodes(root->left, str + "0");  // Traverse left with code "0"
        printCodes(root->right, str + "1"); // Traverse right with code "1"
    }

public:
    // Constructor to build the Huffman Tree from input text
    HuffmanTree(const std::string& text) {
        // Create a map to store character frequencies
        std::unordered_map<char, int> freq;
        // Calculate frequencies of characters in the text
        for (char ch : text) {
            freq[ch]++;
        }

        // Priority queue to store Huffman nodes based on frequency
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;
        // Create Huffman nodes for each character and add them to the priority queue
        for (auto& pair : freq) {
            minHeap.push(new HuffmanNode(pair.first, pair.second));
        }

        // Build the Huffman Tree by merging nodes until only one node remains in the priority queue
        while (minHeap.size() != 1) {
            // Extract the two nodes with the lowest frequencies
            HuffmanNode* left = minHeap.top();
            minHeap.pop();
            HuffmanNode* right = minHeap.top();
            minHeap.pop();
            // Create a new internal node with combined frequency and add it to the priority queue
            HuffmanNode* top = new HuffmanNode('$', left->frequency + right->frequency);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }

        // The remaining node in the priority queue is the root of the Huffman Tree
        root = minHeap.top();
    }

    // Function to print Huffman codes
    void printCodes() {
        // Call the recursive function to print codes starting from the root
        printCodes(root, "");
    }
};

int main() {
    // Input text for Huffman encoding
    std::string text = "this is an example for huffman encoding";
    // Create a Huffman Tree with the input text
    HuffmanTree tree(text);

    // Print Huffman Codes
    std::cout << "Huffman Codes:" << std::endl;
    tree.printCodes();

    return 0;
}

/*

    Structure of the Huffman tree after construction:

        ($, 37)
       /       \
  (i, 7)       ($, 30)
             /         \
         (s, 5)       ($, 15)
                    /        \
               ( , 8)       ($, 7)
                           /       \
                       (h, 3)    (t, 4)

*/
