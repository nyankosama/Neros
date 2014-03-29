/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-03-28 07:32
#
# Filename:		list.h
#
# Description: 
#
=============================================================================*/
#ifndef BASE_LIST_H_
#define BASE_LIST_H_
#include <cstdlib>
#include "macro.h"

namespace lightdis{
    namespace base{
        template <typename T> class List;
        template <typename T> class ListIter;
        template <typename T> struct ListNode;

        template <typename T>
            class ListIterator{
                public:
                    ListIterator(List<T>& li);
                    ListIterator(ListNode<T>* lin);
                    virtual ~ListIterator();
                    T& operator * ();
                    T* operator -> ();
                    ListIterator& operator ++ ();
                    ListIterator& operator -- ();
                    bool operator == (const ListIterator<T>& iter);
                    bool operator != (const ListIterator<T>& iter);

                private:
                    ListNode<T>* _lin;
                    DISALLOW_POST_OPERATOR(ListIterator);
            };

        template<typename T>
            struct ListNode{
                struct ListNode* prev;
                struct ListNode* next;
                T* value;
                T& operator * ();
            };


        template <typename T>
            class List {
                public:
                    List();
                    virtual ~List();
                    List(const List<T>& list);
                    int popFront(T& val);
                    int popBack(T& val);
                    int popAt(const ListIterator<T>& iter, T& val);
                    int popAt(size_t index, T& val);

                    //all push methods will copy the val object
                    int pushBack(const T& val);
                    int pushFront(const T& val);
                    int pushAt(const ListIterator<T>& index, const T& val);
                    int clearAll();
                    bool empty() const{return _len == 0;}

                    size_t size() const;

                    ListIterator<T> begin() const;
                    ListIterator<T> end() const;
                    ListIterator<T> find(const T& key);

                    friend class ListIterator<T>;

                private:
                    ListNode<T>* _head;
                    ListNode<T>* _tail;
                    size_t _len;
                    int remove(ListNode<T>* node);
                    T* copyT(const T* t);
                    DISALLOW_ASSIGN(List);
            };
    }
}

#endif /* LIST_H_ */
