/*
 * StringData.h
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#ifndef BASE_STRING_DATA_H_
#define BASE_STRING_DATA_H_
#include <string>
#include "macro.h"
using namespace std;

namespace lightdis{
    namespace base{
        class StringData {
            public:

                /*
                 * init a StringData with 0 free and 0 length and empty string
                 */
                StringData();                

                /*
                 * init StringData with concrete text, the free length will be 0
                 */
                explicit StringData(const string& str);

                explicit StringData(const string& str, size_t len);
                
                /*
                 * notice: the string must be terminated with '\0'
                 */
                explicit StringData(const char* c);

                explicit StringData(const char* c, size_t len);

                /*
                 * init StringData with special free buffer length and empty content
                 */
                explicit StringData(size_t len);

                /*copy constructor remains*/
                StringData(const StringData& other){
                    StringData(other._data, other._len);
                }

                virtual ~StringData();

                size_t size() const{return _len;}

                int compare(const StringData& other) const;

                /*
                 *notice: if the parameter len is not passed from the caller, the append_str must be terminated with '\0'
                 */
                StringData& append(const char* append_str, size_t len = 0);
                StringData& append(const StringData& another);

                StringData subStr(size_t start_pos, size_t len = string::npos) const;

                void copyTo(char* dest, bool include_ending_null) const;

                size_t find(char c, size_t from_pos = 0) const;
                
                size_t find(const StringData& needle) const;

                size_t rfind(char c, size_t from_pos = string::npos) const;

                bool startsWith(const StringData& prefix) const;

                bool endsWith(const StringData& suffix) const;

                bool empty() const {return _len == 0; }

                bool equals(const StringData& other) const;

                string toString() const{return string(_data);}

                const char* rawData() const {return _data;}

                //iterators
                typedef const char* const_iterator;

                const_iterator begin() const {return _data; }

                const_iterator end() const {return _data + _len; }

            private:
                size_t _len;
                size_t _free;
                char* _data;
                void makeRoomForAppend(size_t required_len);
                DISALLOW_ASSIGN(StringData);
        };

    }
}

#include "base/string_data_inl.h"
#endif /* StringData_H_ */
