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

#include "base/dict.h"

namespace lightdis{
    namespace base{

        _DICT_TEMPLATE
            _DICT_HEAD::Dict(size_t table_size){
                //TODO 这里依赖于编译器会给Bucket类中的bucket_size初始化为0
                _table = _bucket_allocator.allocate(table_size);
                _size = table_size;
                _used_node = 0;
                _rehashidx = -1;                
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::put(const key_t& key, const value_t& value){
                size_t index = _key_hash(key) % _size;
                int ret = 0;
                if (_rehashidx == -1){//没有rehash
                    bucket& bc = _table[index];
                    ret = _putWithBucket(bc, key, value);
                }
                else{//正在进行rehash
                    bucket& bc = _rehash_table[index];
                    ret = _putWithBucket(bc, key, value);
                }
                return ret;
            }

        _DICT_TEMPLATE 
            int _DICT_HEAD::_copyConstructNode(entry_node*& node, const key_t& key, const value_t& value){
                node = _allocator.allocate(1);
                new ((void*)&(node->key)) key_t(key);
                new ((void*)&(node->value)) value_t(value);
                return SUCCESS;
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::get(const key_t& key, value_t& out){
                size_t index = _key_hash(key) % _size;
                if (_rehashidx == -1){
                    
                }

            }

        _DICT_TEMPLATE
        int _DICT_HEAD::_getWithBucket(const bucket& bc, const key_t& key, value_t& out){
            if (bc.begin == NULL){
                return DICT_ERR_KEY_NOT_EXISTES;
            } 
            else{
                entry_node* iter = bc.begin;     
            }
        }

        _DICT_TEMPLATE
            int _DICT_HEAD::_putWithBucket(const bucket& bc, const key_t& key, const value_t& value){
                if (bc.begin == NULL){
                    _copyConstructNode(bc.begin, key, value);
                    bc.bucket_size ++;
                }
                else{
                    entry_node* iter = bc.begin; 
                    do{
                        if (iter->key == key){
                            return DICT_ERR_KEY_EXISTS;
                        }
                    }
                    while (iter->next != NULL);
                    _copyConstructNode(iter->next, key, value);
                    bc.bucket_size ++;
                    return SUCCESS;
                }
            }

        _DICT_TEMPLATE
            entry_node* _DICT_HEAD::findWithKey(const key_t& key){

            }
    }
}

#endif
