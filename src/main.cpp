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
#include "base/list.cpp"
#include "base/string_data.h"
using namespace std;
using namespace sdis::base;


void printList(List<int>& list){
    ListIter<int> iter = list.iterator();
    cout << "list value:" << endl;
    while(iter.hasNext()){
        cout << iter.next() <<"->";
    }
    cout << endl;
}


void print_mem_as_int(char* cptr, int len){
    for (int i=0; i<len; i++){
        cout << (int)*cptr << endl;
        cptr++;
    }
}

int main() {
    cout << "===============" << endl;
    StringData data1("123");
    data1.append("456");
    cout << data1.rawData() << endl;
    cout << "===============" << endl;
    
    StringData data2;
    data2.append("123");
    cout << data2.rawData() << endl; 
    print_mem_as_int(const_cast<char*>(data2.rawData()), 4);
    cout << "===============" << endl;

    StringData data3(5);
    data3.append("12");
    cout << data3.rawData() << endl;
    print_mem_as_int(const_cast<char*>(data3.rawData()), 5);
    cout << "===============" << endl;

    StringData data4(2);
    data4.append("1234");
    cout << data4.rawData() << endl;    
    print_mem_as_int(const_cast<char*>(data4.rawData()), 5);
    cout << "===============" << endl;

    StringData data5("123456");
    StringData sub = data5.subStr(0, 112);
    cout << sub.rawData() << endl;
    cout << "===============" << endl;
    /*
    List<int> list;
    ListNode<int>* n1 = new ListNode<int>();
    ListNode<int>* n2 = new ListNode<int>();
    ListNode<int>* n3 = new ListNode<int>();
    ListNode<int>* val = new ListNode<int>();
    n1->value = 1;
    n2->value = 2;
    n3->value = 3;
    val->value = 4;
    list.appendTail(n1);
    list.appendTail(n2);
    list.appendHead(n3);

    printList(list);
    ListNode<int>* tmp = list.popAt(3);
    if(tmp != 0)
        cout<<tmp->value<< endl;
    printList(list);
    */
}
