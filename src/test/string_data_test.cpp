#include <string>
#include "base/string_data.h"
#include "unittest/unittest.h"

using namespace std;

namespace lightdis {
    namespace base {
        //init data
        StringData* str1 = NULL;

        SUITE_TRIGGER(STRING_DATA, BEFORE) {
            str1 = new StringData("123");
        }

        SUITE_TRIGGER(STRING_DATA, AFTER) {
            delete str1;
        }

        TEST(STRING_DATA, CONSTRUCTOR_1) {
            ASSERT_EQUALS(str1->toString(), "123");
            ASSERT_EQUALS(str1->size(), 3);
        }

        TEST(STRING_DATA, CONSTRUCTOR_2) {
            StringData str("123", 3);
            str.append("4567890");
            ASSERT_EQUALS(str.toString(), "1234567890");
        }

        TEST(STRING_DATA, CONSTRUCTOR_3) {
            const char* c = "123";
            StringData str(c);
            ASSERT_EQUALS(str.toString(), "123");
            ASSERT_EQUALS(str.size(), 3);
        }

        TEST(STRING_DATA, CONSTRUCTOR_4) {
            const char* c = "1";
            StringData str(c, 1);
            str.append("2345678");
            ASSERT_EQUALS(str.toString(), "12345678");
        }

        TEST(STRING_DATA, CONSTRUCTOR_5) {
            StringData str(1);
            str.append("123456");
            ASSERT_EQUALS(str.toString(), "123456");
        }

        TEST(STRING_DATA, COMPARE) {
            StringData str1("123");
            StringData str2("123");
            StringData str3("1234");
            ASSERT_EQUALS(str1.compare(str2), 0);
            ASSERT_NOT_EQUALS(str1.compare(str3), 0);
        }

        TEST(STRING_DATA, APPEND) {
            StringData str("123");
            str.append("456");
            ASSERT_EQUALS(str.toString(), "123456");
        }

        TEST(STRING_DATA, subStr) {
            StringData str("12345");
            StringData str1 = str.subStr(0);
            ASSERT_EQUALS(str1.toString(), str.toString());
            ASSERT_EQUALS(str.subStr(0, 2).toString(), "12");
            ASSERT_EQUALS(str.subStr(0).toString(), "12345");
            ASSERT_EQUALS(str.subStr(2).toString(), "345");
        }

        TEST(STRING_DATA, copyTo) {
            char* dest = new char[10];
            StringData str("123");
            str.copyTo(dest, true);
            ASSERT_EQUALS(string(dest), "123");
        }

        TEST(STRING_DATA, find) {
            StringData str("12345");
            ASSERT_EQUALS(str.find('1'), 0);
            ASSERT_EQUALS(str.find('1',3), string::npos);
            StringData str1("234");
            ASSERT_EQUALS(str.find(str1), 1);
            ASSERT_EQUALS(str.rfind('5'), 4);
        }

        TEST(STRING_DATA, startsWith) {
            StringData str("12345");
            ASSERT_EQUALS(str.startsWith(StringData("123")), true);
        }

        TEST(STRING_DATA, endsWith) {
            StringData str("12345");
            ASSERT_EQUALS(str.endsWith(StringData("345")), true);
        }

    }
}


TEST_START(STRING_DATA_TEST)







