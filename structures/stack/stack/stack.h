#ifndef STACK_H
#define STACK_H

#include "stack_node.h"

#ifdef STACK_EXPORTS
#define STACK_API __declspec(dllexport)
#else
#define STACK_API __declspec(dllimport)
#endif

namespace ds {

    template <class T>
    class stack {
    public:
        stack()
        : _size(0)
        , _top(nullptr)
        {}

        stack(const stack& data)
        : _size(data._size)
        , _top(data._top)
        {}

        void push(const T &new_value);
        void pop();
        T& top() const;

        size_t get_size() const;
        bool is_empty() const;

    private:
        std::shared_ptr<stack_node<T>> _top;
        size_t _size;
    };

    template <class T>
    void stack<T>::push(const T &new_value) {
        _top = std::make_shared<stack_node<T>>(new_value, _top);

        _size++;
    }

    template <class T>
    void stack<T>::pop() {
        if (_top) {
            _top = _top->_next_node;
            
            _size--;
        }
    }

    template <class T>
    T& stack<T>::top() const {
        return _top->_value;
    }

    template <class T>
    size_t stack<T>::get_size() const {
        return _size;
    }

    template <class T>
    bool stack<T>::is_empty() const {
        return _top == nullptr;
    }

}

#endif // STACK_H