/*
 * StringData.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#include <iostream>
#include <cstring>
#include <algorithm>
#include "constants.h"
#include "string_data.h"

//for unittest
#include "unittest/unittest_util.h"
namespace test = lightdis::unittest;

namespace lightdis{
    namespace base{
        StringData::StringData() {
            test::echo("none-para constru");
            _free = 0;
            _len = 0;
            _data = new char[1];
            _data[0] = '\0';
        }

        StringData::~StringData() {
            delete _data;
        }

        StringData::StringData(const char* c){
            test::echo("char* c constru");
            _len = strlen(c);
            _data = new char[_len*2 + 1];
            _free = _len;
            memcpy(_data, c, _len+1);
            _data[_len] = '\0';
        }
        
        StringData::StringData(const char* c, size_t len) {
            test::echo("char* t, size_t len constru");
            this->_len = len;
            _free = len;
            _data = new char[len*2 + 1]; 
            memcpy(_data, c, _len+1);
            _data[_len] = '\0';
        }

        StringData::StringData(const string& c){
            test::echo("string& t constru");
            const char* c_str = c.c_str();
            _len = strlen (c_str);
            _data = new char[_len * 2 + 1];
            _free = _len;
            memcpy(_data, c_str, _len+1);
            _data[_len] = '\0';
        }

        StringData::StringData(size_t free){
            test::echo("size_t len constru");
            this->_len = 0;
            _free = free;
            _data = new char[free + 1];
            _data[0]='\0';
        }

        size_t StringData::size() const{
            return _len;
        }

        string StringData::toString() const{
            return string(_data);
        }

        StringData& StringData::append(const char* app_str, size_t len){
            if (len == 0){
                len = strlen(app_str);
            }
            makeRoomForAppend(len);
            memcpy(_data+_len, app_str, len+1);
            _len += len;
            _free -= len;
            return *this;
        }

        StringData& StringData::append(const StringData& another) {
            test::echo("append string_data");
            append(another._data);
            return *this;
        }


        int StringData::compare(const StringData& other) const {
            int res = memcmp(_data, other._data, std::min(_len, other._len));
            if (res != 0){
                return res > 0 ? 1 : -1;
            }
            else if(_len == other._len){
                return 0;
            }
            else {
                return _len > other._len ? 1 : -1;
            }
        }

        
        StringData StringData::subStr(size_t start_pos, size_t len) const {
            if (len > _len){
                return StringData(_data + start_pos, _len);
            }
            else{
                return StringData(_data + start_pos, len);
            }
        }

        
        void StringData::makeRoomForAppend(size_t required_len){
            if (_free >= required_len)
                return;

            size_t newlen = _len + required_len;

            if (newlen < STRING_DATA_MAX_PREALLOC)
                newlen *= 2;
            else
                newlen += STRING_DATA_MAX_PREALLOC;

            char* tmp = new char[newlen + 1];
            memcpy(tmp, _data, _len+1);
            delete _data;
            _data = tmp;
            _free = newlen - _len;
        }       
    }
}   
