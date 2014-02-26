/*
 * Dstr.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#include "Dstr.h"
#include <string.h>

Dstr::Dstr() {
	free = 0;
	len = 0;
	text = new char[1];
	text[0] = '\0';
}

Dstr::~Dstr() {
	delete text;
}

Dstr::Dstr(string t){
	const char* c_str = t.c_str();
	len = strlen (c_str);
	text = new char[len * 2 + 1];
	free = len;
	strcpy(text,c_str);
}

Dstr::Dstr(int len){
	this->len = len;
	free = len * 2;
	text = new char[len * 2 + 1];
	text[0]='\0';
}

int Dstr::size(){
	return len;
}

string Dstr::getContent() const{
	return string(text);
}

void Dstr::append(string app_str){
	const char* c_str = app_str.c_str();
	int required_len = strlen(c_str);
	makeRoomForAppend(required_len);
	strcat(text,c_str);
}

Dstr::Dstr(const Dstr& s) {
	cout << "copy constructor!" <<endl;
	delete text;
	len = s.len;
	free = s.free;
	text = new char[len+free+1];
	strcpy(text,s.text);
}

Dstr& Dstr::operator =(const Dstr& s) {
	delete text;
	len = s.len;
	free = s.free;
	text = new char[len+free+1];
	strcpy(text,s.text);
    return *this;
}

int Dstr::compare(const Dstr& another) {
	return strcmp(text,another.text);
}

void Dstr::append(const Dstr& another) {
	append(another.getContent());
}

Dstr Dstr::subStr(int start, int end) {
	if (end == -1)
		end = len - 1;
	char* tmp_p = text + start;
	Dstr tmp(tmp_p,end-start+1);
	return tmp;
}

Dstr::Dstr(const char* t, int len) {
	this->len = len;
	free = len;
	text = new char[len*2 + 1];
	strncpy(text,t,len);
}

void Dstr::makeRoomForAppend(int required_len){
	if (free >= required_len)
		return;

	int newlen = len + required_len;

	if (newlen < DSTR_MAX_PREALLOC)
		newlen *= 2;
	else
		newlen += DSTR_MAX_PREALLOC;

	char* tmp = new char[newlen + 1];
	strcpy(tmp,text);
	delete text;
	text = tmp;
	free = newlen - len;
}



