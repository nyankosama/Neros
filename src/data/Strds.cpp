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

Strds::Strds(char* t){
	len = strlen (t);
	text = new char[len * 2];
	free = len;
	strcpy(text,t);
}

Strds::Strds(int len){
	this->len = len;
	free = len * 2;
	text = new char[len * 2];
	text[0]='\0';
}

int Strds::size(){
	return len;
}

char* Strds::getContent(){
	return text;
}

void Strds::append(char* app_str){
	int required_len = strlen(app_str);
	makeRoomForAppend(required_len);
}

void Strds::makeRoomForAppend(int required_len){
	if (free >= required_len)
		return;

	int newlen = len + required_len;

	if (newlen < STRDS_MAX_PREALLOC)
		newlen *= 2;
	else
		newlen += STRDS_MAX_PREALLOC;

	char* tmp = new char[newlen];
	strcpy(tmp,text);
	delete text;
	text = tmp;
	free = newlen - len;
}

