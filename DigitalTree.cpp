// ﷽
// DigitalTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>

class DigitalTreeNode {
public:
    bool isEndOfWord;
    std::vector<DigitalTreeNode*> children;

    DigitalTreeNode() : isEndOfWord(false), children(10, nullptr) {}
};

class DigitalTree {
private:
    DigitalTreeNode* root;

    void insert(DigitalTreeNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            node->isEndOfWord = true;
            return;
        }

        int digit = word[index] - '0';
        if (node->children[digit] == nullptr) {
            node->children[digit] = new DigitalTreeNode();
        }
        insert(node->children[digit], word, index + 1);
    }

    bool search(DigitalTreeNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            return node->isEndOfWord;
        }

        int digit = word[index] - '0';
        if (node->children[digit] == nullptr) {
            return false;
        }
        return search(node->children[digit], word, index + 1);
    }

    void traverse(DigitalTreeNode* node, std::string& word) {
        if (node->isEndOfWord) {
            std::cout << word << std::endl;
        }

        for (int i = 0; i < 10; ++i) {
            if (node->children[i] != nullptr) {
                word.push_back('0' + i);
                traverse(node->children[i], word);
                word.pop_back();
            }
        }
    }

public:
    DigitalTree() : root(new DigitalTreeNode()) {}

    void insert(const std::string& word) {
        insert(root, word, 0);
    }

    bool search(const std::string& word) {
        return search(root, word, 0);
    }

    void traverse() {
        std::string word;
        traverse(root, word);
    }
};

int main() {
    DigitalTree tree;
    tree.insert("123");
    tree.insert("456");
    tree.insert("789");
    tree.insert("12");
    tree.insert("4567");

    std::cout << "Traversal of Digital Tree:" << std::endl;
    tree.traverse();

    std::cout << "Search '123': " << (tree.search("123") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search '45': " << (tree.search("45") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search '4567': " << (tree.search("4567") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search '7890': " << (tree.search("7890") ? "Found" : "Not Found") << std::endl;

    return 0;
}

/* Visual Schema:

Structure of the Digital / Prefix tree after inserting numbers:

        root
        / | \
       1  4  7
      /   |   \
     2    5    8
    / \    \    \
   3   .    6    9
        .    \
         .    7

*/
