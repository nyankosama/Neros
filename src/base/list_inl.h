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
#ifndef _BASE_LIST_INL_H_
#define _BASE_LIST_INL_H_

#include <cstring>
#include "list.h"
#include "constants.h"

namespace lightdis{
    namespace base{

        template<class T, class _alloc>
            ListIterator<T, _alloc>::ListIterator(){
                _lin = NULL;
            }

        template<class T, class _alloc>
            ListIterator<T, _alloc>::ListIterator(ListNode<T>* lin) {
                /*_lin = new ListNode<T>();
                _lin->prev = lin->prev;
                _lin->next = lin->next;
                _lin->value = lin->value;*/
                _lin = lin;
            }

        template<class T, class _alloc>
            inline ListIterator<T, _alloc>::~ListIterator() {}

        template<class T, class _alloc>
            inline T& ListIterator<T, _alloc>::operator*() const{
                return *(_lin->value);
            }

        template<class T, class _alloc>
            inline T* ListIterator<T, _alloc>::operator->() const{
                return _lin;
            }

        template<class T, class _alloc>
            inline ListIterator<T, _alloc>& ListIterator<T, _alloc>::operator++(){
                _lin = _lin->next; 
                return *this;
            }

        template<class T, class _alloc>
            inline ListIterator<T, _alloc>& ListIterator<T, _alloc>::operator--(){
                _lin = _lin->prev; 
                return *this;
            }

        template<class T, class _alloc>
            bool ListIterator<T, _alloc>::operator == (const ListIterator<T>& iter) const{
                return iter._lin  == _lin;
            }

        template<class T, class _alloc>
            bool ListIterator<T, _alloc>::operator != (const ListIterator<T>& iter) const{
                return iter._lin != _lin;
            }

        template<class T>
            inline T& ListNode<T>::operator*(){
                return *value;
            }

        template<class T>
            ListNode<T>::~ListNode<T>(){
                delete value;
            }

        template<class T, class _alloc>
            List<T, _alloc>::List() {
                _len = 0;
                _head = NULL;
                _tail = NULL;
            }

        template<class T, class _alloc>
            List<T, _alloc>::~List() {
                clearAll();
            }

        template<class T, class _alloc>
            List<T, _alloc>::List(const List<T>& list) {
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


        template<class T, class _alloc>
            inline int List<T, _alloc>::popFront(T& val) {
                if (empty()){
                    return FAIL;
                }
                ListNode<T>* node = _head;
                _head = _head->next;
                if (_head != NULL)
                    _head->prev = NULL;
                _len--;
                val = *(node->value); 
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::popBack(T& val) {
                if (empty()){
                    return FAIL; 
                }
                ListNode<T>* node = _tail;
                _tail = _tail->prev;
                if (_tail != 0)
                    _tail->next = 0;
                _len--;
                val = *(node->value);
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::popAt(const ListIterator<T>& iter, T& val) {
                int ret = erase(iter);
                if (ret != SUCCESS){
                    return FAIL;
                }
                val = *iter;
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::popAt(size_t index, T& val) {
                ListIterator<int> iter = begin();
                for (int i=0; iter != end() && i < index; ++iter, i++){}
                if (iter == end())
                    return FAIL;
                popAt(iter, val);
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::pushBack(const T& val) {
                if (_len == 0) {
                    _head = new ListNode<T>();
                    _head->value = copyT(&val);
                    _tail = _head;
                    _head->next = NULL;
                    _head->prev = NULL;
                } else {
                    _tail->next = new ListNode<T>();
                    _tail->next->value = copyT(&val);
                    _tail->next->prev = _tail;
                    _tail->next->next = NULL;
                    _tail = _tail->next;
                }
                _len++;
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::pushFront(const T& val) {
                if (_len == 0){
                    _head = new ListNode<T>();
                    _head->value = copyT(&val);
                    _tail = _head;
                    _head->next = NULL;
                    _head->prev = NULL;
                } else{
                    _head->prev = new ListNode<T>();
                    _head->prev->value = copyT(&val);
                    _head->prev->next = _head;
                    _head->prev->prev = NULL;
                    _head = _head->prev;
                }
                _len++;
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::pushAt(const ListIterator<T>& index, const T& val) {
                ListNode<T>* next = index._lin->next;
                ListNode<T>* new_node = new ListNode<T>();
                new_node->value = copyT(&val);
                new_node->prev = index._lin;
                index._lin->next = new_node;
                new_node->next = next;

                if (next != NULL)
                    next->prev = new_node;
                _len++;
                return SUCCESS;
            }


        template<class T, class _alloc>
            inline int List<T, _alloc>::clearAll() {
                ListNode<T>* before = NULL;
                for (ListIterator<T> iter = begin(); iter != end();){
                    before = iter._lin;
                    ++iter;
                    delete before;
                }
                size_t size = _len;
                _len = 0;
                _head = NULL;
                _tail = NULL;
                return size;
            }

        /*
        template<class T>
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
        */
        
        //TODO 这里没有判断node是否为该list中的node，可能会错误传入其他list中的node 
        template<class T, class _alloc>
            inline int List<T, _alloc>::erase(const ListIterator<T>& iter) {
                ListNode<T>* prev = 0;
                ListNode<T>* next = 0;
                if (iter._lin == _head) {
                    next = iter._lin->next;
                    if (next != 0)
                        next->prev = 0;
                    _head = next;
                } else if (iter._lin == _tail) {
                    prev = iter._lin->prev;
                    if (prev != 0)
                        prev->next = 0;
                    _tail = prev;
                } else {
                    prev = iter._lin->prev;
                    next = iter._lin->next;
                    prev->next = next;
                    next->prev = prev;
                }
                _len--;
                //TODO 暂时没有处理异常情况
                return SUCCESS;
            }


        template<class T, class _alloc>
            inline T* List<T, _alloc>::copyT(const T* t){
                //TODO 这里sizeof是否能正确得出大小有待验证
                void* dest = malloc(sizeof(T));
                memcpy(dest, t, sizeof(T));
                return static_cast<T*>(dest);
            }



        template<class T, class _alloc>
            ListIterator<T, _alloc> List<T, _alloc>::begin() const{
                return ListIterator<T>(_head);
            }


        template<class T, class _alloc>
            ListIterator<T, _alloc> List<T, _alloc>::end() const{
                return ListIterator<T>();
            }


        template<class T, class _alloc>
            int List<T, _alloc>::find(const T& t, ListIterator<T>& val){
                for (ListIterator<T> iter = begin(); iter != end(); ++iter)            {
                    if (*iter == t){
                        val._lin = iter._lin;
                        return SUCCESS;
                    }
                }
                return FAIL;
            }
    }
}

#endif
