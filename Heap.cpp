// ﷽
// Heap.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For std::out_of_range


// Class representing a Heap data structure
class Heap {
private:
    std::vector<int> heap; // Vector to store elements of the heap

    // Method to swap two elements in the heap
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Method to adjust the heap upwards (sifting up)
    void siftUp(int index) {
        while (index > 0 && heap[index] < heap[(index - 1) / 2]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    // Method to adjust the heap downwards (sifting down)
    void siftDown(int index) {
        int minIndex = index;
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;

        if (leftChild < heap.size() && heap[leftChild] < heap[minIndex]) {
            minIndex = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] < heap[minIndex]) {
            minIndex = rightChild;
        }

        if (minIndex != index) {
            swap(heap[index], heap[minIndex]);
            siftDown(minIndex);
        }
    }

public:
    // Method to insert an element into the heap
    void insert(int value) {
        heap.push_back(value);
        siftUp(heap.size() - 1);
    }

    // Method to extract the root element from the heap (the minimum element in a min heap)
    int extractMin() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        int minElement = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        siftDown(0);
        return minElement;
    }

    // Method to check if the heap is empty
    bool isEmpty() const {
        return heap.empty();
    }

    // Method to display the contents of the heap
    void display() const {
        std::cout << "Heap: ";
        for (int i = 0; i < heap.size(); ++i) {
            std::cout << heap[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // Creating a min heap
    Heap minHeap;

    // Inserting elements into the heap
    minHeap.insert(4);
    minHeap.insert(7);
    minHeap.insert(2);
    minHeap.insert(5);
    minHeap.insert(1);

    // Displaying the contents of the heap
    minHeap.display();

    // Extracting the minimum element from the heap
    int minElement = minHeap.extractMin();
    std::cout << "Min Element: " << minElement << std::endl;

    // Displaying the contents of the heap after extraction
    minHeap.display();

    return 0;
}

/* 

    Heap: 1 4 2 7 5 
    Min Element: 1
    Heap: 2 4 5 7 


*/
