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

#include "base/dict.h"

namespace lightdis{
    namespace base{

        template<class Dict_>
            _DictHashTable<Dict_>::_DictHashTable(int table_size){
                   
            }
       
        template<class Key_, class Value_, class Allocator_>
            Dict<Key_, Value_, Allocator_>::Dict(size_t index_num){
                _rehashidx = -1;                

            }

    }
}

#endif
