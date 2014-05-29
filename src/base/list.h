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
#include "base/macro.h"
#include "base/constants.h"

namespace lightdis {
    namespace base {
        template <class T, class Allocator_> class List;

        template<class T>
        struct ListNode {
            virtual ~ListNode<T>();
            struct ListNode* prev;
            struct ListNode* next;
            T value;
            T& operator * ();
        };

        template <class _List>
        class ListIterator {
        public:
            typedef typename _List::value_type value_type;
            typedef typename _List::node_t node_t;
            typedef ListIterator<_List> iterator;

            friend class List<value_type, typename _List::allocator_t>;

        private:
            node_t* _lin;
            DISALLOW_POST_OPERATOR(ListIterator);

        public:
            ListIterator();
            ListIterator(node_t* lin);
            virtual ~ListIterator();
            value_type& operator * () const;
            value_type* operator -> () const;
            ListIterator& operator ++ ();
            ListIterator& operator -- ();
            bool operator == (const iterator& iter) const;
            bool operator != (const iterator& iter) const;

        };


//TODO 需要const iterator的实现
        template <class T, class Allocator_ = std::allocator<ListNode<T> > >
        class List {
        public:
            typedef List<T, Allocator_> self_t;
            typedef T value_type;
            typedef Allocator_ allocator_t;
            typedef ListIterator<self_t> iterator;
            typedef ListNode<value_type> node_t;


            friend class ListIterator<self_t>;

        private:
            node_t* _head;
            node_t* _tail;
            size_t _len;
            allocator_t _allocator;

        public:
            List();
            virtual ~List();
            List(const List<value_type>& list);
            int popFront();
            int popBack();
            int popAt(const iterator& iter);
            int popAt(size_t index);

            //all push methods will copy the val object
            void pushBack(const value_type& val);
            void pushFront(const value_type& val);
            void pushAt(const iterator& index, const value_type& val);
            int clearAll();//return the elements it removed
            int erase(const iterator& iter);
            bool empty() const {
                return _len == 0;
            }

            size_t size() const {
                return _len;
            };

            iterator begin() const;
            iterator end() const;
            iterator rbegin() const;
            iterator rend() const;

            iterator find(const value_type& key, int& err_code = ERR_REF);

            void operator=(const self_t& r_list);

        private:
            void _copyList(const self_t& list);
            node_t* _createNode(const value_type& value);
            void _destroyNode(node_t* node);
        };

    }
}

#include "list_inl.h"
#endif /* LIST_H_ */



