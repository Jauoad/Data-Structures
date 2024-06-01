// ﷽
// MerkleTree.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <string>
#include <openssl/sha.h>

class MerkleTree {
public:
    std::vector<std::string> leaves;
    std::vector<std::string> tree;

    MerkleTree(const std::vector<std::string>& data) {
        for (const auto& datum : data) {
            leaves.push_back(hash(datum));
        }
        buildTree();
    }

    std::string getRoot() {
        return tree.empty() ? "" : tree[0];
    }

private:
    void buildTree() {
        std::vector<std::string> currentLevel = leaves;
        while (currentLevel.size() > 1) {
            std::vector<std::string> nextLevel;
            for (size_t i = 0; i < currentLevel.size(); i += 2) {
                if (i + 1 < currentLevel.size()) {
                    nextLevel.push_back(hash(currentLevel[i] + currentLevel[i + 1]));
                } else {
                    nextLevel.push_back(currentLevel[i]);
                }
            }
            currentLevel = nextLevel;
        }
        tree = currentLevel;
    }

    std::string hash(const std::string& data) {
        unsigned char digest[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)data.c_str(), data.size(), digest);
        char mdString[SHA256_DIGEST_LENGTH * 2 + 1];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
        }
        return std::string(mdString);
    }
};

int main() {
    std::vector<std::string> data = {"a", "b", "c", "d"};
    MerkleTree tree(data);

    std::cout << "Merkle Root: " << tree.getRoot() << std::endl;
    return 0;
}

/* 

Merkle tree structure for data "a", "b", "c", "d":

        hash(hash(ab) + hash(cd))
        /                       \
   hash(ab)                  hash(cd)
   /      \                  /      \
hash(a)  hash(b)         hash(c)  hash(d)

*/

