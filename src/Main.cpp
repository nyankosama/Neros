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



int main() {
	cout << "========" << endl;

	List<int> list;
	ListNode<int>* n1 = new ListNode<int>();
	ListNode<int>* n2 = new ListNode<int>();
	n1->value = 1;
	n2->value = 2;
	list.appendTail(n1);
	list.appendTail(n2);
	cout << "Hello world" << endl;
	cout << list.size() << endl;
	list.delAll();
	cout << list.size() << endl;
}
