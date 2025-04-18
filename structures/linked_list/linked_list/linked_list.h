#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "linked_list_node.h"

#ifdef LINKED_LIST_EXPORTS
#define LINKED_LIST_API __declspec(dllexport)
#else
#define LINKED_LIST_API __declspec(dllimport)
#endif

namespace ds {

    template <class T>
    class linked_list {
    public:
        struct linked_list_iterator
        {
            linked_list_iterator(const std::shared_ptr<linked_list_node<T>> &node)
            : _element_ptr(node) {}

            T& operator*() {
                return _element_ptr->_value;
            }

            T* operator7() {
                return &(_element_ptr->_value);
            }

            linked_list_iterator& operator= (const linked_list_iterator &iterator) {
                _element_ptr = iterator._element_ptr;
            }

            linked_list_iterator& operator++() {
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_next;
                }
                return *this;
            }
            linked_list_iterator& operator--() {
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_prev.lock();
                }
                return *this;
            }
            linked_list_iterator operator++(int) {
                linked_list_iterator iterator = *this;
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_next;
                }
                return iterator;
            }
            linked_list_iterator operator--(int) {
                linked_list_iterator iterator = *this;
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_prev.lock();
                }
                return iterator;
            }

            bool is_null() {
                return _element_ptr == nullptr;
            }

            std::shared_ptr<linked_list_node<T>> _element_ptr = nullptr;
        };


        linked_list()
        : _size(0)
        , _head(nullptr)
        , _tail(nullptr) {}

        linked_list(const linked_list<T>& list)
        : _size(list._size)
        , _head(list._head)
        , _tail(list._tail) {}

        linked_list<T>::linked_list_iterator insert(const T &new_value) {
            std::shared_ptr<linked_list_node<T>> new_node = std::make_shared<linked_list_node<T>>(new_value, _head, nullptr);
    
            if (_head) {
                _head->_next = new_node;
            }
            
            _head = new_node;
    
            if (!_tail) {
                _tail = _head;
            }
            
            _size++;
    
            return linked_list<T>::linked_list_iterator(new_node);
        }

        linked_list<T>::linked_list_iterator insert(const size_t &pos, const T &new_value) {
            _size++;
            
            if (pos < _size) {
                linked_list<T>::linked_list_iterator pos_iterator = get(pos);
                std::shared_ptr<linked_list_node<T>> prev = pos_iterator._element_ptr->_prev.lock();
                std::shared_ptr<linked_list_node<T>> new_node = std::make_shared<linked_list_node<T>>(new_value, prev, pos_iterator._element_ptr);
    
                pos_iterator._element_ptr->_prev = new_node;
    
                if (prev) {
                    prev->_next = new_node;
                } else {
                    _tail = new_node;
                }
    
                return linked_list<T>::linked_list_iterator(new_node);
            } else {
                return insert(new_value);
            }
        }

        bool remove(const size_t &pos);
        bool remove(const T &value);
        void remove(linked_list<T>::linked_list_iterator &remove_iterator);

        linked_list<T>::linked_list_iterator get(const size_t &pos) {
            linked_list<T>::linked_list_iterator iterator{_tail};
            
            if (pos < _size) {
                for (size_t i = 0; i < pos; i++) {
                    ++iterator;
                }
            }
    
            return iterator;
        }

        linked_list<T>::linked_list_iterator search(const T &value) {
            linked_list<T>::linked_list_iterator iterator{_tail};
            
            while (!iterator.is_null()) {
                if (iterator._element_ptr->_value == value) {
                    break;
                } else {
                    ++iterator;
                }
            }
    
            return iterator;
        }

        linked_list<T>::linked_list_iterator head() {
            return linked_list<T>::linked_list_iterator{_head};
        }

        linked_list<T>::linked_list_iterator tail() {
            return linked_list<T>::linked_list_iterator{_tail};
        }

        size_t get_size() {
            return _size;
        }

    private:
        size_t _size;
        std::shared_ptr<linked_list_node<T>> _head;
        std::shared_ptr<linked_list_node<T>> _tail;
    };

    template <class T>
    bool linked_list<T>::remove(const size_t &pos) {
        linked_list<T>::linked_list_iterator remove_iterator = get(pos);

        if (remove_iterator._element_ptr) {
            remove(remove_iterator);

            return true;
        }

        return false;
    }

    template <class T>
    bool linked_list<T>::remove(const T &value) {
        linked_list<T>::linked_list_iterator remove_iterator = search(value);

        if (remove_iterator._element_ptr) {
            remove(remove_iterator);

            return true;
        }

        return false;
    }

    template <class T>
    void linked_list<T>::remove(linked_list<T>::linked_list_iterator &remove_iterator) {
        std::shared_ptr<linked_list_node<T>> prev = remove_iterator._element_ptr->_prev.lock();

            if (prev) {
                prev->_next = remove_iterator._element_ptr->_next;
            }

            if (remove_iterator._element_ptr->_next) {
                remove_iterator._element_ptr->_next->_prev = prev;
            }

            if (remove_iterator._element_ptr == _head) {
                _head = prev;
            }

            if (remove_iterator._element_ptr == _tail) {
                _tail = remove_iterator._element_ptr->_next;
            }

            _size--;
    }

}
#endif // LINKED_LIST_H