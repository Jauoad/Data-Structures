// ﷽
// DynamicArray.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad


#include <iostream>
#include <stdexcept> // For std::out_of_range

// Class representing a dynamic array data structure
class DynamicArray {
private:
    int* data; // Pointer to the array data
    int size;  // Size of the array

public:
    // Constructor with size parameter
    DynamicArray(int size) : size(size) {
        // Dynamically allocate memory for the array
        data = new int[size];
    }

    // Destructor to free the allocated memory
    ~DynamicArray() {
        delete[] data;
    }

    // Method to access elements of the array
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Method to resize the array
    void resize(int newSize) {
        int* newData = new int[newSize];
        int minSize = (newSize < size) ? newSize : size;
        for (int i = 0; i < minSize; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
    }
};

int main() {
    // Create a dynamic array of size 5
    DynamicArray arr(5);

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

    // Resize the array to 8 elements
    arr.resize(8);

    // Access and print array elements after resizing
    for (int i = 0; i < 8; ++i) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    return 0;
}

/*


Dynamic Array:
+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  <-- Initial array with size 8
+---+---+---+---+---+---+---+---+

After resizing to 10:
+---+---+---+---+---+---+---+---+---+---+
| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |  <-- Resized array with size 10
+---+---+---+---+---+---+---+---+---+---+



*/
