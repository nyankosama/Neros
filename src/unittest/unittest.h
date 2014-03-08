#ifndef UNITEST_UNITTEST_H_
#define UNITEST_UNITTEST_H_

#include <string>
#include <vector>
#include <iostream>

#include "base/Singleton.h"
using namespace std;

#define TEST_START() \
    int main(){ \
        ::lightdis::unittest::SuiteManager::get()->run();\
    }
    
#define TEST(SUITE_NAME, TEST_NAME) \
    class _TEST_TYPE_NAME(SUITE_NAME, TEST_NAME) : public ::lightdis::unittest::TestHolder{ \
        public:                                        \
            _TEST_TYPE_NAME(SUITE_NAME, TEST_NAME)(const string& name) : ::lightdis::unittest::TestHolder(name){}                       \
            virtual void doTest();                      \
            static const RegistrationAgent<_TEST_TYPE_NAME(SUITE_NAME, TEST_NAME)> _agent; \
    };\
    const lightdis::unittest::TestHolder::RegistrationAgent<_TEST_TYPE_NAME(SUITE_NAME, TEST_NAME)> _TEST_TYPE_NAME(SUITE_NAME, TEST_NAME)::_agent(#SUITE_NAME, #TEST_NAME);\
    void _TEST_TYPE_NAME(SUITE_NAME, TEST_NAME)::doTest()


#define _TEST_TYPE_NAME(SUITE_NAME, TEST_NAME) UnitTest_##SUITE_NAME##_##TEST_NAME




namespace lightdis{
    namespace unittest{

        class TestHolder{
            public:
                TestHolder(const string& name):testName(name){}
                virtual void doTest() = 0;
            private:
                string testName;

            protected:
                template <typename T>
                class RegistrationAgent{
                    public:
                        RegistrationAgent(const string& suite_name, const string& test_name);
                };
        };


        class SuiteHolder{
            public:
                SuiteHolder(const string& name):_suite_name(name){}
                virtual void before(){}
                virtual void after(){}
                virtual void setup(){}
                virtual void tearDown(){}

                void registeTestHolder(TestHolder* holder);
                void run();
                string getName(){return _suite_name;}
            private:
                string _suite_name;
                vector<TestHolder*> _test_holder_list;
        };


        class SuiteManager{
            public:
                SuiteHolder& getSuiteHolder(const string& suite_name);
                void run();
                static SuiteManager* get(){return _instance;}

            private:
                vector<SuiteHolder*> _suite_holder_list;
                static SuiteManager* _instance;
        };

        SuiteManager* SuiteManager::_instance = new SuiteManager();

    }
}

#include "unittest/unittest_inl.h"
#endif
