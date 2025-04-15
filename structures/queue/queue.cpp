#include "queue/queue_node.h"
#include "queue/queue.h"

#define QUEUE_NODE_EXPORTS
#define QUEUE_EXPORTS

namespace ds {
    void queue::enqueue(const int &value) {
        std::shared_ptr<queue_node> new_node = std::make_shared<queue_node>(value, nullptr);

        if (!_tail) {
            _head = new_node;
        } else {
            _tail->_next_node = new_node;
        }

        _tail = new_node;

        _size++;
    }

    void queue::dequeue() {
        if (_head) {
            if (!_head->_next_node) {
                _tail = nullptr;
            }
            
            _head = _head->_next_node;

            _size--;
        }
    }

    int& queue::head() const {
        return _head->_value;
    }

    int& queue::tail() const {
        return _tail->_value;
    }

    size_t queue::get_size() const {
        return _size;
    }

    bool queue::is_empty() const {
        return _tail == nullptr;
    }

}