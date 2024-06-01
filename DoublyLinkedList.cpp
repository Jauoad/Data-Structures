// ﷽
// DoublyLinkedList.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>

// Structure to represent a node in the doubly linked list
struct Node {
    int data;   // Value of the node
    Node* prev; // Pointer to the previous node
    Node* next; // Pointer to the next node

    // Constructor to initialize a node with a given value
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Class to represent a doubly linked list
class DoublyLinkedList {
private:
    Node* head; // Pointer to the first node in the list

public:
    // Constructor to initialize the list with a node initialized to nullptr
    DoublyLinkedList() : head(nullptr) {}

    // Method to insert a node at the end of the list
    void insert(int value) {
        Node* newNode = new Node(value); // Create a new node with the given value

        if (head == nullptr) { // If the list is empty
            head = newNode;    // The new node becomes the first node (head)
        } else {
            Node* current = head;
            while (current->next != nullptr) { // Traverse the list until reaching the last node
                current = current->next;
            }
            current->next = newNode; // The last node points to the new node
            newNode->prev = current; // The new node points to the last node
        }
    }

    // Method to display the list in forward order
    void displayForward() {
        Node* current = head;
        std::cout << "Forward: ";
        while (current != nullptr) { // Traverse the list from beginning to end
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Method to display the list in reverse order
    void displayBackward() {
        Node* current = head;
        if (current == nullptr) return; // If the list is empty, there's nothing to display
        while (current->next != nullptr) { // Traverse the list until reaching the last node
            current = current->next;
        }
        std::cout << "Backward: ";
        while (current != nullptr) { // Traverse the list from the last node to the first node
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    // Create a doubly linked list and insert some values
    DoublyLinkedList myList;
    myList.insert(1);
    myList.insert(2);
    myList.insert(3);
    myList.insert(4);

    // Display the list in forward and reverse order
    myList.displayForward(); // Forward: 1 2 3 4
    myList.displayBackward(); // Backward: 4 3 2 1

    return 0;
}

/* 

Doubly Linked List

+------+    +------+    +------+    +------+    +------+
|  1   |    |  2   |    |  3   |    |  4   |    |  5   |
|prev: |<-- |prev: |<-- |prev: |<-- |prev: |<-- |prev: |<--> nullptr
|next: | -->|next: | -->|next: | -->|next: | -->|next: |<--> 
+------+    +------+    +------+    +------+    +------+



*/
