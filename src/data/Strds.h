/*
 * Strds.h
 *
 *  Created on: Jul 23, 2013
 *      Author: root
 */

#ifndef STRDS_H_
#define STRDS_H_
#include <iostream>
#include "Constants.h"
using namespace std;

class Strds {
public:
	Strds();//init a Strds with 0 free and 0 length and empty string
	Strds(char* t);//init strds with concrete text, the free length will be 0
	Strds(int len);//init strds with special free buffer length and empty content;
	virtual ~Strds();
	int size();
	int compare(const Strds& another);
	void append(char* app_str);
	Strds subStr(int start = 0, int end = len-1);
	char* getContent();

	static Strds strds_copy(const Strds& copy_item);
private:
	int len;
	int free;
	char* text;

	void makeRoomForAppend(int required_len);
};

#endif /* STRDS_H_ */
