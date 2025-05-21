#include <iostream>
#include "MySTL/Sort.h"
#include "Test/vector_test.h"

int main(){
    {
        int a[10]={1,2,3,4,5,6,7,8,9,10};
        SortbyTrivial(a,10);
        for(int i=0;i<10;i++){
            std::cout<<a[i]<<" ";
        }
        std::cout<<std::endl;
    };
    std::cout<<"test1"<<std::endl;
    {
        int arr[10]={1,2,3,4,5,6,7,8,9,10};
        for(int i=0;i<10;i++){
            int key=arr[i],j;
            for(j=i-1;j>=0&&arr[j]>key;j--){
                arr[j+1]=arr[j];
            }
            arr[j+1]=key;
        }
        for(int i=0;i<10;i++){
            std::cout<<arr[i]<<" ";
        }
        std::cout<<std::endl;
    };
    std::cout<<"test2"<<std::endl;
    {
    int arr[10]={1,2,3,4,5,6,7,8,9,10};
    for(int i=0;i<10;i++){
        int key=arr[i],j;
        for(j=i-1;j>=0&&arr[j]>key;j--){
            arr[j+1]=arr[j];
        }
    }
    };
    std::cout<<"test3"<<std::endl;
    {
        auto add = [](int a, int b) -> int {
        return a + b;
    };

    std::cout << "Sum: " << add(3, 5) << std::endl; // 输出: Sum: 8
    };
    std::cout<<"test4"<<std::endl;
    test();
    std::cout<<"test5"<<std::endl;
    return 0;
}