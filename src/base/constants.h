/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:	2014-02-26 00:18
#
# Filename:		Constants.h
#
# Description: 
#
=============================================================================*/
#ifndef BASE_CONSTRANT_H_
#define BASE_CONSTRANT_H_

#define SUCCESS 0
#define FAIL -1

//======dict.h======
#define DICT_DEFAULT_INDEX_NUM 5

//error code
#define DICT_ERR_KEY_EXISTS 1 //键已存在，无法插入
#define DICT_ERR_KEY_NOT_EXISTES 2 //键不存在

//======dict.h end======

namespace lightdis{
    namespace base{

        const int DEFAULT_FREE_LEN = 20;
        const int STRING_DATA_MAX_PREALLOC = 1024 * 1024;

    }
}

#endif /* CONSTRANT_H_ */
