/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-04-04 02:34
#
# Filename:		dict_inl.h
#
# Description: 
#
=============================================================================*/
#ifndef _BASE_DICT_INL_H_
#define _BASE_DICT_INL_H_

#define _DICT_TEMPLATE \
    template<class Key_, class Value_, class Allocator_, class PtrAllocator_>
#define _DICT_HEAD \
    Dict<Key_, Value_, Allocator_, PtrAllocator_>

#define _HASH_TABLE_TEMPLATE \
    template<class Dict_>
#define _HASH_TABLE_HEAD \
    _DictHashTable<Dict_>

#include "base/dict.h"

namespace lightdis{
    namespace base{

        _HASH_TABLE_TEMPLATE
            _HASH_TABLE_HEAD::_DictHashTable(int table_size){
                //TODO 这里依赖于编译器会给Bucket类中的bucket_size初始化为0
                init(table_size);
            }

        _HASH_TABLE_TEMPLATE
            int _HASH_TABLE_HEAD::init(int table_size){
                _table = _bucket_allocator.allocate(table_size);
                _size = table_size;
                _used_node = 0;
            }

        _DICT_TEMPLATE
            _DICT_HEAD::Dict(size_t table_size){
                _rehashidx = -1;                
                _table.init(table_size);
            }
    }
}

#endif
