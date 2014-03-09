/*
 * StringData.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#include <iostream>
#include <cstring>
#include <algorithm>
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

        ostream& operator<<(std::ostream& stream, const StringData& value) {
            return stream.write(value.rawData(), value.size());
        }
    }
}   
