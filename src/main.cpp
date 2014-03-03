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
using namespace neros::base;


void printList(List<int>& list){
    ListIter<int> iter = list.iterator();
    cout << "list value:" << endl;
    while(iter.hasNext()){
        cout << iter.next() <<"->";
    }
    cout << endl;
}


int main() {
    cout << "===============" << endl;
    StringData data("123");
    data.append("456");
    cout << data.getContent() << endl;
    cout << "===============" << endl;
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
}