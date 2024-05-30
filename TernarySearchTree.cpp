// ﷽
// TernarySearchTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>

class TrieNode {
public:
    char data;
    bool isEndOfWord;
    TrieNode* left;
    TrieNode* middle;
    TrieNode* right;

    TrieNode(char data) : data(data), isEndOfWord(false), left(nullptr), middle(nullptr), right(nullptr) {}
};

class TernarySearchTree {
private:
    TrieNode* root;

    TrieNode* insert(TrieNode* node, const std::string& word, int index) {
        if (node == nullptr) {
            node = new TrieNode(word[index]);
        }

        if (word[index] < node->data) {
            node->left = insert(node->left, word, index);
        } else if (word[index] > node->data) {
            node->right = insert(node->right, word, index);
        } else {
            if (index + 1 < word.length()) {
                node->middle = insert(node->middle, word, index + 1);
            } else {
                node->isEndOfWord = true;
            }
        }
        return node;
    }

    bool search(TrieNode* node, const std::string& word, int index) {
        if (node == nullptr) {
            return false;
        }

        if (word[index] < node->data) {
            return search(node->left, word, index);
        } else if (word[index] > node->data) {
            return search(node->right, word, index);
        } else {
            if (index + 1 == word.length()) {
                return node->isEndOfWord;
            }
            return search(node->middle, word, index + 1);
        }
    }

public:
    TernarySearchTree() : root(nullptr) {}

    void insert(const std::string& word) {
        root = insert(root, word, 0);
    }

    bool search(const std::string& word) {
        return search(root, word, 0);
    }
};

int main() {
    TernarySearchTree tst;
    tst.insert("apple");
    tst.insert("banana");
    tst.insert("cherry");

    std::cout << "Search for 'apple': " << (tst.search("apple") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search for 'grape': " << (tst.search("grape") ? "Found" : "Not Found") << std::endl;

    return 0;
}

/*

Trie representing the words: "apple", "banana", "cherry"

     a
    /|\
   / | \
  b  p  c
   \ |   \
    a p   h
     \|   |
      n l e
       | |
       a e
       | |
       n r
         |
         y


*/