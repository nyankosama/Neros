/*
 * StringData.h
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#ifndef StringData_H_
#define StringData_H_
#include <iostream>
#include <string>
#include "constants.h"
#include "macro.h"
using namespace std;

namespace neros{
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

                explicit StringData(const char* c);

                explicit StringData(const char* c, size_t len);

                /*
                 * init StringData with special free buffer length and empty content
                 */
                StringData(size_t len);
                virtual ~StringData();
                size_t size();
                int compare(const StringData& another);
                void append(const string& append_str);
                void append(const StringData& another);
                StringData subStr(size_t start_pos = 0, size_t end_pos = -1);
                string getContent() const;

            private:
                size_t _len;
                size_t _free;
                char* _data;
                void makeRoomForAppend(size_t required_len);
                DISALLOW_COPY_AND_ASSIGN(StringData); 
        };

    }
}

#endif /* StringData_H_ */
