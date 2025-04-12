#ifndef RB_TREE_H
#define RB_TREE_H

#include "rb_node.h"

#ifdef RB_TREE_EXPORTS
#define RB_TREE_API __declspec(dllexport)
#else
#define RB_TREE_API __declspec(dllimport)
#endif

namespace ds {

    // Red and Black Tree
    template <class T>
    class rb_tree {
    public:
        struct ConstIterator {
            ConstIterator() = default;
            ConstIterator(const rb_node<T>* element_ptr)
            : _element_ptr(element_ptr) {}
            ConstIterator(const ConstIterator &p_other)
            : _element_ptr(p_other._element_ptr) {}

            bool is_nil() { return _element_ptr->_is_nil; }

            const int& operator*() const{ return _element_ptr->_key; }
            const int* operator->() const{ return &(_element_ptr->_key); }

            ConstIterator& operator++() { _element_ptr = _element_ptr->successor();   return *this; }
            ConstIterator& operator--() { _element_ptr = _element_ptr->predecessor(); return *this; }
            ConstIterator operator++() { rb_tree::ConstIterator old_iterator = *this; _element_ptr = _element_ptr->successor();   return old_iterator; }
            ConstIterator operator--() { rb_tree::ConstIterator old_iterator = *this; _element_ptr = _element_ptr->predecessor(); return old_iterator; }

            bool operator==(const ConstIterator& p_other) const { return _element_ptr == p_other._element_ptr; }
            bool operator!=(const ConstIterator& p_other) const { return _element_ptr != p_other._element_ptr; }

            ConstIterator& operator=(const ConstIterator& p_other) {
                if (this != &p_other) {
                    _element_ptr = p_other._element_ptr;
                }
                return *this;
            }

        private:
            const rb_node<T>* _element_ptr = nullptr;
        };

        struct Iterator {
            Iterator() = default;
            Iterator(rb_node<T>* element_ptr)
            : _element_ptr(element_ptr) {}
            Iterator(const Iterator &p_other)
            : _element_ptr(p_other._element_ptr) {}

            bool is_nil() { return _element_ptr->_is_nil; }

            const int& operator*() const { return _element_ptr->_key; }
            const int* operator->() const { return &(_element_ptr->_key); }

            Iterator& operator++() { _element_ptr = _element_ptr->successor();   return *this; }
            Iterator& operator--() { _element_ptr = _element_ptr->predecessor(); return *this; }
            Iterator operator++(int) { rb_tree::Iterator old_iterator = *this; _element_ptr = _element_ptr->successor();   return old_iterator; }
            Iterator operator--(int) { rb_tree::Iterator old_iterator = *this; _element_ptr = _element_ptr->predecessor(); return old_iterator; }

            bool operator==(const Iterator& p_other) const { return _element_ptr == p_other._element_ptr; }
            bool operator!=(const Iterator& p_other) const { return _element_ptr != p_other._element_ptr; }

            Iterator& operator=(const Iterator& p_other) {
                if (this != &p_other) {
                    _element_ptr = p_other._element_ptr;
                }
                return *this;
            }

        private:
            rb_node<T>* _element_ptr = nullptr;
        };

        rb_tree() { _nil = std::make_shared<rb_node<T>>(); _root = _nil; _size = 0; }
        rb_tree(const rb_tree<T>& tree) { _size = tree._size; _nil = tree._nil; _root = tree._root; }
        ~rb_tree() { _nil->_l = nullptr; _nil->_r = nullptr; }

        rb_tree& operator= (const rb_tree& tree) {
            if (this != &tree) {
                _size = tree._size;
                _nil = tree._nil;
                _root = tree._root;
            }
        
            return *this;
        }

        /**
         * Insert a new key
         * @parm key: the key
         * @return True if the key was not in the tree, False if not
         */
        bool insert(const T &key);

        /**
         * Remove a new key
         * @parm key: the key
         * @return True if the key was in the tree, False if not
         */
        bool remove(const T &key);

