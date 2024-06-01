// ﷽
// Array.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad


#include <iostream>
#include <stdexcept> // For std::out_of_range

// Class representing a simple Array data structure
class Array {
private:
    int* data; // Pointer to the array data
    int size;  // Size of the array

public:
    // Constructor with size parameter
    Array(int size) : size(size) {
        // Dynamically allocate memory for the array
        data = new int[size];
    }

    // Destructor to free the allocated memory
    ~Array() {
        delete[] data;
    }

    // Method to access elements of the array
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }
};

int main() {
    // Create an array of size 5
    Array arr(5);

    // Assign values to array elements
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    // Access and print array elements
    for (int i = 0; i < 5; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    return 0;
}
