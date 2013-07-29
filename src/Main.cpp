//============================================================================
// Name        : Neros.cpp
// Author      : nekosama
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "data/Strds.h"
#include "data/List.h"
#include "data/List.cpp"
#include <stdio.h>
using namespace std;

class T1{
public:
	static int a;
};

int T1::a = 1;

class T2:public T1{
public:
	int b;
};


void printList(List<int>& list){
	ListIter<int> iter = list.iterator();
	cout << "list value:" << endl;
	while(iter.hasNext()){
		cout << iter.next() <<"->";
	}
	cout << endl;
}


int main() {
	cout << "========" << endl;

	List<int> list;
	ListNode<int>* n1 = new ListNode<int>();
	ListNode<int>* n2 = new ListNode<int>();
	ListNode<int>* n3 = new ListNode<int>();
	ListNode<int>* val = new ListNode<int>();
	n1->value = 1;
	n2->value = 2;
	n3->value = 3;
	val->value = 4;
	list.appendTail(n1);
	list.appendTail(n2);
	list.appendHead(n3);

	printList(list);
	ListNode<int>* tmp = list.popAt(3);
	if(tmp != 0)
		cout<<tmp->value<< endl;
	printList(list);
	ListNode<int>* node1 = list.searchKey(1);
}
