#ifndef QUEUE_H
#define QUEUE_H

#include "queue_node.h"

#ifdef QUEUE_EXPORTS
#define QUEUE_API __declspec(dllexport)
#else
#define QUEUE_API __declspec(dllimport)
#endif

namespace ds {

    template <class T>
    class queue {
    public:
        queue()
        : _size(0)
        , _head(nullptr)
        , _tail(nullptr)
        {}

        queue(const queue & new_queue)
        : _size(0)
        , _head(nullptr)
        , _tail(nullptr)
        {}

        void enqueue(const T &value);
        void dequeue();

        T& head() const;
        T& tail() const;

        size_t get_size() const;
        bool is_empty() const;

    private:
        size_t _size;
        std::shared_ptr<queue_node<T>> _head;
        std::shared_ptr<queue_node<T>> _tail;
    };

    template <class T>
    void queue<T>::enqueue(const T &value) {
        std::shared_ptr<queue_node<T>> new_node = std::make_shared<queue_node<T>>(value, nullptr);

        if (!_tail) {
            _head = new_node;
        } else {
            _tail->_next_node = new_node;
        }

        _tail = new_node;

        _size++;
    }

    template <class T>
    void queue<T>::dequeue() {
        if (_head) {
            if (!_head->_next_node) {
                _tail = nullptr;
            }
            
            _head = _head->_next_node;

            _size--;
        }
    }

    template <class T>
    T& queue<T>::head() const {
        return _head->_value;
    }

    template <class T>
    T& queue<T>::tail() const {
        return _tail->_value;
    }

    template <class T>
    size_t queue<T>::get_size() const {
        return _size;
    }

    template <class T>
    bool queue<T>::is_empty() const {
        return _tail == nullptr;
    }

}

#endif // QUEUE_H