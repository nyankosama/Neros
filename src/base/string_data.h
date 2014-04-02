/*
 * BasicStringData.h
 *
 *  Created on: Jul 23, 2013
 *      Author: nekosama
 */

#ifndef BASE_STRING_DATA_H_
#define BASE_STRING_DATA_H_
#include <string>
#include <memory>
#include "macro.h"
using namespace std;

namespace lightdis{
    namespace base{
        template <class _alloc> class BasicStringData;
        typedef BasicStringData<allocator<char> > StringData;

        template <class _alloc = allocator<char> >
        class BasicStringData {
            public:

                /*
                 * init a BasicStringData with 0 free and 0 length and empty string
                 */
                BasicStringData();                

                /*
                 * init BasicStringData with concrete text, the free length will be 0
                 */
                explicit BasicStringData(const string& str);

                explicit BasicStringData(const string& str, size_t len);

                /*
                 * notice: the string must be terminated with '\0'
                 */
                explicit BasicStringData(const char* c);

                explicit BasicStringData(const char* c, size_t len);

                /*
                 * init BasicStringData with special free buffer length and empty content
                 */
                explicit BasicStringData(size_t len);

                /*copy constructor remains*/
                BasicStringData(const BasicStringData& other){
                    BasicStringData(other._data, other._len);
                }

                virtual ~BasicStringData();

                size_t size() const{return _len;}

                int compare(const BasicStringData& other) const;

                /*
                 *notice: if the parameter len is not passed from the caller, the append_str must be terminated with '\0'
                 */
                BasicStringData& append(const char* append_str, size_t len = 0);
                BasicStringData& append(const BasicStringData& another);

                BasicStringData subStr(size_t start_pos, size_t len = string::npos) const;

                void copyTo(char* dest, bool include_ending_null) const;

                size_t find(char c, size_t from_pos = 0) const;

                size_t find(const BasicStringData& needle) const;

                size_t rfind(char c, size_t from_pos = string::npos) const;

                bool startsWith(const BasicStringData& prefix) const;

                bool endsWith(const BasicStringData& suffix) const;

                bool empty() const {return _len == 0; }

                bool equals(const BasicStringData& other) const;

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
                DISALLOW_ASSIGN(BasicStringData);
        };

        template<class _alloc>
        inline bool operator==(const BasicStringData<_alloc>& lhs, const BasicStringData<_alloc>& rhs) {
            return lhs.compare(rhs) == 0;
        }

        template<class _alloc>
        inline bool operator!=(const BasicStringData<_alloc>& lhs, const BasicStringData<_alloc>& rhs) {
            return lhs.compare(rhs) != 0;
        }

        template<class _alloc>
        inline bool operator<(const BasicStringData<_alloc>& lhs, const BasicStringData<_alloc>& rhs) {
            return lhs.compare(rhs) < 0 ;
        }

        template<class _alloc>
        inline bool operator<=(const BasicStringData<_alloc>& lhs, const BasicStringData<_alloc>& rhs) {
            return lhs.compare(rhs) <= 0;
        }

        template<class _alloc>
        inline bool operator>(const BasicStringData<_alloc>& lhs, const BasicStringData<_alloc>& rhs) {
            return lhs.compare(rhs) > 0;
        }

        template<class _alloc>
        inline bool operator>=(const BasicStringData<_alloc>& lhs, const BasicStringData<_alloc>& rhs) {
            return lhs.compare(rhs) >= 0;
        }

        template<class _alloc>
        ostream& operator<< (std::ostream& stream, const BasicStringData<_alloc>& value);

    }
}

#include "base/string_data_inl.h"
#endif /* BasicStringData_H_ */
