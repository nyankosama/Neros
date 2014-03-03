/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-02-26 00:49
#
# Filename:		List.h
#
# Description: 
#
=============================================================================*/
#ifndef BASE_LIST_H_
#define BASE_LIST_H_

namespace neros{
    namespace base{
        template <typename T> class List;
        template <typename T> class ListIter;
        template <typename T> struct ListNode;


        /**
         * ListNode can only be created by new operator!!
         * you can't create it in stack space!!!!
         */
        template <typename T>
            struct ListNode{
                struct ListNode<T>* prev;
                struct ListNode<T>* next;
                T value;
            };

        template <typename T>
            class ListIter{
                public:
                    ListIter(List<T>& li);
                    ListIter(ListNode<T>* lin);
                    virtual ~ListIter();
                    bool hasNext();
                    bool hasPrev();
                    T& val();
                    T& next();
                    T& prev();
                private:
                    ListNode<T>* lin;
            };

        template <typename T>
            class List {
                public:
                    List();
                    virtual ~List();
                    List(const List<T>& list);
                    List<T>& operator =(const List<T>& li);
                    int compare(const List<T>* li);
                    ListNode<T>* popHead();
                    ListNode<T>* popTail();
                    ListNode<T>* popAt(ListNode<T>* index);
                    ListNode<T>* popAt(int index);
                    ListNode<T>* getHead();
                    ListNode<T>* getTail();
                    void appendTail(ListNode<T>* li);//based on copy
                    void appendHead(ListNode<T>* li);
                    void insert(ListNode<T>* index,ListNode<T>* val);//insert the val at the position after index
                    bool insert(int index,ListNode<T>* val);
                    bool del(ListNode<T>* index);
                    bool del(int index);
                    void delAll();
                    long size() const;
                    ListIter<T> iterator();
                    ListNode<T>* searchKey(const T& key);

                private:
                    mutable ListNode<T>* head;
                    mutable ListNode<T>* tail;
                    unsigned long len;
                    void makeCopy(const List<T> &list);
                    void kickOut(ListNode<T>* index);
            };

    }
}

#endif /* LIST_H_ */
