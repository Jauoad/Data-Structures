// ﷽
// MaxHeap.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MaxHeap {
    vector<int> heap;

    // Helper function to maintain the heap property by moving a node up the tree
    void heapifyUp(int index) {
        int parent = (index - 1) / 2;
        while (index > 0 && heap[parent] < heap[index]) {
            swap(heap[parent], heap[index]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    // Helper function to maintain the heap property by moving a node down the tree
    void heapifyDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Function to insert a new key into the heap
    void insert(int key) {
        heap.push_back(key);
        heapifyUp(heap.size() - 1);
    }

    // Function to extract the maximum key from the heap
    int extractMax() {
        if (heap.empty()) {
            throw logic_error("Heap is empty");
        }

        int max = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return max;
    }

    // Function to print the elements of the heap
    void printHeap() {
        for (int i = 0; i < heap.size(); ++i) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    MaxHeap maxHeap;
    maxHeap.insert(5);
    maxHeap.insert(3);
    maxHeap.insert(8);
    maxHeap.insert(1);
    maxHeap.insert(10);

    cout << "Max heap: ";
    maxHeap.printHeap();

    cout << "Extracted max: " << maxHeap.extractMax() << endl;
    cout << "Max heap after extraction: ";
    maxHeap.printHeap();

    return 0;
}

/*
     Max Heap:

        10
      /    \
     5      8
    / \
   3   1



*/