        /**
         * Search for a key
         * @parm key: the key
         * @return An iterator with the key if it is in the tree, if not, return an iterator with nil
         */
        rb_tree<T>::Iterator search(const T &key) { return rb_tree<T>::Iterator(_search(key).get()); }

        /**
         * Search for a key
         * @parm key: the key
         * @return An iterator with the key if it is in the tree, if not, return an iterator with nil
         */
        rb_tree<T>::ConstIterator search(const T &key) const { return rb_tree<T>::ConstIterator(_search(key).get()); }

        /**
         * Iterator to smallest tree's key
         * @return An iterator with the smallest key if it is in the tree, if the tree did not have any key, return an iterator with nil
         */
        rb_tree<T>::Iterator begin() { return rb_tree<T>::Iterator(_root->min()); }

        /**
         * Iterator to smallest tree's key
         * @return An iterator with the smallest key if it is in the tree, if the tree did not have any key, return an iterator with nil
         */
        rb_tree<T>::ConstIterator begin() const { return rb_tree<T>::ConstIterator(_root->min()); }

        /**
         * Iterator to end
         * @return An iterator with nil
         */
    	rb_tree<T>::Iterator end() { return rb_tree<T>::Iterator(_nil->max()); }

        /**
         * Iterator to end
         * @return An iterator with nil
         */
    	rb_tree<T>::ConstIterator end() const { return rb_tree<T>::ConstIterator(_nil->max()); }

        /**
         * Iterator to nil
         * @return An iterator with nil
         */
        rb_tree<T>::Iterator nil() { return rb_tree<T>::Iterator(_nil.get()); }

        /**
         * Iterator to nil
         * @return An iterator with nil
         */
        rb_tree<T>::ConstIterator nil() const { return rb_tree<T>::ConstIterator(_nil.get()); }

        /**
         * Get the current tree size
         * @return the num of keys in the tree
         */
        size_t get_size() { return _size; }

    protected:
        /**
         * Search for a key
         * @parm key: the key
         * @return A pointer the key if it is in the tree, if not, return a pointer to nil
         */
        std::shared_ptr<rb_node<T>> _search(const T &key) const;

        /**
         * Pointer to smallest subtree's key
         * @param node: The root subtree
         * @return A pointer with the smallest key if it is in the subtree, if the tree did not have any key, return an pointer with nil
         */
        std::shared_ptr<rb_node<T>> _min(std::shared_ptr<rb_node<T>> node) const;

        /**
         * Pointer to biggest subtree's key
         * @param node: The root subtree
         * @return A pointer with the biggest key if it is in the subtree, if the tree did not have any key, return an pointer with nil
         */
        std::shared_ptr<rb_node<T>> _max(std::shared_ptr<rb_node<T>> node) const;

    private:
        /**
         * Left rotate a subtree
         * @parm root node: the subtree's node
         */
        void left_rotation_node(const std::shared_ptr<rb_node<T>> &root_node);

        /**
         * Right rotate a subtree
         * @parm root node: the subtree's node
         */
        void right_rotation_node(const std::shared_ptr<rb_node<T>> &root_node);

        /**
         * Fixup the key insertion
         * @parm node: the new node
         */
        void insert_fixup(std::shared_ptr<rb_node<T>> node);

        /**
         * Fixup the key remotion
         * @parm node: the transplanted node
         */
        void remove_fixup(std::shared_ptr<rb_node<T>> node);

        /**
         * Change node places
         * @parm node: the node to be placed in node_trans
         * @parm node_trans: the node to be placed in node place
         */
        void transplant(std::shared_ptr<rb_node<T>> node, std::shared_ptr<rb_node<T>> node_trans);

        size_t _size;
        std::shared_ptr<rb_node<T>> _nil;
        std::shared_ptr<rb_node<T>> _root;
    };




