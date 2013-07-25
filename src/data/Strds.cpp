/*
 * Strds.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: root
 */

#include "Strds.h"
#include <string.h>

Strds::Strds() {
	free = 0;
	len = 0;
	text = new char[1];
	text[0] = '\0';
}

Strds::~Strds() {
	delete text;
}

Strds::Strds(string t){
	const char* c_str = t.c_str();
	len = strlen (c_str);
	text = new char[len * 2 + 1];
	free = len;
	strcpy(text,c_str);
}

Strds::Strds(int len){
	this->len = len;
	free = len * 2;
	text = new char[len * 2 + 1];
	text[0]='\0';
}

int Strds::size(){
	return len;
}

string Strds::getContent() const{
	return string(text);
}

void Strds::append(string app_str){
	const char* c_str = app_str.c_str();
	int required_len = strlen(c_str);
	makeRoomForAppend(required_len);
	strcat(text,c_str);
}

Strds::Strds(const Strds& s) {
	delete text;
	len = s.len;
	free = s.free;
	text = new char[len+free+1];
	strcpy(text,s.text);
}

Strds& Strds::operator =(const Strds& s) {
	delete text;
	len = s.len;
	free = s.free;
	text = new char[len+free+1];
	strcpy(text,s.text);
}

int Strds::compare(const Strds& another) {
	return strcmp(text,another.text);
}

void Strds::append(const Strds& another) {
	append(another.getContent());
}

Strds Strds::subStr(int start, int end) {
	if (end == -1)
		end = len - 1;
	char* tmp_p = text + start;
	Strds tmp(tmp_p,end-start+1);
	return tmp;
}

Strds::Strds(const char* t, int len) {
	this->len = len;
	free = len;
	text = new char[len*2 + 1];
	strncpy(text,t,len);
}

void Strds::makeRoomForAppend(int required_len){
	if (free >= required_len)
		return;

	int newlen = len + required_len;

	if (newlen < STRDS_MAX_PREALLOC)
		newlen *= 2;
	else
		newlen += STRDS_MAX_PREALLOC;

	char* tmp = new char[newlen + 1];
	strcpy(tmp,text);
	delete text;
	text = tmp;
	free = newlen - len;
}



