// ﷽
// RadixTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <unordered_map>
#include <string>

class RadixTreeNode {
public:
    std::unordered_map<char, RadixTreeNode*> children;
    bool isEndOfWord;

    RadixTreeNode() : isEndOfWord(false) {}
};

class RadixTree {
private:
    RadixTreeNode* root;

    void insert(RadixTreeNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            node->isEndOfWord = true;
            return;
        }

        char c = word[index];
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new RadixTreeNode();
        }
        insert(node->children[c], word, index + 1);
    }

    bool search(RadixTreeNode* node, const std::string& word, int index) {
        if (index == word.length()) {
            return node->isEndOfWord;
        }

        char c = word[index];
        if (node->children.find(c) == node->children.end()) {
            return false;
        }
        return search(node->children[c], word, index + 1);
    }

    void traverse(RadixTreeNode* node, std::string& word) {
        if (node->isEndOfWord) {
            std::cout << word << std::endl;
        }

        for (auto& child : node->children) {
            word.push_back(child.first);
            traverse(child.second, word);
            word.pop_back();
        }
    }

public:
    RadixTree() : root(new RadixTreeNode()) {}

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
    RadixTree tree;
    tree.insert("apple");
    tree.insert("app");
    tree.insert("banana");
    tree.insert("band");
    tree.insert("bandana");

    std::cout << "Traversal of Radix Tree:" << std::endl;
    tree.traverse();

    std::cout << "Search 'apple': " << (tree.search("apple") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'app': " << (tree.search("app") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'band': " << (tree.search("band") ? "Found" : "Not Found") << std::endl;
    std::cout << "Search 'banda': " << (tree.search("banda") ? "Found" : "Not Found") << std::endl;

    return 0;
}

/* Visual Schema:

Structure of the Radix tree after inserting words:

          ""
         /  \
       "a"  "b"
      /      /  \
   "pp"   "and" "anana"
  /  \
"le"  ""

*/