    template <class T>
    bool rb_tree<T>::insert(const T &key) {
        std::shared_ptr<rb_node<T>> parent = _nil;
        std::shared_ptr<rb_node<T>> node = _root;

        // Find place
        while (node != _nil) {
            parent = node;

            if (key < node->_key) {
                node = node->_l;
            } else if (node->_key < key) {
                node = node->_r;
            } else {
                return false;
            }
        }


        node = std::make_shared<rb_node<T>>(key, red, _nil, _nil, parent);


        // Insert new red node
        if (parent == _nil) {
            _root = node;
        } else if (key < parent->_key) {
            parent->_l = node;
        } else {
            parent->_r = node;
        }


        insert_fixup(node);


        _size++;
        return true;
    }

    template <class T>
    bool rb_tree<T>::remove(const T &key) {
        std::shared_ptr<rb_node<T>> node = _search(key);

        if (node == _nil) {
            return false;
        } else {
            std::shared_ptr<rb_node<T>> substitute = node;
            std::shared_ptr<rb_node<T>> child = nullptr;
            bool original_substitute_color = substitute->_color;

            if (node->_l == _nil) {
                child = node->_r;
                transplant(node, child);
            } else if (node->_r == _nil) {
                child = node->_l;
                transplant(node, child);
            } else {
                substitute = _min(node->_r);
                original_substitute_color = substitute->_color;
                child = substitute->_r;

                if (substitute->_p.lock() == node) {
                    child->_p = substitute;
                } else {
                    transplant(substitute, child);
                    substitute->_r = node->_r;
                    substitute->_r->_p = substitute;
                }

                transplant(node, substitute);
                substitute->_l = node->_l;
                substitute->_l->_p = substitute;
                substitute->_color = node->_color;
            }

            if (original_substitute_color == black) {
                remove_fixup(child);
            }

            _size--;
            return true;
        }
    }

    template <class T>
    std::shared_ptr<rb_node<T>> rb_tree<T>::_search(const T &key) const {
        std::shared_ptr<rb_node<T>> node = _root;

        while (node != _nil && ((key < node->_key) || (node->_key < key))) {
            if (key < node->_key) {
                node = node->_l;
            } else {
                node = node->_r;
            }
        }

        return node;
    }

    template <class T>
    std::shared_ptr<rb_node<T>> rb_tree<T>::_min(std::shared_ptr<rb_node<T>> node) const {
        while (node->_l && node->_l != _nil) {
            node = node->_l;
        }

        return node;
    }

    template <class T>
    std::shared_ptr<rb_node<T>> rb_tree<T>::_max(std::shared_ptr<rb_node<T>> node) const {
        while (node->_r && node->_r != _nil) {
            node = node->_r;
        }

        return node;
    }

    template <class T>
    void rb_tree<T>::left_rotation_node(const std::shared_ptr<rb_node<T>> &root_node) {
        std::shared_ptr<rb_node<T>> right_node = root_node->_r;

        root_node->_r = right_node->_l;
        if (root_node->_r != _nil) {
            root_node->_r->_p = root_node;
        }

        right_node->_p = root_node->_p;
        if (right_node->_p.lock() == _nil) {
            _root = right_node;
        } else if (right_node->_p.lock()->_l == root_node) {
            right_node->_p.lock()->_l = right_node;
        } else {
            right_node->_p.lock()->_r = right_node;
        }

        right_node->_l = root_node;
        root_node->_p = right_node;
    }

    template <class T>
    void rb_tree<T>::right_rotation_node(const std::shared_ptr<rb_node<T>> &root_node) {
        std::shared_ptr<rb_node<T>> left_node = root_node->_l;

        root_node->_l = left_node->_r;
        if (root_node->_l != _nil) {
            root_node->_l->_p = root_node;
        }

        left_node->_p = root_node->_p;
        if (left_node->_p.lock() == _nil) {
            _root = left_node;
        } else if (left_node->_p.lock()->_l == root_node) {
            left_node->_p.lock()->_l = left_node;
        } else {
            left_node->_p.lock()->_r = left_node;
        }

        left_node->_l = root_node;
        root_node->_p = left_node;
    }

