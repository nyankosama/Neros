/*
 * List.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: nekosama
 */

#include "List.h"

template<typename T>
inline ListIter<T>::ListIter(const List<T>& li) {
}

template<typename T>
inline ListIter<T>::ListIter(ListNode<T>& lin) {
}

template<typename T>
inline ListIter<T>::~ListIter() {
}

template<typename T>
inline T ListIter<T>::val() {
}

template<typename T>
inline T ListIter<T>::next() {
}

template<typename T>
inline T ListIter<T>::prev() {
}

template<typename T>
inline List<T>::List() {
}

template<typename T>
inline List<T>::~List() {
}

template<typename T>
inline List<T>::List(const List<T>& list) {
}

template<typename T>
inline List<T>& List<T>::operator =(const List<T>& li) {
}

template<typename T>
inline int List<T>::compare(const List<T>* li) {
}

template<typename T>
inline ListNode<T>& List<T>::popHead() {
}

template<typename T>
inline ListNode<T>& List<T>::popTail() {
}

template<typename T>
inline void List<T>::appendTail(ListNode<T>& li) {
}

template<typename T>
inline void List<T>::appendHead(ListNode<T>& li) {
}

template<typename T>
inline void List<T>::insert(ListNode<T>& index, ListNode<T>& val) {
}

template<typename T>
inline void List<T>::insert(int index, ListNode<T>& val) {
}

template<typename T>
inline void List<T>::del(ListNode<T>& index) {
}

template<typename T>
inline void List<T>::del(int index) {
}

template<typename T>
inline ListNode<T>& List<T>::searchKey(void* key) {
}
