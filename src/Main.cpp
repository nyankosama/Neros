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
	cout << "Hello world!" <<endl;
	Strds s1("abc");
	Strds s2("de");
	int a = s1.compare(s2);
	cout << "compare:" <<a<<endl;
	s1.append("123");
	cout << s1.getContent() <<endl;
	s1.append("456");
	cout << s1.getContent() <<endl;
	s1.append(s2);
	cout << s1.getContent() <<endl;
	Strds s3 = s1.subStr(0,1);
	cout << s3.getContent() <<endl;

	ListNode<int> node;
	node.value = 1;
	ListIter<int> iter(node);

	cout << "========" << endl;

	List<int> li;

	ListNode<int> node1;
	ListNode<int> node2;
	node1.value = 1;
	node2.value = 2;
	node1.next = &node2;
	node2.prev = &node1;

	cout << "====" << endl;

	int* p1 = new int();
	int c = 1;
	int* p2 = &c;
	cout << sizeof(p1) <<endl;
	cout << sizeof(p2) << endl;
}
