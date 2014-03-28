#include <string>
#include "unittest/unittest.h"
#include "base/list.h"
#include "base/list.cpp"

using namespace std;

namespace lightdis{
    namespace base{

        TEST(LIST, COMPILE){
            List<int> list;
            ListNode<int>* node = new ListNode<int>();
            node->value = 1;
            list.appendTail(node);
            cout << list.popTail()->value << endl;
        }
    }
}


TEST_START()







