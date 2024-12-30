// ﷽
// Trie.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <unordered_map>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode();
    }

    // Method to insert a word into the Trie
    void insert(const std::string& word) {
        TrieNode* currentNode = root;
        for (char c : word) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                currentNode->children[c] = new TrieNode();
            }
            currentNode = currentNode->children[c];
        }
        currentNode->isEndOfWord = true;
    }

    // Method to search for a word in the Trie
    bool search(const std::string& word) {
        TrieNode* currentNode = root;
        for (char c : word) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                return false;
            }
            currentNode = currentNode->children[c];
        }
        return currentNode->isEndOfWord;
    }

    // Method to display the Trie tree (visually)
    void display(TrieNode* node, std::string word) {
        if (node == nullptr) return;

        if (node->isEndOfWord) {
            std::cout << word << std::endl;
        }

        for (auto& child : node->children) {
            display(child.second, word + child.first);
        }
    }

    void display() {
        display(root, "");
    }
};

int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("app");
    trie.insert("bat");
    trie.insert("ball");

    std::cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'bat': " << (trie.search("bat") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'ball': " << (trie.search("ball") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'banana': " << (trie.search("banana") ? "Found" : "Not Found") << std::endl;

    std::cout << "Words in Trie:" << std::endl;
    trie.display();

    return 0;
}

/*
Trie Structure

        root
         |
         a
         |
         p
         |
         p
        / \
       l   t
      /     \
     e       a
             |
             b
             |
             l
             |
             l

1. Insert "apple"
2. Insert "app"
3. Insert "bat"
4. Insert "ball"

*/
