/*
 * List.h
 *
 *  Created on: Jul 25, 2013
 *      Author: root
 */

#ifndef LIST_H_
#define LIST_H_
template <typename T> class List;
template <typename T> class ListIter;
template <typename T> struct ListNode;


template <typename T>
struct ListNode{
	struct ListNode<T>* prev;
	struct ListNode<T>* next;
	T value;
};

template <typename T>
class ListIter{
public:
	ListIter(const List<T>& li);
	ListIter(ListNode<T>& lin);
	virtual ~ListIter();
	T val();
	T next();
	T prev();
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
	ListNode<T>& popHead();
	ListNode<T>& popTail();
	void appendTail(ListNode<T>& li);//based on copy
	void appendHead(ListNode<T>& li);
	void insert(ListNode<T>& index,ListNode<T>& val);//insert the val at the position after index
	void insert(int index,ListNode<T>& val);
	void del(ListNode<T>& index);
	void del(int index);
	ListNode<T>& searchKey(void* key);

private:
	ListNode<T>* head;
	ListNode<T>* tail;
	unsigned long len;
};

#endif /* LIST_H_ */
