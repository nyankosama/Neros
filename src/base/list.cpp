/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-02-26 00:49
#
# Filename:		List.cpp
#
# Description: 
#
=============================================================================*/
#include <iostream>
#include "list.h"
using namespace std;

namespace lightdis{
    namespace base{
        template<typename T>
            inline ListIter<T>::ListIter(List<T>& li) {
                lin = new ListNode<T>();
                lin->prev = 0;
                lin->next = li.getHead();
            }

        template<typename T>
            inline ListIter<T>::ListIter(ListNode<T>* lin) {
                this->lin = new ListNode<T>();
                this->lin->prev = 0;
                this->lin->next = lin;
            }

        template<typename T>
            inline ListIter<T>::~ListIter() {
            }

        template<typename T>
            inline T& ListIter<T>::val() {
                return lin->value;
            }

        template<typename T>
            inline T& ListIter<T>::next() {
                lin = lin->next;
                if (lin != 0)
                    return lin->value;
            }

        template<typename T>
            inline T& ListIter<T>::prev() {
                lin = lin->prev;
                if (lin != 0)
                    return lin->value;
            }

        template<typename T>
            inline bool ListIter<T>::hasNext() {
                if (lin->next != 0)
                    return true;
                else
                    return false;
            }

        template<typename T>
            inline bool ListIter<T>::hasPrev() {
                if (lin->prev != 0)
                    return true;
                else
                    return false;
            }

        template<typename T>
            inline List<T>::List() {
                len = 0;
                head = 0;
                tail = 0;
            }

        template<typename T>
            inline List<T>::~List() {
                delAll();
            }

        template<typename T>
            inline List<T>::List(const List<T>& list) {
                makeCopy(list);
            }

        template<typename T>
            inline List<T>& List<T>::operator =(const List<T>& li) {
                delAll();
                makeCopy(li);
                return *this;
            }

        template<typename T>
            inline int List<T>::compare(const List<T>* li) {
                ListNode<T>* iter_my = head;
                ListNode<T>* iter = li->head;

                while (iter_my->next != tail && iter->next != li->tail) {
                    if (iter_my->value != iter->value) {
                        return -1;
                    }
                }

                if (iter_my->next == tail && iter->next == li->tail) {
                    if (iter_my->next->value == iter->next->value)
                        return 0;
                    else
                        return -1;
                }
                return -1;
            }

        template<typename T>
            inline ListNode<T>* List<T>::popHead() {
                ListNode<T>* iter = head;
                head = head->next;
                if (head != 0)
                    head->prev = 0;
                len--;
                return iter;
            }

        template<typename T>
            inline ListNode<T>* List<T>::popTail() {
                ListNode<T>* iter = tail;
                tail = tail->prev;
                if (tail != 0)
                    tail->next = 0;
                len--;
                return iter;
            }

        template<typename T>
            inline ListNode<T>* List<T>::popAt(ListNode<T>* index) {
                kickOut(index);
                len--;
                return index;
            }

        template<typename T>
            inline ListNode<T>* List<T>::popAt(int index) {
                ListNode<T>* iter = head;
                for (int i = 0; i < index && iter != 0; i++) {
                    iter = iter->next;
                }
                if (iter == 0)
                    return 0;
                popAt(iter);
                return iter;
            }

        template<typename T>
            inline void List<T>::appendTail(ListNode<T>* li) {
                if (len == 0) {
                    head = li;
                    tail = li;
                    li->next = 0;
                    li->prev = 0;
                } else {
                    tail->next = li;
                    li->prev = tail;
                    tail = li;
                }
                len++;
            }

        template<typename T>
            inline void List<T>::appendHead(ListNode<T>* li) {
                if (len == 0){
                    head = li;
                    tail = li;
                    li->next = 0;
                    li->prev = 0;
                } else{
                    head->prev = li;
                    li->next = head;
                    head = li;
                }
                len++;
            }

        template<typename T>
            inline void List<T>::insert(ListNode<T>* index, ListNode<T>* val) {
                ListNode<T>* next = index->next;
                index->next = val;
                val->prev = index;
                val->next = next;
                if (next != 0)
                    next->prev = val;
                len++;
            }

        template<typename T>
            inline bool List<T>::insert(int index, ListNode<T>* val) {
                if (len == 0)
                    appendTail(val);
                ListNode<T>* iter = head;
                for (int i = 0; i < index && iter != 0; i++) {
                    iter = iter->next;
                }
                if (iter == 0)
                    return false;
                insert(iter, val);
                return true;
            }

        template<typename T>
            inline bool List<T>::del(ListNode<T>* index) {
                kickOut(index);
                delete index;
                len--;
            }

        template<typename T>
            inline bool List<T>::del(int index) {
                if (len == 0)
                    return false;
                ListNode<T>* iter = head;
                for (int i = 0; i < index; i++) {
                    iter = iter->next;
                    if (iter == 0)
                        return false;
                }
                del(iter);
                return true;
            }

        template<typename T>
            inline void List<T>::kickOut(ListNode<T>* index) {
                ListNode<T>* prev = 0;
                ListNode<T>* next = 0;
                if (index == head) {
                    next = index->next;
                    if (next != 0)
                        next->prev = 0;
                    head = next;
                } else if (index == tail) {
                    prev = index->prev;
                    if (prev != 0)
                        prev->next = 0;
                    tail = prev;
                } else {
                    prev = index->prev;
                    next = index->next;
                    prev->next = next;
                    next->prev = prev;
                }
            }

        template<typename T>
            inline ListNode<T>* List<T>::getHead() {
                return head;
            }

        template<typename T>
            inline ListNode<T>* List<T>::getTail() {
                return tail;
            }

        template<typename T>
            inline void List<T>::delAll() {
                ListNode<T>* iter = head;
                while (iter->next != 0) {
                    ListNode<T>* tmp = iter;
                    iter = iter->next;
                    delete tmp;
                }
                delete tail;
                head = 0;
                tail = 0;
                len = 0;
            }

        template<typename T>
            inline void List<T>::makeCopy(const List<T>& list) {
                len = list.len;
                head = list.head;
                if (len == 0){
                    tail = 0;
                    return;
                }
                ListNode<T>* li_iter = list.head;
                ListNode<T>* iter = 0;
                while (li_iter->next != list.tail) {
                    iter = new ListNode<T>;
                    if (iter == list.head)
                        iter->prev = 0;
                    iter->next = li_iter->next;
                    iter->next->prev = iter;
                    iter->value = li_iter->value;
                    li_iter = li_iter->next;
                    iter = iter->next;
                }
                tail = iter;
                iter->next = 0;
                iter->value = li_iter->value;
            }

        template<typename T>
            inline long List<T>::size() const {
                return len;
            }

        template<typename T>
            inline ListNode<T>* List<T>::searchKey(const T& key) {
                ListNode<T>* iter = head;
                while (iter != 0) {
                    if (iter->value == key)
                        return iter;
                    iter = iter->next;
                }
                return 0;
            }


        template<typename T>
            inline ListIter<T> List<T>::iterator() {
                return ListIter<T>(*this);
            }       
    }
}

