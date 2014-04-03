/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-04-03 00:11
#
# Filename:		dict.h
#
# Description: 
#
=============================================================================*/
#ifndef _BASE_DICT_H_
#define _BASE_DICT_H_

#include <memory>
#include <cstdlib>
#include "base/constants.h"
#include "base/list.h"

namespace lightdis{
    namespace base{

        template <class Key_, class Value_, class Allocator_> class Dict;

        template <class Key_, class Value_> struct _DictNode{
            Key_ key;
            Value_ value;
        };

        template <class Dict_> class DictIterator{
            public:
                typedef typename Dict_::key_t key_t;
                typedef typename Dict_::value_t value_t;
                typedef DictIterator<Dict_> iterator;

                friend class Dict<key_t, value_t, typename Dict_::allocator_t>;
        };

        template <class Dict_> struct _DictHashTable{
            typedef typename Dict_::key_t key_t;
            typedef typename Dict_::value_t value_t;
            typedef _DictNode<key_t, value_t> entry_node;

            List<entry_node>* table;
            size_t size;//table指针数组的大小
            size_t used_node;//table指针数组使用的节点的数目
        };

        template <class Key_, 
                 class Value_, 
                 class Allocator_ = std::allocator<_DictNode<Key_, Value_> > > 
                     class Dict{
                         public:
                             typedef Dict<Key_, Value_, Allocator_> self_t;
                             typedef Key_ key_t;
                             typedef Value_ value_t;
                             typedef Allocator_ allocator_t;
                             typedef DictIterator<self_t> iterator;
                             typedef _DictHashTable<self_t> hash_table;


                             friend class DictIterator<self_t>;

                         public:
                             Dict(size_t index_num = DICT_DEFAULT_INDEX_NUM);
                             virtual ~Dict();
                             bool empty();
                             int put(const key_t& key, const value_t& value);
                             int get(const key_t& key, value_t& out);
                             int replace(key_t key, value_t value);
                             int deleteKey(const key_t& key, value_t& out);
                             int getRandomKey(key_t& out);
                             int clearDict();
                             int resizeAll();
                             int resizeStep(size_t step);
                             int resizeMilliseconds(size_t milliseconds);

                         private:
                             hash_table* _first_table;
                             hash_table* _second_table;
                             size_t rehashidx; //当前rehash已完成的索引号，-1表示rehash未进行
                     };

    }
}

#endif
