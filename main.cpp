#include <iostream>
#include <algorithm>

#include <queue/queue.h>

int main() {
    ds::queue<int> teste{};
    
    size_t size = teste.get_size();

    teste.enqueue(0);
    teste.enqueue(1);
    teste.enqueue(2);
    teste.enqueue(3);
    teste.enqueue(4);
    teste.enqueue(5);
    teste.enqueue(6);
    teste.enqueue(7);
    teste.enqueue(8);
    teste.enqueue(9);

    while (!teste.is_empty())
    {
        std::cout << teste.head() << " -> ";

        teste.dequeue();
    }
    

    std::cout << "NULL" << std::endl;
}