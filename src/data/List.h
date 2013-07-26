/*
 * List.h
 *	this is a list without commmon share nodes of other lists
 *  Created on: Jul 25, 2013
 *      Author: nekosama
 */

#ifndef LIST_H_
#define LIST_H_
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
	ListIter(const List<T>& li);
	ListIter(ListNode<T>& lin);
	virtual ~ListIter();
	inline bool hasNext();
	inline bool hasPrev();
	inline T& val();
	inline T& next();
	inline T& prev();
private:
	ListNode<T>* lin;
};

template <typename T>
class List {
public:
	inline List();
	inline virtual ~List();
	List(const List<T>& list);
	List<T>& operator =(const List<T>& li);
	int compare(const List<T>* li);
	ListNode<T>* popHead();
	ListNode<T>* popTail();
	ListNode<T>* popAt(ListNode<T>* index);
	ListNode<T>* popAt(int index);
	inline ListNode<T>* getHead();
	inline ListNode<T>* getTail();
	void appendTail(ListNode<T>* li);//based on copy
	void appendHead(ListNode<T>* li);
	void insert(ListNode<T>* index,ListNode<T>* val);//insert the val at the position after index
	bool insert(int index,ListNode<T>* val);
	void del(ListNode<T>* index);
	void del(int index);
	void delAll();
	inline long size() const;
	ListNode<T>* searchKey(const T& key);

private:
	mutable ListNode<T>* head;
	mutable ListNode<T>* tail;
	unsigned long len;
	void makeCopy(const List<T> &list);
	void kickOut(ListNode<T>* index);
};
#endif /* LIST_H_ */