    template <class T>
    void rb_tree<T>::insert_fixup(std::shared_ptr<rb_node<T>> node) {
        std::shared_ptr<rb_node<T>> uncle = nullptr;
        while (node->_p.lock()->_color == red) {

            if (node->_p.lock() == node->_p.lock()->_p.lock()->_l) {
            
                uncle = node->_p.lock()->_p.lock()->_r;

                if (uncle->_color == red) {
                    node->_p.lock()->_color = black;
                    uncle->_color = black;
                    node->_p.lock()->_p.lock()->_color = red;
                    node = node->_p.lock()->_p.lock();
                } else {
                    if (node == node->_p.lock()->_r) {
                        node = node->_p.lock();
                        left_rotation_node(node);
                    }

                    node->_p.lock()->_color = black;
                    node->_p.lock()->_p.lock()->_color = red;
                    right_rotation_node(node->_p.lock()->_p.lock());
                }
            } else {
            
                uncle = node->_p.lock()->_p.lock()->_l;

                if (uncle->_color == red) {
                    node->_p.lock()->_color = black;
                    uncle->_color = black;
                    node->_p.lock()->_p.lock()->_color = red;
                    node = node->_p.lock()->_p.lock();
                } else {
                    if (node == node->_p.lock()->_l) {
                        node = node->_p.lock();
                        right_rotation_node(node);
                    }

                    node->_p.lock()->_color = black;
                    node->_p.lock()->_p.lock()->_color = red;
                    left_rotation_node(node->_p.lock()->_p.lock());
                }
            }
        }

        _root->_color = black;
    }

    template <class T>
    void rb_tree<T>::remove_fixup(std::shared_ptr<rb_node<T>> node) {
        std::shared_ptr<rb_node<T>> sibling = nullptr;

        while (node != _root && node->_color == black) {
            if (node == node->_p.lock()->_l) {
                sibling = node->_p.lock()->_r;

                if (sibling->_color == red) {
                    sibling->_color = black;
                    node->_p.lock()->_color = red;
                    left_rotation_node(node->_p.lock());
                    sibling = node->_p.lock()->_r;
                }

                if (sibling->_l->_color == black && sibling->_r->_color == black) {
                    sibling->_color = red;
                    node = node->_p.lock();
                } else {
                    if (sibling->_r->_color == black) {
                        sibling->_l->_color = black;
                        sibling->_color = red;
                        right_rotation_node(sibling);
                        sibling = node->_p.lock()->_r;
                    }

                    sibling->_color = node->_p.lock()->_color;
                    node->_p.lock()->_color = black;
                    sibling->_r->_color = black;
                    left_rotation_node(node->_p.lock());
                    node = _root;
                }
            } else {
                sibling = node->_p.lock()->_l;

                if (sibling->_color == red) {
                    sibling->_color = black;
                    node->_p.lock()->_color = red;
                    left_rotation_node(node->_p.lock());
                    sibling = node->_p.lock()->_l;
                }

                if (sibling->_r->_color == black && sibling->_l->_color == black) {
                    sibling->_color = red;
                    node = node->_p.lock();
                } else {
                    if (sibling->_l->_color == black) {
                        sibling->_r->_color = black;
                        sibling->_color = red;
                        left_rotation_node(sibling);
                        sibling = node->_p.lock()->_l;
                    }

                    sibling->_color = node->_p.lock()->_color;
                    node->_p.lock()->_color = black;
                    sibling->_l->_color = black;
                    right_rotation_node(node->_p.lock());
                    node = _root;
                }
            }
        }

        node->_color = black;
    }

    template <class T>
    void rb_tree<T>::transplant(std::shared_ptr<rb_node<T>> node, std::shared_ptr<rb_node<T>> node_trans) {
        if (node->_p.lock() == _nil) {
            _root = node_trans;
        } else if (node == node->_p.lock()->_l) {
            node->_p.lock()->_l = node_trans;
        } else {
            node->_p.lock()->_r = node_trans;
        }

        node_trans->_p = node->_p;
    }

}


#endif // RB_TREE_H