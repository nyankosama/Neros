#include "base/string_data.h"
#include "unittest/unittest.h"

namespace lightdis{
    namespace base{

        TEST(STRING_DATA, CONSTRUCTOR_1){
            StringData str1("123");
            ASSERT_EQUALS(str1.toString(), "123");
            ASSERT_EQUALS(str1.size(), 3);
        } 

        TEST(STRING_DATA, CONSTRUCTOR_2){
            StringData str("123", 3);
            str.append("4567890");
            ASSERT_EQUALS(str.toString(), "1234567890");
        } 

        TEST(STRING_DATA, CONSTRUCTOR_3){
            const char* c = "123";
            StringData str(c);
            ASSERT_EQUALS(str.toString(), "123");
            ASSERT_EQUALS(str.size(), 3);
        } 

        TEST(STRING_DATA, CONSTRUCTOR_4){
            const char* c = "1";
            StringData str(c, 1);
            str.append("2345678");
            ASSERT_EQUALS(str.toString(), "12345678");
        } 

        TEST(STRING_DATA, CONSTRUCTOR_5){
            StringData str(1);
            str.append("123456");
            ASSERT_EQUALS(str.toString(), "123456");
        } 

    }
}


TEST_START()







