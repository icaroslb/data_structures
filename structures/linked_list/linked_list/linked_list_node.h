#ifndef LINKED_LIST_NODE
#define LINKED_LIST_NODE

#include <memory>

#ifdef LINKED_LIST_NODE_EXPORTS
#define LINKED_LIST_NODE_API __declspec(dllexport)
#else
#define LINKED_LIST_NODE_API __declspec(dllimport)
#endif

namespace ds {

    template <class T>
    struct linked_list_node {
    public:
        linked_list_node()
        : _value(0)
        , _prev()
        , _next() {}

        linked_list_node(const T &value, std::weak_ptr<linked_list_node> prev, std::shared_ptr<linked_list_node> next)
        : _value(value)
        , _prev(prev)
        , _next(next) {}

        protected:

        linked_list_node* successor() const {
            return _next.get();
        }
    
        linked_list_node* predecessor() const {
            return _prev.lock().get();
        }

        T _value;
        std::weak_ptr<linked_list_node> _prev;
        std::shared_ptr<linked_list_node> _next;

        template <class U> friend class linked_list;
    };

}

#endif // LINKED_LIST_NODE