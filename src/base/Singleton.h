#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <stdlib.h>

namespace lightdis{
    namespace base{
        template <typename T>
        class Singleton {
            public:
                static T* val;

            public:
                static void init(){
                    val = new T();
                }

                static void destory() {
                    delete val;
                    val = NULL;
                }

                static T* get() {
                    return val;
                }  

                static void swap(T* newVal) {
                    val = newVal;
                }
        };

        template <typename T> T* Singleton<T>::val = NULL;

    }
}

#endif
