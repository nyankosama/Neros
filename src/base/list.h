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
        struct ListNode;

        template <typename T>
            class ListIterator{
                public:
                    ListIterator(List<T>& li);
                    ListIterator(ListNode* lin);
                    virtual ~ListIterator();
                    T& operator * ();
                    T& operator -> ();
                    ListIterator& operator ++ ();
                    ListIterator& operator -- ();

                private:
                    ListNode* _lin;
                    DISALLOW_POST_OPERATOR(ListIterator);
            };


        template <typename T>
            class List {
                public:
                    List();
                    virtual ~List();
                    List(const List<T>& list);
                    T* popFront();
                    T* popBack();
                    T* popAt(ListIterator<T>& iter);
                    T* popAt(size_t index);

                    void pushBack(const T& val);
                    void pushFront(const T& val);
                    void pushAt(const ListIterator<T>& index, const T& val);
                    void clearAll();

                    int compare(const List<T>* li);
                    size_t size() const;

                    ListIterator<T> begin() const;
                    ListIterator<T> end() const;
                    ListIterator<T> find(const T& key);

                protected:
                    struct ListNode{
                        struct ListNode* prev;
                        struct ListNode* next;
                        T value;
                    };

                private:
                    ListNode* _head;
                    ListNode* _tail;
                    size_t _len;
                    void remove(ListNode* node);
                    DISALLOW_ASSIGN(List);
            };
    }
}

#endif /* LIST_H_ */
