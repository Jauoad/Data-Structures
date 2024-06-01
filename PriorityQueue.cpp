// ﷽
// Filename: PriorityQueue.cpp
// Source: https://github.com/Jauoad
// Copyright (c) 2024 Jauoad

#include <iostream>
#include <queue>

// Function to print the elements of a priority queue
template <typename T, typename Container, typename Compare>
void printPriorityQueue(std::priority_queue<T, Container, Compare>& pq) {
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << std::endl;
}


int main() {
    // Creating a max priority queue (by default, it is maximum)
    std::priority_queue<int> max_pq;

    // Inserting elements into the max priority queue
    max_pq.push(3);
    max_pq.push(5);
    max_pq.push(1);
    max_pq.push(9);

    std::cout << "Max Priority Queue: ";
    printPriorityQueue(max_pq);

    // Creating a min priority queue
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;

    // Inserting elements into the min priority queue
    min_pq.push(3);
    min_pq.push(5);
    min_pq.push(1);
    min_pq.push(9);

    std::cout << "Min Priority Queue: ";
    printPriorityQueue(min_pq);

    return 0;
}

/* Visual Schema:

    Max Priority Queue: 9 5 3 1
    Min Priority Queue: 1 3 5 9

*/
