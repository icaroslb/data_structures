#include <iostream>
#include <algorithm>

#include <rb_tree/rb_tree.h>

struct teste {
    int _x;
    int _y;

    teste() {}
    teste(int x, int y) : _x(x), _y(y) {}
    teste(const teste& t) : _x(t._x), _y(t._y) {}
};

int main() {
    // ds::rb_tree<int> set0;

    // set0.insert(0);
    // set0.insert(1);
    // set0.insert(2);
    // set0.insert(3);
    // set0.insert(4);
    // set0.insert(5);
    // set0.insert(6);
    // set0.insert(7);
    // set0.insert(8);
    // set0.insert(9);
    // set0.insert(10);
    // set0.insert(11);
    // set0.insert(12);
    // set0.insert(13);
    // set0.insert(14);
    // set0.insert(15);
    // set0.insert(16);
    // set0.insert(17);
    // set0.insert(18);
    // set0.insert(19);
    // set0.insert(20);
    // set0.insert(21);
    // set0.insert(22);
    // set0.insert(23);
    // set0.insert(24);
    // set0.insert(25);
    // set0.insert(26);
    // set0.insert(27);
    // set0.insert(28);
    // set0.insert(29);

    ds::rb_tree<teste> set0([](const teste &t0, const teste &t1) -> bool {
        return (
            (t0._x < t1._x) ||
            (t0._x == t1._x && (t0._y < t1._y))
        );
    });

    set0.insert(teste(0, 0));
    set0.insert(teste(1, 1));
    set0.insert(teste(2, 2));
    set0.insert(teste(3, 3));
    set0.insert(teste(4, 4));
    set0.insert(teste(5, 5));
    set0.insert(teste(6, 6));
    set0.insert(teste(7, 7));
    set0.insert(teste(8, 8));
    set0.insert(teste(9, 9));
    set0.insert(teste(10, 10));
    set0.insert(teste(11, 11));
    set0.insert(teste(12, 12));
    set0.insert(teste(13, 13));
    set0.insert(teste(14, 14));
    set0.insert(teste(15, 15));
    set0.insert(teste(16, 16));
    set0.insert(teste(17, 17));
    set0.insert(teste(18, 18));
    set0.insert(teste(19, 19));
    set0.insert(teste(20, 20));
    set0.insert(teste(21, 21));
    set0.insert(teste(22, 22));
    set0.insert(teste(23, 23));
    set0.insert(teste(24, 24));
    set0.insert(teste(25, 25));
    set0.insert(teste(26, 26));
    set0.insert(teste(27, 27));
    set0.insert(teste(28, 28));
    set0.insert(teste(29, 29));

    std::for_each(std::begin(set0), std::end(set0), [] (const teste &value) {
        std::cout << "( " << value._x << ", " << value._y << " ) -> ";
    });

    std::cout << "NULL" << std::endl;
}