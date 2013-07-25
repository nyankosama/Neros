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
using namespace std;

int main() {
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
}
