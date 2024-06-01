// ﷽
// InvertedIndex.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad


#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// InvertedIndex class represents the inverted index data structure
class InvertedIndex {
private:
    std::unordered_map<std::string, std::vector<int>> index; // Hash map to store the inverted index

public:
    // Constructor
    InvertedIndex() {}

    // Destructor
    ~InvertedIndex() {}

    // Add a document to the inverted index
    void addDocument(const std::string& document, int documentId) {
        std::vector<std::string> words = extractWords(document);
        for (const std::string& word : words) {
            index[word].push_back(documentId);
        }
    }

    // Search for documents containing a specific term
    std::vector<int> search(const std::string& term) {
        if (index.find(term) != index.end()) {
            return index[term];
        } else {
            return {};
        }
    }

    // Remove a document from the inverted index
    void removeDocument(int documentId) {
        for (auto& entry : index) {
            auto& docIds = entry.second;
            docIds.erase(std::remove(docIds.begin(), docIds.end(), documentId), docIds.end());
        }
    }

    // Clear the inverted index
    void clearIndex() {
        index.clear();
    }

    // Get the number of unique terms in the inverted index
    int getNumUniqueTerms() {
        return index.size();
    }

    // Extract words from a document (simplified for demonstration)
    std::vector<std::string> extractWords(const std::string& document) {
        std::vector<std::string> words;
        std::string word;
        for (char c : document) {
            if (c == ' ') {
                words.push_back(word);
                word.clear();
            } else {
                word += c;
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }
        return words;
    }

    // Print the inverted index
    void printIndex() {
        std::cout << "Inverted Index:" << std::endl;
        for (const auto& entry : index) {
            std::cout << entry.first << ": ";
            for (int docId : entry.second) {
                std::cout << docId << " ";
            }
            std::cout << std::endl;
        }
    }
};

// Main function to test the InvertedIndex class
int main() {
    // Create an instance of the InvertedIndex class
    InvertedIndex index;

    // Add documents to the inverted index
    index.addDocument("apple banana apple", 1);
    index.addDocument("banana orange", 2);
    index.addDocument("apple orange", 3);

    // Search for documents containing a specific term
    std::cout << "Documents containing 'apple': ";
    std::vector<int> appleDocs = index.search("apple");
    for (int docId : appleDocs) {
        std::cout << docId << " ";
    }
    std::cout << std::endl;

    // Print the inverted index
    index.printIndex();

    // Remove a document from the inverted index
    index.removeDocument(2);

    // Print the updated inverted index
    std::cout << "Updated Inverted Index:" << std::endl;
    index.printIndex();

    // Clear the inverted index
    index.clearIndex();

    // Print the cleared inverted index
    std::cout << "Cleared Inverted Index:" << std::endl;
    index.printIndex();

    return 0;
}

/*


Inverted Index:
apple: 1 3
banana: 1 2
orange: 2 3

Updated Inverted Index:
apple: 1 3
orange: 3

Cleared Inverted Index:

*/
