// ﷽
// SuffixArray.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <algorithm>

// Structure to represent a suffix
struct Suffix {
    int index; // Index of the suffix in the original text
    std::string suffix; // String representing the suffix

    // Constructor
    Suffix(int i, std::string s) : index(i), suffix(s) {}

    // Comparison operator to sort suffixes
    bool operator<(const Suffix& other) const {
        return suffix < other.suffix;
    }
};

// Class to represent the Suffix Array
class SuffixArray {
private:
    std::vector<int> suffixArray;

public:
    // Constructor taking a string as input
    SuffixArray(const std::string& text) {
        std::vector<Suffix> suffixes;

        // Create all suffixes
        for (int i = 0; i < text.size(); ++i) {
            suffixes.emplace_back(i, text.substr(i));
        }

        // Sort the suffixes
        std::sort(suffixes.begin(), suffixes.end());

        // Store the indices of sorted suffixes in the Suffix Array
        for (const auto& suffix : suffixes) {
            suffixArray.push_back(suffix.index);
        }
    }

    // Method to print the Suffix Array
    void printSuffixArray() const {
        std::cout << "Suffix Array: ";
        for (int index : suffixArray) {
            std::cout << index << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::string text = "banana";

    // Create the Suffix Array from the string
    SuffixArray sa(text);

    // Print the Suffix Array
    sa.printSuffixArray();

    return 0;

    /*
    Visual Representation:

    Original Text: "banana"

    Suffixes:
    0: banana
    1: anana
    2: nana
    3: ana
    4: na
    5: a

    Suffix Array:
    5 3 1 0 4 2
    */
}

