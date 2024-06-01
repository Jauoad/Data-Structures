// ﷽
// StringSearchTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <unordered_map>
#include <vector>

// Class representing a node in the String Search Tree
class StringSearchTreeNode {
public:
    std::unordered_map<char, StringSearchTreeNode*> children; // Children nodes
    bool isEndOfWord; // Flag to indicate the end of a word

    // Constructor
    StringSearchTreeNode() : isEndOfWord(false) {}

    // Destructor to clean up dynamically allocated memory
    ~StringSearchTreeNode() {
        for (auto& pair : children) {
            delete pair.second;
        }
    }
};

// Class representing the String Search Tree
class StringSearchTree {
private:
    StringSearchTreeNode* root; // Root node of the tree

    // Recursive function to insert a word into the tree
    void insert(StringSearchTreeNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            node->isEndOfWord = true;
            return;
        }

        char c = word[index];
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new StringSearchTreeNode();
        }
        insert(node->children[c], word, index + 1);
    }

    // Recursive function to search for a word in the tree
    bool search(StringSearchTreeNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            return node->isEndOfWord;
        }

        char c = word[index];
        if (node->children.find(c) == node->children.end()) {
            return false;
        }
        return search(node->children[c], word, index + 1);
    }

    // Recursive function to traverse the tree and print all words
    void traverse(StringSearchTreeNode* node, std::string& buffer) {
        if (node->isEndOfWord) {
            std::cout << buffer << std::endl;
        }

        for (auto& pair : node->children) {
            buffer.push_back(pair.first);
            traverse(pair.second, buffer);
            buffer.pop_back();
        }
    }

public:
    // Constructor
    StringSearchTree() : root(new StringSearchTreeNode()) {}

    // Destructor to delete the root node and clean up memory
    ~StringSearchTree() {
        delete root;
    }

    // Public method to insert a word into the tree
    void insert(const std::string& word) {
        insert(root, word, 0);
    }

    // Public method to search for a word in the tree
    bool search(const std::string& word) {
        return search(root, word, 0);
    }

    // Public method to traverse the tree and print all words
    void traverse() {
        std::string buffer;
        traverse(root, buffer);
    }
};

int main() {
    StringSearchTree sst;
    sst.insert("hello");
    sst.insert("world");
    sst.insert("hi");
    sst.insert("her");

    std::cout << "Traversal of String Search Tree:" << std::endl;
    sst.traverse();

    std::cout << "Search 'hello': " << (sst.search("hello") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'hero': " << (sst.search("hero") ? "Found" : "Not Found") << std::endl;

    return 0;
}

/*

Structure of the String Search Tree after inserting words:

         (root)
        /   |   \
      h     w     h
     /     /     / \
    e     o     i   e
   /     /         / \
  l     r         r   l
 /     /             /
l     l             o
|     |
o     d

*/
