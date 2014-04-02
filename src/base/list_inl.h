/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-04-02 02:53
#
# Filename:		list_inl.h
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

        template<class _List>
            ListIterator<_List>::ListIterator(){
                _lin = NULL;
            }

        template<class _List>
            ListIterator<_List>::ListIterator(node_t* lin) {
                _lin = lin;
            }

        template<class _List>
            inline ListIterator<_List>::~ListIterator() {}

        template<class _List>
            inline typename ListIterator<_List>::value_type& ListIterator<_List>::operator*() const{
                return *(_lin->value);
            }

        template<class _List>
            inline typename ListIterator<_List>::value_type* ListIterator<_List>::operator->() const{
                return _lin;
            }

        template<class _List>
            inline ListIterator<_List>& ListIterator<_List>::operator++(){
                _lin = _lin->next; 
                return *this;
            }

        template<class _List>
            inline ListIterator<_List>& ListIterator<_List>::operator--(){
                _lin = _lin->prev; 
                return *this;
            }

        template<class _List>
            bool ListIterator<_List>::operator == (const iterator& iter) const{
                return iter._lin  == _lin;
            }

        template<class _List>
            bool ListIterator<_List>::operator != (const iterator& iter) const{
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
            List<T, _alloc>::List(const List<value_type>& list) {
                _len = list._len;
                node_t* before = NULL;
                node_t* current = NULL;

                for (iterator iter = list.begin(); iter != list.end(); ++iter){
                    if (iter == list.begin()){
                        current = new node_t();
                        current->value = copyT(iter._lin->value);
                        current->prev = NULL;
                        _head = current;
                        before = current;
                        continue;
                    }
                    else if (iter == list.end()){
                        current = new node_t();
                        current->value = copyT(iter._lin->value);
                        current->prev = before;
                        current->prev->next = current;
                        current->next = NULL;
                        _tail = current;
                        continue;
                    }

                    current = new node_t();
                    current->value = copyT(iter._lin->value);
                    current->prev = before;
                    current->prev->next = current;
                    before = current;
                }
            }


        template<class T, class _alloc>
            inline int List<T, _alloc>::popFront(value_type& val) {
                if (empty()){
                    return FAIL;
                }
                node_t* node = _head;
                _head = _head->next;
                if (_head != NULL)
                    _head->prev = NULL;
                _len--;
                val = *(node->value); 
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::popBack(value_type& val) {
                if (empty()){
                    return FAIL; 
                }
                node_t* node = _tail;
                _tail = _tail->prev;
                if (_tail != 0)
                    _tail->next = 0;
                _len--;
                val = *(node->value);
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::popAt(const iterator& iter, T& val) {
                int ret = erase(iter);
                if (ret != SUCCESS){
                    return FAIL;
                }
                val = *iter;
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::popAt(size_t index, value_type& val) {
                iterator iter = begin();
                for (int i=0; iter != end() && i < index; ++iter, i++){}
                if (iter == end())
                    return FAIL;
                popAt(iter, val);
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::pushBack(const value_type& val) {
                if (_len == 0) {
                    _head = new node_t();
                    _head->value = copyT(&val);
                    _tail = _head;
                    _head->next = NULL;
                    _head->prev = NULL;
                } else {
                    _tail->next = new node_t();
                    _tail->next->value = copyT(&val);
                    _tail->next->prev = _tail;
                    _tail->next->next = NULL;
                    _tail = _tail->next;
                }
                _len++;
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::pushFront(const value_type& val) {
                if (_len == 0){
                    _head = new node_t();
                    _head->value = copyT(&val);
                    _tail = _head;
                    _head->next = NULL;
                    _head->prev = NULL;
                } else{
                    _head->prev = new node_t();
                    _head->prev->value = copyT(&val);
                    _head->prev->next = _head;
                    _head->prev->prev = NULL;
                    _head = _head->prev;
                }
                _len++;
                return SUCCESS;
            }

        template<class T, class _alloc>
            inline int List<T, _alloc>::pushAt(const iterator& index, const value_type& val) {
                node_t* next = index._lin->next;
                node_t* new_node = new node_t();
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
                node_t* before = NULL;
                for (iterator iter = begin(); iter != end();){
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
            inline int List<T, _alloc>::erase(const iterator& iter) {
                node_t* prev = 0;
                node_t* next = 0;
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
            inline T* List<T, _alloc>::copyT(const value_type* t){
                //TODO 这里sizeof是否能正确得出大小有待验证
                void* dest = malloc(sizeof(value_type));
                memcpy(dest, t, sizeof(value_type));
                return static_cast<value_type*>(dest);
            }



        template<class T, class _alloc>
            typename List<T, _alloc>::iterator List<T, _alloc>::begin() const{
                return iterator(_head);
            }


        template<class T, class _alloc>
            typename List<T, _alloc>::iterator List<T, _alloc>::end() const{
                return iterator();
            }


        template<class T, class _alloc>
            int List<T, _alloc>::find(const value_type& t, iterator& val){
                for (iterator iter = begin(); iter != end(); ++iter)            {
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