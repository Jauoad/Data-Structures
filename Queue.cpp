// ﷽
// Queue.cpp (filename)
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <queue>

int main() {
    std::queue<int> Q;

    Q.push(10);
    Q.push(20);
    Q.push(30);
    Q.push(40);
    Q.push(50);

    std::cout << "Queue elements: ";
    while (!Q.empty()) {
        std::cout << Q.front() << " ";
        Q.pop();
    }
    std::cout << std::endl;

    return 0;
}

/* 
         Queue elements:  10 | 20 | 30 | 40 | 50 
                          -----------------------
*/