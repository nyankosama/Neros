/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-04-02 02:53
#
# Filename:		list.h
#
# Description: 
#
=============================================================================*/
#ifndef BASE_LIST_H_
#define BASE_LIST_H_
#include <cstdlib>
#include <memory>
#include "macro.h"

namespace lightdis{
    namespace base{
        template <class T, class Allocator> class List;
        
        template<class T>
            struct ListNode{
                virtual ~ListNode<T>();
                struct ListNode* prev;
                struct ListNode* next;
                T* value;
                T& operator * ();
            };

        template <class _List>
            class ListIterator{
                public:
                    typedef typename _List::value_type value_type;
                    typedef typename _List::node_t node_t;
                    typedef ListIterator<_List> iterator;

                    ListIterator();
                    ListIterator(node_t* lin);
                    virtual ~ListIterator();
                    value_type& operator * () const;
                    value_type* operator -> () const;
                    ListIterator& operator ++ ();
                    ListIterator& operator -- ();
                    bool operator == (const iterator& iter) const;
                    bool operator != (const iterator& iter) const;

                    friend class List<value_type, typename _List::allocator_t>;
                private:
                    node_t* _lin;
                    DISALLOW_POST_OPERATOR(ListIterator);
            };

        
        //TODO 需要const iterator的实现
        template <class T, class Allocator = std::allocator<T> >
            class List {
                public:
                    typedef List<T, Allocator> self_t;
                    typedef T value_type;
                    typedef Allocator allocator_t;
                    typedef ListIterator<self_t> iterator;
                    typedef ListNode<value_type> node_t;

                    List();
                    virtual ~List();
                    List(const List<value_type>& list);
                    int popFront(value_type& val);
                    int popBack(value_type& val);
                    int popAt(const iterator& iter, value_type& val);
                    int popAt(size_t index, value_type& val);

                    //all push methods will copy the val object
                    int pushBack(const value_type& val);
                    int pushFront(const value_type& val);
                    int pushAt(const iterator& index, const value_type& val);
                    int clearAll();//return the elements it removed
                    int erase(const iterator& iter);
                    bool empty() const{return _len == 0;}

                    size_t size() const {return _len;};

                    iterator begin() const;
                    iterator end() const;
                    
                    int find(const value_type& key, iterator& val);

                    friend class ListIterator<self_t>;

                private:
                    node_t* _head;
                    node_t* _tail;
                    size_t _len;
                    int remove(node_t* node);
                    value_type* copyT(const value_type* t);
                    allocator_t allocator;
                    DISALLOW_ASSIGN(List);
            };
    }
}

#include "list_inl.h"
#endif /* LIST_H_ */
