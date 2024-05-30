// ﷽
// SuffixTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <string>
#include <unordered_map>
#include <limits>

class SuffixTree {
private:
    struct Node {
        std::unordered_map<char, Node*> children;
        size_t start;
        size_t* end;
        Node* suffixLink;

        Node(size_t start, size_t* end) : start(start), end(end), suffixLink(nullptr) {}
    };

    Node* root;
    std::string text;
    Node* lastNewNode;
    Node* activeNode;
    size_t activeEdge;
    size_t activeLength;
    size_t remainingSuffixCount;
    size_t leafEnd;
    size_t* rootEnd;
    size_t* splitEnd;
    size_t size;

    Node* newNode(size_t start, size_t* end) {
        Node* node = new Node(start, end);
        node->suffixLink = root;
        return node;
    }

    size_t edgeLength(Node* n) const {
        return *(n->end) - (n->start) + 1;
    }

    void extendSuffixTree(size_t pos) {
        leafEnd = pos;
        remainingSuffixCount++;
        lastNewNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) {
                activeEdge = pos;
            }

            if (activeNode->children.find(text[activeEdge]) == activeNode->children.end()) {
                activeNode->children[text[activeEdge]] = newNode(pos, &leafEnd);

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
            } else {
                Node* next = activeNode->children[text[activeEdge]];
                if (activeLength >= edgeLength(next)) {
                    activeEdge += edgeLength(next);
                    activeLength -= edgeLength(next);
                    activeNode = next;
                    continue;
                }

                if (text[next->start + activeLength] == text[pos]) {
                    if (lastNewNode != nullptr && activeNode != root) {
                        lastNewNode->suffixLink = activeNode;
                        lastNewNode = nullptr;
                    }

                    activeLength++;
                    break;
                }

                splitEnd = new size_t(next->start + activeLength - 1);
                Node* split = newNode(next->start, splitEnd);
                activeNode->children[text[activeEdge]] = split;

                split->children[text[pos]] = newNode(pos, &leafEnd);
                next->start += activeLength;
                split->children[text[next->start]] = next;

                if (lastNewNode != nullptr) {
                    lastNewNode->suffixLink = split;
                }

                lastNewNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = pos - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }

    void printTree(Node* node, size_t height) const {
        for (const auto& pair : node->children) {
            Node* child = pair.second;
            std::cout << std::string(height * 2, ' ') << text.substr(child->start, edgeLength(child)) << std::endl;
            printTree(child, height + 1);
        }
    }

public:
    
    void printSuffixes() const {
        for (size_t i = 0; i < text.length(); ++i) {
            std::cout << text.substr(i) << std::endl;
        }
    }

    SuffixTree(const std::string& text) : text(text) {
        size = text.size();
        rootEnd = new size_t(std::numeric_limits<size_t>::max());
        root = newNode(std::numeric_limits<size_t>::max(), rootEnd);
        activeNode = root;

        activeEdge = 0;
        activeLength = 0;
        remainingSuffixCount = 0;
        leafEnd = 0;

        for (size_t i = 0; i < size; i++) {
            extendSuffixTree(i);
        }
    }

    void print() const {
        printTree(root, 0);
    }
};

int main() {
    std::string text = "banana";
    SuffixTree suffixTree(text);
    
    std::cout << "Suffixes:" << std::endl;
    suffixTree.printSuffixes();
    
    std::cout << "=================" << std::endl;
    
    std::cout << "Suffix Tree:" << std::endl;
    std::cout << std::endl;
    std::cout << "root" << std::endl;
    suffixTree.print();
    
    return 0;
}

/*

First Visualization

root (start=max, end=max)
├── b (start=0, end=0)
│   ├── a (start=1, end=5)
│   │   ├── n (start=2, end=5)
│   │   │   ├── a (start=3, end=5)
│   │   │   │   ├── n (start=4, end=5)
│   │   │   │   │   ├── a (start=5, end=5)
│   │   │   │   │   └── [end]
│   │   │   │   └── [end]
│   │   │   └── [end]
│   │   └── [end]
│   ├── a (start=1, end=6)
│   │   ├── n (start=2, end=6)
│   │   │   ├── a (start=3, end=6)
│   │   │   │   ├── n (start=4, end=6)
│   │   │   │   │   ├── a (start=5, end=6)
│   │   │   │   │   └── [end]
│   │   │   │   └── [end]
│   │   │   └── [end]
│   │   └── [end]
│   └── [end]
├── a (start=1, end=6)
│   ├── n (start=2, end=6)
│   │   ├── a (start=3, end=6)
│   │   │   ├── n (start=4, end=6)
│   │   │   │   ├── a (start=5, end=6)
│   │   │   │   └── [end]
│   │   │   └── [end]
│   │   └── [end]
│   └── [end]
├── n (start=2, end=6)
│   ├── a (start=3, end=6)
│   │   ├── n (start=4, end=6)
│   │   │   ├── a (start=5, end=6)
│   │   │   └── [end]
│   │   └── [end]
│   └── [end]
├── a (start=3, end=6)
│   ├── n (start=4, end=6)
│   │   ├── a (start=5, end=6)
│   │   └── [end]
│   └── [end]
├── n (start=4, end=6)
│   ├── a (start=5, end=6)
│   └── [end]
└── a (start=5, end=6)
    └── [end]


Second Visualization

                      root
               ________|________
              |                 |
             'b'                'a'
         _____|______            |
        |            |        'nana'
       'a'          'n'     ____|_____
      ___|___       _|_    |         |
     |       |     |   |   'a'      'na'
    'na'   'na'  'a'  'a'         ___|___
    _|_    _|_                      |    |
   |   |  |   |                  'na'  'a'
   'n'  'a'  'a'                  |
                                  'a'



/*