//
// Created by Links on 25-7-30.
//

#include "vector_test.h"
#include "MySTL/Vector.h"
#include "iostream"
void test(){
    Vector<int> arr;
    for(int i=0;i<10;i++)
        arr.insert(10-i);
    arr.sort();
    arr.print();
}