#ifndef BASE_STRING_DATA_INL_H_
#define BASE_STRING_DATA_INL_H_ 

#include <cstring>
#include "base/string_data.h"

namespace lightdis{
    namespace base{

        inline void StringData::copyTo(char* dest, bool include_ending_null) const{
            memcpy(dest, _data, _len);
            if (include_ending_null){
                dest[_len] = '\0';
            }
        }

    }
}

#endif
