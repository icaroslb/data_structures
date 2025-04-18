#include <iostream>
#include <algorithm>

#include <linked_list/linked_list.h>

int main() {
    ds::linked_list<int> teste{};
    
    size_t size = teste.get_size();

    teste.insert(0);
    teste.insert(1);
    teste.insert(2);
    teste.insert(3);
    teste.insert(4);
    teste.insert(5);
    teste.insert(6);
    teste.insert(7);
    teste.insert(8);
    teste.insert(9);

    teste.insert(2, 9);

    teste.remove(size_t(5));

    ds::linked_list<int>::Iterator iterator = teste.tail();

    while (!iterator.is_null())
    {
        std::cout << *iterator << " -> ";

        ++iterator;
    }
    

    std::cout << "NULL" << std::endl;
}