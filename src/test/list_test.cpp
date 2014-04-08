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
#include <iostream>
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
            ASSERT_EQUALS(copy.size(), 5);
        }

        TEST(LIST, POP_FRONT){
            list->popFront();
            ASSERT_EQUALS(*(list->begin()), 1);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, POP_BACK){
            list->popBack();
            ASSERT_EQUALS(*(list->rbegin()), 3);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, POP_AT){
            List<int>::iterator iter = list->begin();
            ++iter;
            list->popAt(iter);
            List<int>::iterator iter1 = list->begin();
            ++iter1;
            ASSERT_EQUALS(*iter1, 2);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, POP_AT_INDEX){
            list->popAt(1);
            List<int>::iterator iter = list->begin();
            ++iter;
            ASSERT_EQUALS(*iter, 2);
            ASSERT_EQUALS(list->size(), 4);
        }

        TEST(LIST, PUSH_BACK){
            list->pushBack(5);
            ASSERT_EQUALS(list->size(), 6);
            List<int>::iterator iter = list->rbegin();
            ASSERT_EQUALS(*iter, 5);
        }

        TEST(LIST, PUSH_FRONT){
            list->pushFront(-1);
            ASSERT_EQUALS(list->size(), 6);
            List<int>::iterator iter = list->begin();
            ASSERT_EQUALS(*iter, -1);
        }

        TEST(LIST, PUSH_AT){
            List<int>::iterator iter = list->begin();
            ++iter;
            list->pushAt(iter, 10);
            ASSERT_EQUALS(list->size(), 6);
            iter = list->begin();
            ++iter;
            ++iter;
            ASSERT_EQUALS(*iter, 10);
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
            List<int>::iterator iter = list->find(1);
            ASSERT_EQUALS(*iter, 1); 
            ++iter;
            ASSERT_EQUALS(*iter, 2);
        }

        TEST(LIST, ASSIGN){
            List<int> other;
            other = *list;
            List<int>::iterator iter = other.begin();
            ASSERT_EQUALS(*iter, 0);
            ASSERT_EQUALS(other.size(), 5);
        }
    }
}


TEST_START(LIST_TEST)







