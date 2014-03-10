#ifndef BASE_STRING_DATA_INL_H_
#define BASE_STRING_DATA_INL_H_ 

#include <cstring>
#include <string>
#include "base/string_data.h"
#include "base/constants.h"


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
            if (len > _len || len == string::npos){
                return StringData(_data + start_pos, _len - start_pos);
            }
            else{
                if (len > _len - start_pos)
                    len = _len - start_pos;
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

        inline size_t StringData::find(char c, size_t from_pos) const {
            if (from_pos >= _len){
                return string::npos;
            }

            const void* x = memchr(_data + from_pos, c, _len - from_pos);
            if (x == NULL){
                return string::npos;
            }

            return static_cast<size_t>( static_cast<const char*>(x) - _data);
        }


        inline size_t StringData::find(const StringData& needle) const{
            size_t mx = _len;
            size_t needle_size = needle.size();

            if (needle_size == 0){
                return 0;
            }
            else if (needle_size > mx){
                return string::npos;
            }

            mx -= needle_size;

            //TODO performance problem, string find algorithm can be replaced with KMP
            for (size_t i = 0; i <= mx; i++){
                if (memcmp(_data + i, needle._data, needle_size) == 0){
                    return i;
                }
            }
            return string::npos;
        }

        inline size_t StringData::rfind(char c, size_t from_pos) const{
            if (from_pos >= _len){
                from_pos = _len;
            }

            for ( const char* cur = _data + from_pos; cur > _data; --cur ) {
                if ( *(cur - 1) == c )
                    return (cur - _data) - 1;
            }
            return string::npos;
        }

        inline bool StringData::equals(const StringData& other) const{
            if (compare(other) == 0)
                return true;
            else
                return false;
        }

        inline bool StringData::startsWith(const StringData& prefix) const{
            return subStr(0, prefix.size()).equals(prefix);
        }

        inline bool StringData::endsWith(const StringData& suffix) const{
            const size_t this_size = _len;
            const size_t suffix_size = suffix.size();
            if (suffix_size > this_size){
                return false;
            }
            return subStr(this_size - suffix_size).equals(suffix);
        }

    }
}

#endif
