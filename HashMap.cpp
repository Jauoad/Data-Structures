// ﷽
// HashMap.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <list>
#include <utility>

class HashMap {
public:
    HashMap(size_t size);
    void insert(int key, int value);
    bool remove(int key);
    bool search(int key, int& value);
    void display();

private:
    std::vector<std::list<std::pair<int, int>>> table;
    size_t hashFunction(int key);
};

HashMap::HashMap(size_t size) : table(size) {}

size_t HashMap::hashFunction(int key) {
    return key % table.size();
}

void HashMap::insert(int key, int value) {
    size_t hashValue = hashFunction(key);
    for (auto& pair : table[hashValue]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    table[hashValue].emplace_back(key, value);
}

bool HashMap::remove(int key) {
    size_t hashValue = hashFunction(key);
    auto& list = table[hashValue];
    for (auto it = list.begin(); it != list.end(); ++it) {
        if (it->first == key) {
            list.erase(it);
            return true;
        }
    }
    return false;
}

bool HashMap::search(int key, int& value) {
    size_t hashValue = hashFunction(key);
    for (const auto& pair : table[hashValue]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    return false;
}

void HashMap::display() {
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << "Bucket " << i << ": ";
        for (const auto& pair : table[i]) {
            std::cout << "[" << pair.first << ": " << pair.second << "] ";
        }
        std::cout << std::endl;
    }
}

int main() {
    HashMap hashMap(10);
    hashMap.insert(1, 100);
    hashMap.insert(2, 200);
    hashMap.insert(12, 300);  // This will go into the same bucket as key 2

    int value;
    if (hashMap.search(1, value)) {
        std::cout << "Found key 1 with value: " << value << std::endl;
    } else {
        std::cout << "Key 1 not found." << std::endl;
    }

    hashMap.display();

    hashMap.remove(2);
    hashMap.display();

    return 0;
}

/*

Structure of the HashMap after inserting keys:

    HashMap (size 10)
    -----------------------------------------
    | Bucket 0 | Bucket 1 | Bucket 2 | ...  |
    -----------------------------------------
    |          | [1: 100] | [2: 200] | ...  |
    |          |          | [12: 300]| ...  |
    |          |          |          | ...  |
    -----------------------------------------

After removing key 2:

    HashMap (size 10)
    -----------------------------------------
    | Bucket 0 | Bucket 1 | Bucket 2 | ...  |
    -----------------------------------------
    |          | [1: 100] | [12: 300]| ...  |
    |          |          |          | ...  |
    |          |          |          | ...  |
    -----------------------------------------
*/
