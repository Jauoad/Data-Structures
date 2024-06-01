// ﷽
// Stack.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <stack>

int main() {
    // Create a stack of integers
    std::stack<int> myStack;

    // Push elements onto the stack
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);
    myStack.push(40);
    myStack.push(50);

    // Print stack elements
    std::cout << "Stack elements: ";
    while (!myStack.empty()) {
        std::cout << myStack.top() << " "; // Print the top element
        myStack.pop(); // Pop the top element
    }
    std::cout << std::endl;

    return 0;
}

/*

    Stack elements: | 50
                    _ 
                    | 40
                    _ 
                    | 30
                    _ 
                    | 20
                    _ 
                    | 10

*/
