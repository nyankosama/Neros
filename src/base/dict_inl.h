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
    template<class Key_, class Value_, class Allocator_, class BucketAllocator_>
#define _DICT_HEAD \
    Dict<Key_, Value_, Allocator_, BucketAllocator_>

#define _VALUE_T \
    typename Dict<Key_, Value_, Allocator_, BucketAllocator_>::value_t

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
            _DICT_HEAD::~Dict(){
                clearDict(); 
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::put(const key_t& key, const value_t& value){
                size_t index = _hash(key);
                int ret = 0;
                if (_rehashidx == -1){//没有rehash
                    bucket& bc = _table[index];
                    ret = _putWithBucket(bc, key, value, false);
                }
                else{//正在进行rehash
                    bucket& bc = _rehash_table[index];
                    ret = _putWithBucket(bc, key, value, false);
                }
                return ret;
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::replace(const key_t& key, const value_t& value){
                size_t index = _hash(key);
                int ret = 0;
                if (_rehashidx == -1){//没有rehash
                    bucket& bc = _table[index];
                    ret = _putWithBucket(bc, key, value, true);
                }
                else{//正在进行rehash
                    bucket& bc = _rehash_table[index];
                    ret = _putWithBucket(bc, key, value, true);
                }
                return ret;

            }


        _DICT_TEMPLATE
            _VALUE_T _DICT_HEAD::get(const key_t& key, int& err_code){
                size_t index = _hash(key);
                int ret = 0;
                if (_rehashidx == -1){//没有rehash
                    bucket& bc = _table[index];
                    value_t& val = _getWithBucket(bc, key, ret);
                    if (ret != SUCCESS){
                        err_code = ret;
                        return NULL;
                    }
                    else{
                        return val; 
                    }
                }
                else{//正在rehash
                    //TODO not implemented
                }

            }

        _DICT_TEMPLATE
            int _DICT_HEAD::deleteKey(const key_t& key){
                size_t index = _hash(key);
                int ret = 0;
                bucket& bc = (_rehashidx == -1 ? _table[index] : _rehash_table[index]);
                ret = _eraseWithBucket(bc, key);
                return ret;
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::clearDict(){
                //TODO 竞争条件
                //TODO destroy _table
                //TODO destroy _rehash_table
            }

        _DICT_TEMPLATE 
            int _DICT_HEAD::_copyConstructNode(entry_node*& node, const key_t& key, const value_t& value){
                node = _allocator.allocate(1);
                new ((void*)&(node->key)) key_t(key);
                new ((void*)&(node->value)) value_t(value);
                return SUCCESS;
            }

        _DICT_TEMPLATE
            void _DICT_HEAD::_destroyNode(entry_node* node){
                node->key.~key_t();
                node->value.~value_t();
                _allocator.deallocate(node, 1);
            }

        _DICT_TEMPLATE
            void _DICT_HEAD::_destroyBucket(bucket* bc){
                if (bc->bucket_size == 0){
                    return;
                }
                entry_node* iter = bc->begin;   
                entry_node* before = NULL;
                for (; iter != NULL;){
                    before = iter;
                    iter = iter->next;
                    _destroyNode(before);
                }
            }

        _DICT_TEMPLATE
            size_t _DICT_HEAD::_hash(const key_t& key){
                return _key_hash(key) % _size;
            }


        _DICT_TEMPLATE
            _VALUE_T* _DICT_HEAD::_getWithBucket(const bucket& bc, const key_t& key, int& err_code){
                if (bc.begin == NULL){
                    err_code = DICT_ERR_KEY_NOT_EXISTES;
                    return NULL;
                } 
                else{
                    entry_node* iter = bc.begin;     
                    for (; iter != NULL; iter = iter->next){
                        if(iter->key == key){
                            return &(iter->value); 
                        }
                    }
                    err_code = DICT_ERR_KEY_NOT_EXISTES;
                    return NULL;
                }
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::_putWithBucket(const bucket& bc, const key_t& key, const value_t& value, bool is_replace){
                if (bc.begin == NULL){
                    _copyConstructNode(bc.begin, key, value);
                    bc.bucket_size ++;
                }
                else{
                    entry_node* iter = bc.begin; 
                    for (; iter != NULL; iter = iter->next){
                        if (iter->key == key){
                            if (is_replace){
                                iter->value = value; //这里调用赋值操作符
                                return SUCCESS;
                            }
                            else{
                                return DICT_ERR_KEY_EXISTS;
                            }
                        }

                    }
                    _copyConstructNode(iter->next, key, value);
                    bc.bucket_size ++;
                    return SUCCESS;
                }
            }

        _DICT_TEMPLATE
            int _DICT_HEAD::_eraseWithBucket(const bucket& bc, const key_t& key){
                if (bc.begin == NULL){
                    return DICT_ERR_KEY_NOT_EXISTES;
                }
                entry_node* iter = bc.begin;
                entry_node* before = NULL;
                for (; iter != NULL; iter = iter->next){
                    if (iter->key == key){
                        if (iter == bc.begin){
                            bc.begin = bc.begin->next;
                            bc.bucket_size -= 1;
                            _destroyNode(iter);
                        }
                        before = iter->next;
                        _destroyNode(iter);
                        bc.bucket_size -= 1;
                        return SUCCESS;
                    }
                    before = iter;
                }

                return DICT_ERR_KEY_NOT_EXISTES;
            }
    }
}

#endif
