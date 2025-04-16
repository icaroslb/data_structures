#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include <memory>

#ifdef QUEUE_NODE_EXPORTS
#define QUEUE_NODE_API __declspec(dllexport)
#else
#define QUEUE_NODE_API __declspec(dllimport)
#endif

namespace ds {

    template <class T>
    struct queue_node {
        queue_node()
        {}

        queue_node(const T &value, const std::shared_ptr<queue_node<T>>& next_node)
        : _value(value)
        , _next_node(next_node)
        {}
        
        T _value;
        std::shared_ptr<queue_node<T>> _next_node;
    };

}

#endif // QUEUE_NODE_H