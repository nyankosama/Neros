/*=============================================================================
  iter._lin->value#
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

#define _LIST_TEMPLATE \
    template<class T, class Allocator_>
#define _LIST_HEAD \
    List<T, Allocator_>

#define _ITER_TEMPLATE \
    template<class List_>
#define _ITER_HEAD \
    ListIterator<List_>

#define _NODE_TEMPLATE \
    template<class T>
#define _NODE_HEAD \
    ListNode<T>

#define _VALUE_T \
    typename List<T, Allocator_>::value_type
#define _ITER_T \
    typename List<T, Allocator_>::iterator



#include <cstring>
#include "base/list.h"

namespace lightdis {
    namespace base {

        _ITER_TEMPLATE
        _ITER_HEAD::ListIterator() {
            _lin = NULL;
        }

        _ITER_TEMPLATE
        _ITER_HEAD::ListIterator(node_t* lin) {
            _lin = lin;
        }

        _ITER_TEMPLATE
        inline _ITER_HEAD::~ListIterator() {}

        _ITER_TEMPLATE
        inline typename _ITER_HEAD::value_type& _ITER_HEAD::operator*() const {
            return _lin->value;
        }

        _ITER_TEMPLATE
        inline typename _ITER_HEAD::value_type* _ITER_HEAD::operator->() const {
            return _lin;
        }

        _ITER_TEMPLATE
        inline _ITER_HEAD& _ITER_HEAD::operator++() {
            _lin = _lin->next;
            return *this;
        }

        _ITER_TEMPLATE
        inline _ITER_HEAD& _ITER_HEAD::operator--() {
            _lin = _lin->prev;
            return *this;
        }

        _ITER_TEMPLATE
        bool _ITER_HEAD::operator == (const iterator& iter) const {
            return iter._lin  == _lin;
        }

        _ITER_TEMPLATE
        bool _ITER_HEAD::operator != (const iterator& iter) const {
            return iter._lin != _lin;
        }

        _NODE_TEMPLATE
        inline T& _NODE_HEAD::operator*() {
            return value;
        }


        _LIST_TEMPLATE
        _LIST_HEAD::List():_allocator(allocator_t()) {
            _len = 0;
            _head = NULL;
            _tail = NULL;
        }

        _LIST_TEMPLATE
        _LIST_HEAD::~List() {
            clearAll();
        }

        _LIST_TEMPLATE
        _LIST_HEAD::List(const List<value_type>& list) {
            _copyList(list);
        }


        _LIST_TEMPLATE
        inline int _LIST_HEAD::popFront() {
            if (empty()) {
                return FAIL;
            }
            return erase(begin());
        }

        _LIST_TEMPLATE
        inline int _LIST_HEAD::popBack() {
            if (empty()) {
                return FAIL;
            }
            return erase(rbegin());
        }

        _LIST_TEMPLATE
        inline int _LIST_HEAD::popAt(const iterator& iter) {
            return erase(iter);
        }

        _LIST_TEMPLATE
        inline int _LIST_HEAD::popAt(size_t index) {
            iterator iter = begin();
            for (int i=0; iter != end() && i < index; ++iter, i++) {}
            if (iter == end())
                return FAIL;
            return popAt(iter);
        }

        _LIST_TEMPLATE
        inline void _LIST_HEAD::pushBack(const value_type& val) {
            if (_len == 0) {
                _head = _createNode(val);
                _tail = _head;
                _head->next = NULL;
                _head->prev = NULL;
            } else {
                _tail->next = _createNode(val);
                _tail->next->prev = _tail;
                _tail->next->next = NULL;
                _tail = _tail->next;
            }
            _len++;
        }

        _LIST_TEMPLATE
        inline void _LIST_HEAD::pushFront(const value_type& val) {
            if (_len == 0) {
                _head = _createNode(val);
                _tail = _head;
                _head->next = NULL;
                _head->prev = NULL;
            } else {
                _head->prev = _createNode(val);
                _head->prev->next = _head;
                _head->prev->prev = NULL;
                _head = _head->prev;
            }
            _len++;
        }

        _LIST_TEMPLATE
        inline void _LIST_HEAD::pushAt(const iterator& index, const value_type& val) {
            node_t* next = index._lin->next;
            node_t* new_node = _createNode(val);
            new_node->prev = index._lin;
            index._lin->next = new_node;
            new_node->next = next;

            if (next != NULL)
                next->prev = new_node;
            _len++;
        }


        _LIST_TEMPLATE
        inline int _LIST_HEAD::clearAll() {
            node_t* before = NULL;
            for (iterator iter = begin(); iter != end();) {
                before = iter._lin;
                ++iter;
                _destroyNode(before);
            }
            size_t size = _len;
            _len = 0;
            _head = NULL;
            _tail = NULL;
            return size;
        }


        //TODO 这里没有判断node是否为该list中的node，可能会错误传入其他list中的node
        _LIST_TEMPLATE
        inline int _LIST_HEAD::erase(const iterator& iter) {
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
            _destroyNode(iter._lin);
            return SUCCESS;
            //TODO 暂时没有处理异常情况
        }

        /*
           _LIST_TEMPLATE
           inline T* _LIST_HEAD::copyT(const value_type* t){
        //TODO 这里sizeof是否能正确得出大小有待验证
        void* dest = malloc(sizeof(value_type));
        memcpy(dest, t, sizeof(value_type));
        return static_cast<value_type*>(dest);
        }*/

        _LIST_TEMPLATE
        inline typename _LIST_HEAD::node_t* _LIST_HEAD::_createNode(const value_type& value) {
            node_t* ptr = _allocator.allocate(1);
            new ((void*)(&(ptr->value))) value_type(value);
            return ptr;
        }

        _LIST_TEMPLATE
        inline void _LIST_HEAD::_destroyNode(node_t* node) {
            node->value.~value_type();
            node->value.~value_type();
            _allocator.deallocate(node, 1);
        }


        _LIST_TEMPLATE
        typename _LIST_HEAD::iterator _LIST_HEAD::begin() const {
            return iterator(_head);
        }


        _LIST_TEMPLATE
        typename _LIST_HEAD::iterator _LIST_HEAD::end() const {
            return iterator();
        }

        _LIST_TEMPLATE
        typename _LIST_HEAD::iterator _LIST_HEAD::rbegin() const {
            return iterator(_tail);
        }


        _LIST_TEMPLATE
        typename _LIST_HEAD::iterator _LIST_HEAD::rend() const {
            return iterator();
        }



        _LIST_TEMPLATE
        _ITER_T _LIST_HEAD::find(const value_type& t, int& err_code) {
            for (iterator iter = begin(); iter != end(); ++iter)            {
                if (*iter == t) {
                    return _ITER_T(iter._lin);
                }
            }
            err_code = FAIL;
            return NULL;
        }

        _LIST_TEMPLATE
        void _LIST_HEAD::_copyList(const self_t& list) {
            _len = list._len;
            node_t* before = NULL;
            node_t* current = NULL;

            for (iterator iter = list.begin(); iter != list.end(); ++iter) {
                if (iter == list.begin()) {
                    current = _createNode(iter._lin->value);
                    current->prev = NULL;
                    _head = current;
                    before = current;
                    continue;
                } else if (iter == list.rbegin()) {
                    current = _createNode(iter._lin->value);
                    current->prev = before;
                    current->prev->next = current;
                    current->next = NULL;
                    _tail = current;
                    continue;
                }

                current = _createNode(iter._lin->value);
                current->prev = before;
                current->prev->next = current;
                before = current;

            }
        }

        _LIST_TEMPLATE
        void _LIST_HEAD::operator= (const self_t& r_list) {
            clearAll();
            _copyList(r_list);
        }
    }
}

#endif
