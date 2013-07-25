/*
 * Strds.h
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#ifndef STRDS_H_
#define STRDS_H_
#include <iostream>
#include "Constants.h"
#include <string>
using namespace std;

class Strds {
public:
	Strds();//init a Strds with 0 free and 0 length and empty string
	Strds(string str);//init strds with concrete text, the free length will be 0
	Strds(int len);//init strds with special free buffer length and empty content;
	Strds(const Strds& s);
	Strds& operator =(const Strds& s);
	virtual ~Strds();
	int size();
	int compare(const Strds& another);
	void append(string app_str);
	void append(const Strds& another);
	Strds subStr(int start = 0, int end = -1);
	string getContent() const;

private:
	Strds(const char* t,int len);
	int len;
	int free;
	char* text;
	void makeRoomForAppend(int required_len);
};

#endif /* STRDS_H_ */
