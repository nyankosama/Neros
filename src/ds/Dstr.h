/*
 * Dstr.h
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#ifndef Dstr_H_
#define Dstr_H_
#include <iostream>
#include "Constants.h"
#include <string>
using namespace std;

class Dstr {
public:
	Dstr();//init a Dstr with 0 free and 0 length and empty string
	Dstr(string str);//init Dstr with concrete text, the free length will be 0
	Dstr(int len);//init Dstr with special free buffer length and empty content;
	Dstr(const Dstr& s);
	Dstr& operator =(const Dstr& s);
	virtual ~Dstr();
	int size();
	int compare(const Dstr& another);
	void append(string app_str);
	void append(const Dstr& another);
	Dstr subStr(int start = 0, int end = -1);
	string getContent() const;

private:
	Dstr(const char* t,int len);
	int len;
	int free;
	char* text;
	void makeRoomForAppend(int required_len);
};

#endif /* Dstr_H_ */
