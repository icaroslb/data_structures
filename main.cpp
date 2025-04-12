#include <iostream>
#include <algorithm>

#include <rb_tree/rb_tree.h>

int main() {
    ds::rb_tree<int> set0;

    set0.insert(0);
    set0.insert(1);
    set0.insert(2);
    set0.insert(3);
    set0.insert(4);
    set0.insert(5);
    set0.insert(6);
    set0.insert(7);
    set0.insert(8);
    set0.insert(9);
    set0.insert(10);
    set0.insert(11);
    set0.insert(12);
    set0.insert(13);
    set0.insert(14);
    set0.insert(15);
    set0.insert(16);
    set0.insert(17);
    set0.insert(18);
    set0.insert(19);
    set0.insert(20);
    set0.insert(21);
    set0.insert(22);
    set0.insert(23);
    set0.insert(24);
    set0.insert(25);
    set0.insert(26);
    set0.insert(27);
    set0.insert(28);
    set0.insert(29);

    std::for_each(std::begin(set0), std::end(set0), [] (const int value) {
        std::cout << value << " -> ";
    });

    std::cout << "NULL" << std::endl;
}