#include "unittest/unittest.h"
#include <iostream>
#include <sstream>

using namespace std;

namespace lightdis{
    namespace unittest{

        template <typename T>
        TestHolder::RegistrationAgent<T>::RegistrationAgent(const string& suite_name,const string& test_name) {
            T* testObj = new T(test_name);
            SuiteManager::get()->getSuiteHolder(suite_name).registeTestHolder(testObj);
        }       

        void SuiteHolder::registeTestHolder(TestHolder* holder){
            _test_holder_list.push_back(holder);
        }

        void SuiteHolder::run(){
            for(vector<TestHolder*>::iterator iter = _test_holder_list.begin(); iter != _test_holder_list.end(); ++iter){
                (*iter)->doTest();
            }
        }

        SuiteHolder& SuiteManager::getSuiteHolder(const string& suite_name){
            SuiteHolder* holder = NULL;
            for (vector<SuiteHolder*>::iterator iter = _suite_holder_list.begin(); iter != _suite_holder_list.end(); ++iter){
                if ((*iter)->getName() == suite_name){
                    holder = *iter;
                    break;
                }
            }
            if (holder == NULL){
                holder = new SuiteHolder(suite_name);
                _suite_holder_list.push_back(holder);
            }
            return *holder;
        }

        void SuiteManager::run(){
            for (vector<SuiteHolder*>::iterator iter = _suite_holder_list.begin(); iter != _suite_holder_list.end(); ++iter){
                (*iter)->run();
            }
        }

        void TestAssertion::fail(const string& msg){
            cout << "Assertion fail at line=" << _line << ", file=" << _file
                << ", msg=" << msg;
             
            cout << endl;
        }

        template<typename A, typename B>
        string ComparisonAssertion::getFailMessage(const string& operation, A& a, B& b){
            ostringstream os;
            os << "Expected " << _aexp << " " << operation << " " << _bexp
                << " (" << a << " " << operation << " " << b << ")";
            return os.str();
        }        
    }
}

