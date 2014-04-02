/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified: 2014-04-02 02:53
#
# Filename: list_test.cpp
#
# Description: 
#
=============================================================================*/
#include <string>
#include "unittest/unittest.h"
#include "base/list.h"

using namespace std;

namespace lightdis{
    namespace base{

        List<int>* list = NULL;

        SUITE_TRIGGER(LIST, BEFORE){
            list = new List<int>();
            for (int i =0; i<5; i++){
                list->pushBack(i);
            }
        }

        SUITE_TRIGGER(LIST, AFTER){
            delete list;
        }


        TEST(LIST, COPY_CONSTRUCTOR){
            List<int> copy(*list);
            int ele = *(copy.begin());
            ASSERT_EQUALS(ele, 0);
        }

        TEST(LIST, POP_FRONT){
            int a = 5;
            list->popFront(a);
            ASSERT_EQUALS(a, 0);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, POP_BACK){
            int a = 0;
            list->popBack(a);
            ASSERT_EQUALS(a, 4);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, POP_AT){
            int a = 0;
            List<int>::iterator iter = list->begin();
            ++iter;
            list->popAt(iter, a);
            ASSERT_EQUALS(a, 1);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, POP_AT_INDEX){
            int a = 0;
            list->popAt(1, a);
            ASSERT_EQUALS(a, 1);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, PUSH_BACK){
            list->pushBack(5);
            ASSERT_EQUALS(list->size(), 6);
            int a = 0;
            list->popAt(5, a);
            ASSERT_EQUALS(a, 5);
        }

        TEST(LIST, PUSH_FRONT){
            list->pushFront(-1);
            ASSERT_EQUALS(list->size(), 6);
            int a = 0;
            list->popAt(0, a);
            ASSERT_EQUALS(a, -1);
        }

        TEST(LIST, PUSH_AT){
            List<int>::iterator iter = list->begin();
            ++iter;
            list->pushAt(iter, 10);
            ASSERT_EQUALS(list->size(), 6);
            int a = 0;
            ++iter;
            list->popAt(iter, a);
            ASSERT_EQUALS(a, 10);
        }

        TEST(LIST, CLEAR_ALL){
            list->clearAll();
            ASSERT_EQUALS(list->size(), 0);
        }

        TEST(LIST, ERASE){
            List<int>::iterator iter = list->begin();
            list->erase(iter);
            ASSERT_EQUALS(list->size(), 4);
            List<int>::iterator iter1 = list->begin();
            ASSERT_EQUALS(*iter1, 1);
        }

        TEST(LIST, EMPTY){
            ASSERT_EQUALS(list->empty(), false);
            list->clearAll();
            ASSERT_EQUALS(list->empty(), true);
        }

        TEST(LIST, FIND){
            List<int>::iterator iter;
            int ret = list->find(1, iter);
            ASSERT_EQUALS(*iter, 1); 
            ASSERT_EQUALS(ret, 0);
        }
    }
}


TEST_START(LIST_TEST)







