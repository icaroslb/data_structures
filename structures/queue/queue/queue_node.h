#ifndef QUEUE_NODE_H
#define QUEUE_NODE_H

#include <memory>

#ifdef QUEUE_NODE_EXPORTS
#define QUEUE_NODE_API __declspec(dllexport)
#else
#define QUEUE_NODE_API __declspec(dllimport)
#endif

namespace ds {

    struct queue_node {
        queue_node()
        {}

        queue_node(const int value, const std::shared_ptr<queue_node>& next_node)
        : _value(value)
        , _next_node(next_node)
        {}
        
        int _value;
        std::shared_ptr<queue_node> _next_node;
    };

}

#endif // QUEUE_NODE_H