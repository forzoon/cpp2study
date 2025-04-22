#include <iostream>
#include "MySTL/Sort.h"

int main(){
    {
        int a[10]={1,2,3,4,5,6,7,8,9,10};
        SortbyTrivial(a,10);
        for(int i=0;i<10;i++){
            std::cout<<a[i]<<" ";
        }
        std::cout<<std::endl;
    }
    int arr[10]={1,2,3,4,5,6,7,8,9,10};
    for(int i=0;i<10;i++){
        int key=arr[i],j;
        for(j=i-1;j>=0&&arr[j]>key;j--){
            arr[j+1]=arr[j];
        }
    }
    return 0;
}