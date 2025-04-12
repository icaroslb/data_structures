#ifndef RB_NODE_H
#define RB_NODE_H

#include <memory>

#ifdef RB_NODE_EXPORTS
#define RB_NODE_API __declspec(dllexport)
#else
#define RB_NODE_API __declspec(dllimport)
#endif

namespace ds {

    const bool black = false;
    const bool red = true;
    
    template <class T>
    struct rb_node {
        /**
         * Initialized a NIL node
        */
        rb_node()
        : _color(black)
        , _is_nil(true)
        , _l(nullptr)
        , _r(nullptr)
        {}
    
        /**
         * Initialized a node
        */
        rb_node(T key, bool color, std::shared_ptr<rb_node> l, std::shared_ptr<rb_node> r, std::weak_ptr<rb_node> p)
        : _key(key)
        , _is_nil(false)
        , _color(color)
        , _l(l)
        , _r(r)
        , _p(p)
        {}
    
        bool is_nil() {
            return _is_nil;
        }
    
        T _key;
    
    protected:
        rb_node* successor() const {
            const rb_node* node = this;
        
            if (!node->_r->_is_nil) {
                return node->_r->min();
            } else {
                rb_node* parent = node->_p.lock().get();
            
                while (!parent->_is_nil && parent->_r.get() == node) {
                    node = parent;
                    parent = node->_p.lock().get();
                }
            
                return parent;
            }
        }
    
        rb_node* predecessor() const {
            const rb_node* node = this;
            
            if (!node->_l->_is_nil) {
                return node->_l->max();
            } else {
                rb_node* parent = node->_p.lock().get();
            
                while (!parent->_is_nil && parent->_l.get() == node) {
                    node = parent;
                    parent = node->_p.lock().get();
                }
            
                return parent;
            }
        }
    
        rb_node* min() {
            rb_node* node = this;
            
            while (node->_l && !node->_l->_is_nil) {
                node = node->_l.get();
            }
        
            return node;
        }
    
        rb_node* max() {
            rb_node* node = this;
        
            while (node->_r && !node->_r->_is_nil) {
                node = node->_r.get();
            }
        
            return node;
        }
    
        bool _color;
        bool _is_nil;
    
        std::shared_ptr<rb_node<T>> _l; // left
        std::shared_ptr<rb_node<T>> _r; // right
        std::weak_ptr<rb_node<T>> _p; // parent
    
        template <class U> friend class rb_tree;
    };

}

#endif // RB_NODE_H