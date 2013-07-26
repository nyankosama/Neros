/*
 * List.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: nekosama
 */

#include "List.h"

template<typename T>
inline ListIter<T>::ListIter(const List<T>& li) {
	lin = &li.getHead();
}

template<typename T>
inline ListIter<T>::ListIter(ListNode<T>& lin) {
	this->lin = &lin;
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
inline int List<T>::compare(const List<T>& li) {
	ListNode<T>* iter_my = head;
	ListNode<T>* iter = li.head;

	while (iter_my->next != tail && iter->next != li.tail) {
		if (iter_my->value != iter->value) {
			return -1;
		}
	}

	if (iter_my->next == tail && iter->next == li.tail) {
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
	head->prev = 0;
	return iter;
}

template<typename T>
inline ListNode<T>* List<T>::popTail() {
	ListNode<T>* iter = tail;
	tail = tail->prev;
	tail->next = 0;
	return iter;
}

template<typename T>
inline ListNode<T>* List<T>::popAt(ListNode<T>& index) {
	kickOut(index);
	return &index;
}

template<typename T>
inline ListNode<T>* List<T>::popAt(int index) {
	ListNode<T>* iter = head;
	for (int i = 0; i < index; i++) {
		iter = iter->next;
	}
	popAt(*iter);
}

template<typename T>
inline void List<T>::appendTail(ListNode<T>& li) {
	ListNode<T>* iter = tail;
	tail->next = &li;
	li.prev = iter;
}

template<typename T>
inline void List<T>::appendHead(ListNode<T>& li) {
	ListNode<T>* iter = head;
	head->prev = &li;
	li.next = iter;
}

template<typename T>
inline void List<T>::insert(ListNode<T>& index, ListNode<T>& val) {
	ListNode<T>* next = index.next;
	index.next = &val;
	val.prev = &index;
	val.next = next;
	next->prev = &val;
}

template<typename T>
inline void List<T>::insert(int index, ListNode<T>& val) {
	ListNode<T>* iter = head;
	for (int i = 0; i < index; i++) {
		iter = iter->next;
	}
	insert(iter, val);
}

template<typename T>
inline void List<T>::del(ListNode<T>& index) {
	kickOut(index);
	delete &index;
}

template<typename T>
inline void List<T>::del(int index) {
	ListNode<T>* iter = head;
	for (int i = 0; i < index; i++) {
		iter = iter->next;
	}
	del(*iter);
}

template<typename T>
inline void List<T>::kickOut(ListNode<T>& index) {
	ListNode<T>* prev = 0;
	ListNode<T>* next = 0;
	if (&index == head) {
		next = index->next;
		next->prev = 0;
	} else if (&index == tail) {
		prev = index->prev;
		prev->next = 0;
	} else {
		prev = index.prev;
		next = index.next;
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
	while (iter->next != tail) {
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
