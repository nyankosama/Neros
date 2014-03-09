#include <iostream>
#include "unittest/unittest.h"
#include "base/string_data.h"

using namespace std;
using namespace lightdis::base;

TEST(SUITE_CASE_1, TEST_1){
    cout << "hello unittest!" << endl;
    StringData str1("123");
    StringData str2("12");
    ASSERT_EQUALS(str1, str2);
}

TEST_START()

