/*=============================================================================
#
# Author: liangrui.hlr email:i@nyankosama.com
#
# Last modified:    2014-02-25 21:32
#
# Filename:     Main.cpp
#
# Description:
#
=============================================================================*/
#include <iostream>
#include <string>
#include <stdio.h>
#include "base/list.h"
#include "base/string_data.h"
using namespace std;
using namespace lightdis::base;



void print_mem_as_int(char* cptr, int len) {
    for (int i=0; i<len; i++) {
        cout << (int)*cptr << endl;
        cptr++;
    }
}

int main() {
    StringData data1(2);
}

