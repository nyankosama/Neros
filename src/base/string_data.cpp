/*
 * StringData.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#include "string_data.h"
#include <string.h>

namespace neros{
    namespace base{
        StringData::StringData() {
            _free = 0;
            _len = 0;
            _data = new char[1];
            _data[0] = '\0';
        }

        StringData::~StringData() {
            delete _data;
        }

        StringData::StringData(const char* c){
            _len = strlen(c);
            _data = new char[_len*2 + 1];
            _free = _len;
            strcpy(_data, c);
        }

        StringData::StringData(const string& t){
            const char* c_str = t.c_str();
            _len = strlen (c_str);
            _data = new char[_len * 2 + 1];
            _free = _len;
            strcpy(_data,c_str);
        }

        StringData::StringData(size_t len){
            this->_len = len;
            _free = len * 2;
            _data = new char[len * 2 + 1];
            _data[0]='\0';
        }

        size_t StringData::size(){
            return _len;
        }

        string StringData::getContent() const{
            return string(_data);
        }

        void StringData::append(const string& app_str){
            const char* c_str = app_str.c_str();
            int required_len = strlen(c_str);
            makeRoomForAppend(required_len);
            strcat(_data,c_str);
        }

        int StringData::compare(const StringData& another) {
            return strcmp(_data,another._data);
        }

        void StringData::append(const StringData& another) {
            append(another.getContent());
        }

        StringData StringData::subStr(size_t start_pos, size_t end_pos) {
            char* tmp_p = _data + start_pos;
            StringData tmp(tmp_p,end_pos-start_pos+1);
            return tmp;
        }

        StringData::StringData(const char* t, size_t len) {
            this->_len = len;
            _free = len;
            _data = new char[len*2 + 1]; strncpy(_data,t,len);
        }

        void StringData::makeRoomForAppend(size_t required_len){
            if (_free >= required_len)
                return;

            int newlen = _len + required_len;

            if (newlen < STRING_DATA_MAX_PREALLOC)
                newlen *= 2;
            else
                newlen += STRING_DATA_MAX_PREALLOC;

            char* tmp = new char[newlen + 1];
            strcpy(tmp,_data);
            delete _data;
            _data = tmp;
            _free = newlen - _len;
        }       
    }
}   
