// ﷽
// LinkedList.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Method to insert a new node at the end of the list
    void append(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }

    // Method to display the elements of the list
    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

int main() {
    LinkedList list;

    // Appending elements to the linked list
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);

    // Displaying the linked list
    list.display();

    return 0;
}

/*

Linked List


  Node 1       Node 2       Node 3       Node 4       nullptr
+-------+    +-------+    +-------+    +-------+      +------+
|  data |    |  data |    |  data |    |  data |      |      |
|  next:| -> |  next:| -> |  next:| -> |  next:|  ->  | NULL |
+-------+    +-------+    +-------+    +-------+      +------+
   1            2            3            4



*/
