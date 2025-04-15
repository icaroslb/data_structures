#ifndef STACK_NODE_H
#define STACK_NODE_H

#include <memory>

#ifdef STACK_NODE_EXPORTS
#define STACK_NODE_API __declspec(dllexport)
#else
#define STACK_NODE_API __declspec(dllimport)
#endif

namespace ds {

    template <class T>
    struct stack_node {
        stack_node()
        {}

        stack_node(const T value, const std::shared_ptr<stack_node>& next_node)
        : _value(value)
        , _next_node(next_node)
        {}
        
        T _value;
        std::shared_ptr<stack_node> _next_node;
    };

}

#endif // STACK_NODE_H