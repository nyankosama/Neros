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
#include <memory>
#include "macro.h"

namespace lightdis{
    namespace base{
        template <class T, class _alloc> class List;
        template <class T, class _alloc> class ListIter;
        template <typename T> struct ListNode;

        template <class T, class _alloc = std::allocator<T> >
            class ListIterator{
                public:
                    ListIterator();
                    ListIterator(ListNode<T>* lin);
                    virtual ~ListIterator();
                    T& operator * () const;
                    T* operator -> () const;
                    ListIterator& operator ++ ();
                    ListIterator& operator -- ();
                    bool operator == (const ListIterator<T>& iter) const;
                    bool operator != (const ListIterator<T>& iter) const;

                    friend class List<T, _alloc>;
                private:
                    ListNode<T>* _lin;
                    DISALLOW_POST_OPERATOR(ListIterator);
            };

        template<class T>
            struct ListNode{
                virtual ~ListNode<T>();
                struct ListNode* prev;
                struct ListNode* next;
                T* value;
                T& operator * ();
            };


        template <class T, class _alloc = std::allocator<T> >
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
                    int clearAll();//return the elements it removed
                    int erase(const ListIterator<T>& iter);
                    bool empty() const{return _len == 0;}

                    size_t size() const {return _len;};

                    ListIterator<T, _alloc> begin() const;
                    ListIterator<T, _alloc> end() const;
                    
                    int find(const T& key, ListIterator<T>& val);

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

#include "list_inl.h"
#endif /* LIST_H_ */
