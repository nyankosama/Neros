/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-03-28 07:34
#
# Filename:		list.cpp
#
# Description: 
#
=============================================================================*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "list.h"
#include "constants.h"
using namespace std;

namespace lightdis{
    namespace base{
        template<typename T>
            ListIterator<T>::ListIterator(List<T>& li) {
                _lin = new ListNode<T>();
                _lin = li._head;
            }

        template<typename T>
            ListIterator<T>::ListIterator(ListNode<T>* lin) {
                _lin = new ListNode<T>();
                _lin->prev = lin->prev;
                _lin->next = lin->next;
            }

        template<typename T>
            inline ListIterator<T>::~ListIterator() {}

        template<typename T>
            inline T& ListIterator<T>::operator*() {
                return *_lin;
            }

        template<typename T>
            inline T* ListIterator<T>::operator->(){
                return _lin;
            }

        template<typename T>
            inline ListIterator<T>& ListIterator<T>::operator++(){
                _lin = _lin->next; 
                return *this;
            }

        template<typename T>
            inline ListIterator<T>& ListIterator<T>::operator--(){
                _lin = _lin->prev; 
                return *this;
            }

        template<typename T>
            bool ListIterator<T>::operator == (const ListIterator<T>& iter){
                return iter._lin  == _lin;
            }

        template<typename T>
            bool ListIterator<T>::operator != (const ListIterator<T>& iter){
                return iter._lin != _lin;
            }

        template<typename T>
            inline T& ListNode<T>::operator*(){
                return *value;
            }

        template<typename T>
            List<T>::List() {
                _len = 0;
                _head = NULL;
                _tail = NULL;
            }

        template<typename T>
            List<T>::~List() {
                clearAll();
            }

        template<typename T>
            List<T>::List(const List<T>& list) {
                _len = list._len;
                ListNode<T>* before = NULL;
                ListNode<T>* current = NULL;

                for (ListIterator<T> iter = list.begin(); iter != list.end(); ++iter){
                    if (iter == list.begin()){
                        current = new ListNode<T>();
                        current->value = copyT(iter._lin->value);
                        current->prev = NULL;
                        _head = current;
                        before = current;
                        continue;
                    }
                    else if (iter == list.end()){
                        current = new ListNode<T>();
                        current->value = copyT(iter._lin->value);
                        current->prev = before;
                        current->prev->next = current;
                        current->next = NULL;
                        _tail = current;
                        continue;
                    }

                    current = new ListNode<T>();
                    current->value = copyT(iter._lin->value);
                    current->prev = before;
                    current->prev->next = current;
                    before = current;
                }
            }


        template<typename T>
            inline int List<T>::popFront(T& val) {
                if (empty()){
                    return FAIL;
                }
                ListNode<T>* node = _head;
                _head = _head->next;
                if (_head != NULL)
                    _head->prev = NULL;
                _len--;
                val = node->value; 
                return SUCCESS;
            }

        template<typename T>
            inline int List<T>::popBack(T& val) {
                if (empty()){
                    return FAIL; 
                }
                ListNode<T>* node = _tail;
                _tail = _tail->prev;
                if (_tail != 0)
                    _tail->next = 0;
                _len--;
                val = node->value;
                return SUCCESS;
            }

        template<typename T>
            inline int List<T>::popAt(const ListIterator<T>& iter, T& val) {
                int ret = remove(iter._lin);
                if (ret != SUCCESS){
                    return FAIL;
                }
                _len--;
                val = *iter;
                return SUCCESS;
            }

        template<typename T>
            inline int List<T>::popAt(size_t index, T& val) {
                ListNode<T>* node = _head;
                for (int i = 0; i < index && node != NULL; i++) {
                    node = node->next;
                }
                if (node == NULL)
                    return FAIL;
                popAt(node);
                val = node->value;
                return SUCCESS;
            }

        template<typename T>
            inline int List<T>::pushBack(const T& val) {
                if (_len == 0) {
                    _head = new ListNode<T>();
                    _head->value = val;
                    _tail = _head;
                    _head->next = NULL;
                    _head->prev = NULL;
                } else {
                    _tail->next = new ListNode<T>();
                    _tail->next->value = val;
                    _tail->next->prev = _tail;
                    _tail->next->next = NULL;
                    _tail = _tail->next;
                }
                _len++;
                return SUCCESS;
            }

        template<typename T>
            inline int List<T>::pushFront(const T& val) {
                if (_len == 0){
                    _head = new ListNode<T>();
                    _head->value = val;
                    _tail = _head;
                    _head->next = NULL;
                    _head->prev = NULL;
                } else{
                    _head->prev = new ListNode<T>();
                    _head->prev->value = val;
                    _head->prev->next = _head;
                    _head->prev->prev = NULL;
                    _head = _head->prev;
                }
                _len++;
                return SUCCESS;
            }

        template<typename T>
            inline int List<T>::pushAt(ListNode<T>* index, const T& val) {
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
                remove(index);
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
        
        //TODO 这里没有判断node是否为该list中的node，可能会错误传入其他list中的node 
        template<typename T>
            inline int List<T>::remove(ListNode<T>* node) {
                ListNode<T>* prev = 0;
                ListNode<T>* next = 0;
                if (node == head) {
                    next = node->next;
                    if (next != 0)
                        next->prev = 0;
                    head = next;
                } else if (node == tail) {
                    prev = node->prev;
                    if (prev != 0)
                        prev->next = 0;
                    tail = prev;
                } else {
                    prev = node->prev;
                    next = node->next;
                    prev->next = next;
                    next->prev = prev;
                }
                //TODO 暂时没有处理异常情况
                return SUCCESS;
            }

        template<typename T>
            inline T* List<T>::copyT(const T* t){
                //TODO 这里sizeof是否能正确得出大小有待验证
                void* dest = malloc(sizeof(T));
                memcpy(dest, t, sizeof(T));
                return static_cast<T*>(dest);
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
            inline ListIterator<T> List<T>::iterator() {
                return ListIterator<T>(*this);
            }       
    }
}

