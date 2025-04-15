#ifndef QUEUE_H
#define QUEUE_H

#include "queue_node.h"

#ifdef QUEUE_EXPORTS
#define QUEUE_API __declspec(dllexport)
#else
#define QUEUE_API __declspec(dllimport)
#endif

namespace ds {

    class queue {
    public:
        queue()
        : _size(0)
        , _head()
        , _tail()
        {}

        queue(const queue & new_queue)
        : _size(0)
        , _head()
        , _tail()
        {}

        void enqueue(const int &value);
        void dequeue();

        int& head() const;
        int& tail() const;

        size_t get_size() const;
        bool is_empty() const;

    private:
        size_t _size;
        std::shared_ptr<queue_node> _head;
        std::shared_ptr<queue_node> _tail;
    };

}

#endif // QUEUE_H