// ﷽
// SkipList.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <random>
#include <climits>

// Class for the Skip List node
class SkipNode {
public:
    int value;
    std::vector<SkipNode*> forward;

    SkipNode(int val, int level) : value(val), forward(level, nullptr) {}
};

class SkipList {
private:
    int max_level;
    float p;
    int level;
    SkipNode* header;

    // Function to generate the random level of nodes
    int randomLevel() {
        int lvl = 1;
        while ((float)rand() / RAND_MAX < p && lvl < max_level) {
            lvl++;
        }
        return lvl;
    }

public:
    SkipList(int max_lvl, float prob) : max_level(max_lvl), p(prob), level(0) {
        header = new SkipNode(INT_MIN, max_lvl);
    }

    // Function to search for an element in the Skip List
    bool search(int target) {
        SkipNode* current = header;
        for (int i = level - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < target) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return current && current->value == target;
    }

    // Function to insert an element into the Skip List
    void insert(int val) {
        SkipNode* current = header;
        std::vector<SkipNode*> update(max_level, nullptr);
        for (int i = level - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < val) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (!current || current->value != val) {
            int new_level = randomLevel();
            if (new_level > level) {
                for (int i = level; i < new_level; i++) {
                    update[i] = header;
                }
                level = new_level;
            }
            SkipNode* newNode = new SkipNode(val, new_level);
            for (int i = 0; i < new_level; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    // Function to remove an element from the Skip List
    void remove(int val) {
        SkipNode* current = header;
        std::vector<SkipNode*> update(max_level, nullptr);
        for (int i = level - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < val) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (current && current->value == val) {
            for (int i = 0; i < level; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (level > 0 && header->forward[level - 1] == nullptr) {
                level--;
            }
        }
    }
};

int main() {
    SkipList skiplist(4, 0.5);
    skiplist.insert(1);
    skiplist.insert(4);
    skiplist.insert(5);
    skiplist.insert(7);
    skiplist.insert(8);
    skiplist.remove(5);
    std::cout << "Search 4: " << std::boolalpha << skiplist.search(4) << std::endl; // Expected: true
    std::cout << "Search 5: " << std::boolalpha << skiplist.search(5) << std::endl; // Expected: false
    return 0;
}

/* Visual Schema:

                -oo -------------------------------------> +oo
Level 3:        -oo ------------> 4 -------------------> +oo
Level 2:        -oo -------> 4 ------------> 7 -------> +oo
Level 1:        -oo --> 1 --> 4 --> 5 --> 7 --> 8 --> +oo
Level 0:        -oo --> 1 --> 4 -->     7 --> 8 --> +oo

*/
