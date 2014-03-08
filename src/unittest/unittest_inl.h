#include "unittest/unittest.h"
#include <iostream>

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
    }
}

