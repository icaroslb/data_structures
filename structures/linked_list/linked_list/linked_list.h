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
        struct Iterator
        {
            Iterator(const std::shared_ptr<linked_list_node<T>> &node)
            : _element_ptr(node) {}

            Iterator(const Iterator &iterator)
            : _element_ptr(iterator._element_ptr) {}

            T& operator*() {
                return _element_ptr->_value;
            }

            T* operator7() {
                return &(_element_ptr->_value);
            }

            Iterator& operator= (const Iterator &iterator) {
                _element_ptr = iterator._element_ptr;
            }

            Iterator& operator++() {
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_next;
                }
                return *this;
            }
            Iterator& operator--() {
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_prev.lock();
                }
                return *this;
            }
            Iterator operator++(int) {
                Iterator iterator = *this;
                if (_element_ptr) {
                    _element_ptr = _element_ptr->_next;
                }
                return iterator;
            }
            Iterator operator--(int) {
                Iterator iterator = *this;
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
        , _end(nullptr)
        , _begin(nullptr) {}

        linked_list(const linked_list<T>& list)
        : _size(list._size)
        , _end(list._end)
        , _begin(list._begin) {}

        linked_list<T>::Iterator insert(const T &new_value) {
            std::shared_ptr<linked_list_node<T>> new_node = std::make_shared<linked_list_node<T>>(new_value, _end, nullptr);
    
            if (_end) {
                _end->_next = new_node;
            }
            
            _end = new_node;
    
            if (!_begin) {
                _begin = _end;
            }
            
            _size++;
    
            return linked_list<T>::Iterator(new_node);
        }

        linked_list<T>::Iterator insert(const size_t &pos, const T &new_value) {
            _size++;
            
            if (pos < _size) {
                linked_list<T>::Iterator pos_iterator = get(pos);
                std::shared_ptr<linked_list_node<T>> prev = pos_iterator._element_ptr->_prev.lock();
                std::shared_ptr<linked_list_node<T>> new_node = std::make_shared<linked_list_node<T>>(new_value, prev, pos_iterator._element_ptr);
    
                pos_iterator._element_ptr->_prev = new_node;
    
                if (prev) {
                    prev->_next = new_node;
                } else {
                    _begin = new_node;
                }
    
                return linked_list<T>::Iterator(new_node);
            } else {
                return insert(new_value);
            }
        }

        bool remove(const size_t &pos);
        bool remove(const T &value);
        void remove(linked_list<T>::Iterator &remove_iterator);

        linked_list<T>::Iterator get(const size_t &pos) {
            linked_list<T>::Iterator iterator{_begin};
            
            if (pos < _size) {
                for (size_t i = 0; i < pos; i++) {
                    ++iterator;
                }
            }
    
            return iterator;
        }

        linked_list<T>::Iterator search(const T &value) {
            linked_list<T>::Iterator iterator{_begin};
            
            while (!iterator.is_null()) {
                if (iterator._element_ptr->_value == value) {
                    break;
                } else {
                    ++iterator;
                }
            }
    
            return iterator;
        }

        linked_list<T>::Iterator begin() {
            return linked_list<T>::Iterator{_end};
        }

        linked_list<T>::Iterator end() {
            return linked_list<T>::Iterator{_begin};
        }

        size_t get_size() {
            return _size;
        }

        bool is_empty() {
            return _end == nullptr;
        }

    private:
        size_t _size;
        std::shared_ptr<linked_list_node<T>> _end;
        std::shared_ptr<linked_list_node<T>> _begin;
    };

    template <class T>
    bool linked_list<T>::remove(const size_t &pos) {
        linked_list<T>::Iterator remove_iterator = get(pos);

        if (remove_iterator._element_ptr) {
            remove(remove_iterator);

            return true;
        }

        return false;
    }

    template <class T>
    bool linked_list<T>::remove(const T &value) {
        linked_list<T>::Iterator remove_iterator = search(value);

        if (remove_iterator._element_ptr) {
            remove(remove_iterator);

            return true;
        }

        return false;
    }

    template <class T>
    void linked_list<T>::remove(linked_list<T>::Iterator &remove_iterator) {
        std::shared_ptr<linked_list_node<T>> prev = remove_iterator._element_ptr->_prev.lock();

            if (prev) {
                prev->_next = remove_iterator._element_ptr->_next;
            }

            if (remove_iterator._element_ptr->_next) {
                remove_iterator._element_ptr->_next->_prev = prev;
            }

            if (remove_iterator._element_ptr == _end) {
                _end = prev;
            }

            if (remove_iterator._element_ptr == _begin) {
                _begin = remove_iterator._element_ptr->_next;
            }

            _size--;
    }

}
#endif // LINKED_LIST_H