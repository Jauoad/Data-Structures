// ﷽
// HybridTrie.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <unordered_map>

class HybridTrieNode {
public:
    char data;
    bool isEnd;
    std::unordered_map<char, HybridTrieNode*> children;

    HybridTrieNode(char c) : data(c), isEnd(false) {}
};

class HybridTrie {
private:
    HybridTrieNode* root;

public:
    HybridTrie() : root(new HybridTrieNode('\0')) {}

    void insert(const std::string& word) {
        HybridTrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = new HybridTrieNode(c);
            }
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    bool search(const std::string& word) {
        HybridTrieNode* curr = root;
        for (char c : word) {
            if (curr->children.find(c) == curr->children.end()) {
                return false;
            }
            curr = curr->children[c];
        }
        return curr->isEnd;
    }
};

int main() {
    HybridTrie trie;
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("orange");

    std::cout << "Search 'apple': " << (trie.search("apple") ? "Found" : "Not found") << std::endl;
    std::cout << "Search 'grape': " << (trie.search("grape") ? "Found" : "Not found") << std::endl;

    return 0;
}

/* Visual Schema

              Hybrid Trie

                (root)
                 / | \
                a  b  o
                |  |  |
                p  a  r
                |  |  |  
                p  n  a
                |     |  
                l     g

*/
