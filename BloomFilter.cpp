// ﷽
// BloomFilter.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <bitset>
#include <functional>
#include <cmath>

class BloomFilter {
private:
    std::vector<std::function<size_t(const std::string&)>> hashFunctions;
    std::bitset<10000> bitset; // Using a fixed size bitset for simplicity

public:
    // Constructor initializes hash functions
    BloomFilter() {
        // Default hash function
        hashFunctions.push_back(std::hash<std::string>());
        // Custom hash function
        hashFunctions.push_back([](const std::string& str) {
            size_t hash = 0;
            for (char c : str) {
                hash = (hash * 131) + c; // Simple custom hash function
            }
            return hash;
        });
    }

    // Insert an item into the filter
    void insert(const std::string& item) {
        for (auto hashFunc : hashFunctions) {
            size_t index = hashFunc(item) % bitset.size();
            bitset[index] = 1;
        }
    }

    // Check if an item might exist in the filter
    bool mightContain(const std::string& item) {
        for (auto hashFunc : hashFunctions) {
            size_t index = hashFunc(item) % bitset.size();
            if (!bitset[index]) {
                return false;
            }
        }
        return true;
    }

    // Clear the Bloom filter
    void clear() {
        bitset.reset();
    }

    // Get the size of the bitset
    size_t size() const {
        return bitset.size();
    }

    // Get the number of hash functions
    size_t numHashFunctions() const {
        return hashFunctions.size();
    }

    // Get the false positive probability
    double falsePositiveProbability(size_t numInsertedItems) const {
        // m = size of bitset, n = number of inserted items, k = number of hash functions
        size_t m = bitset.size();
        size_t n = numInsertedItems;
        size_t k = hashFunctions.size();

        // False positive probability formula: (1 - e^(-k * n / m))^k
        return pow(1 - exp(-1.0 * k * n / m), k);
    }
};

int main() {
    BloomFilter bloomFilter;

    // Insert some items
    bloomFilter.insert("apple");
    bloomFilter.insert("banana");
    bloomFilter.insert("orange");

    // Check if items might be in the filter
    std::cout << "Might contain apple: " << bloomFilter.mightContain("apple") << std::endl;
    std::cout << "Might contain pineapple: " << bloomFilter.mightContain("pineapple") << std::endl;
    std::cout << "Might contain orange: " << bloomFilter.mightContain("orange") << std::endl;

    // Display the size and number of hash functions
    std::cout << "Size of bitset: " << bloomFilter.size() << std::endl;
    std::cout << "Number of hash functions: " << bloomFilter.numHashFunctions() << std::endl;

    // Clear the filter
    bloomFilter.clear();
    std::cout << "Might contain apple after clearing: " << bloomFilter.mightContain("apple") << std::endl;

    // Calculate false positive probability after inserting 3 items
    std::cout << "False positive probability after inserting 3 items: " 
              << bloomFilter.falsePositiveProbability(3) << std::endl;

    return 0;
}


/* Bismiallah wa assalatu wa assalamu ala sayidina Muhammad wa ala alyh wa sahbyh ajmaein

           +------------+
           | Bloom      |
           | Filter     |
           +------------+
           /      |     \
     +-----+   +-----+  +-----+
     | Hash|   | Hash|  | Hash|
     | Func|   | Func|  | Func|
     +-----+   +-----+  +-----+
       |         |         |
     +----+   +----+    +----+
     |Hash|   |Hash|    |Hash|
     |Func|   |Func|    |Func|
     +----+   +----+    +----+
       |         |         |
     +----+   +----+    +----+
     |Hash|   |Hash|    |Hash|
     |Func|   |Func|    |Func|
     +----+   +----+    +----+
      /|\       /|\        /|\
       |         |          |
   +---+---+ +---+---+ +----+---+
   | Index | | Index | | Index |
   +-------+ +-------+ +--------+

****

Bloom Filter:

                 Hash Function 1
                      |
                      V
              +------------------+
              |                  |
       +----> |      Bit Array   |
       |      |                  |
       |      +------------------+
       |                |
       |                | Hash Function 2
       |                V
       |      +------------------+
       |      |                  |
       +----> |      Bit Array   |
              |                  |
              +------------------+
                      |
                      |
               ... (more hash functions and bit arrays)
                      |
                      |
              +------------------+
              |                  |
       +----> |      Bit Array   |
       |      |                  |
       |      +------------------+
       |                |
       |                | Hash Function N
       |                V
       |      +------------------+
       |      |                  |
       +----> |      Bit Array   |
              |                  |
              +------------------+


        Note that :

        - Each hash function generates an index in the bit array.
        - The Bloom filter typically consists of multiple hash functions and corresponding bit arrays.
        - Each bit array is usually implemented as a fixed-size array of bits, where each bit represents a slot in the filter.
        - Data items are inserted into the Bloom filter by setting the corresponding bits to 1 based on the hash values generated by the hash functions.
        - During membership query, the Bloom filter checks if all corresponding bits for a given item are set to 1. 
            If any bit is not set, the item is definitively not in the filter. If all bits are set, 
            the item is probably in the filter (but there's a chance of false positives).

        
                              

                        +---------------------------------------+
                        |               Bloom Filter            |
                        +---------------------------------------+
                        |                                       |
                        |  +-----------+       +-----------+    |
                        |  |  Hashing  |       |  Hashing  |    |
                        |  | Function  |       | Function  |    |
                        |  +-----------+       +-----------+    |
                        |           \            /              |
                        |            \          /               |
                        |             \        /                |
                        |              \      /                 |
                        |              +------+                 |
                        |              | Bits |                 |
                        |              +------+                 |
                        |                                       |
                        +---------------------------------------+


*/