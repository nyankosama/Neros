#ifndef BASE_STRING_DATA_INL_H_
#define BASE_STRING_DATA_INL_H_ 

#include <cstring>
#include "base/string_data.h"
#include "base/constants.h"

//for unittest
#include "unittest/unittest_util.h"
namespace test = lightdis::unittest;

namespace lightdis{
    namespace base{

        inline void StringData::copyTo(char* dest, bool include_ending_null) const{
            memcpy(dest, _data, _len);
            if (include_ending_null){
                dest[_len] = '\0';
            }
        }


        inline StringData& StringData::append(const char* app_str, size_t len){
            if (len == 0){
                len = strlen(app_str);
            }
            makeRoomForAppend(len);
            memcpy(_data+_len, app_str, len+1);
            _len += len;
            _free -= len;
            return *this;
        }

        inline StringData& StringData::append(const StringData& another) {
            test::echo("append string_data");
            append(another._data);
            return *this;
        }


        inline int StringData::compare(const StringData& other) const {
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

        
        inline StringData StringData::subStr(size_t start_pos, size_t len) const {
            if (len > _len){
                return StringData(_data + start_pos, _len);
            }
            else{
                return StringData(_data + start_pos, len);
            }
        }

        
        inline void StringData::makeRoomForAppend(size_t required_len){
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

#endif
