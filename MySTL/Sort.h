//
// Created by Links on 2025/4/7.
//

#ifndef DSA_SORT_H
#define DSA_SORT_H

template< typename T>
void Swap(T& a,T& b){ 
    //考虑一个类型的多变量
    T c=a;
    a=b;
    b=c;
}
template< typename T>
void SortbyTrivial(T a[],int n,bool descending=1){
    //基于逆序对的设计,O(n)取决于逆序对数量，wrost_case O(n^2)
    if(descending==1){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i]<a[j])
                    Swap(a[i],a[j]);
            }
        }
    }else{
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i]>a[j])
                    Swap(a[i],a[j]);
            };
        }
    }
};
template<typename T>
void BuffleSort(T a[],int n){
    //基于冒泡排序的设计，O(n^2)
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(a[j]>a[j+1]){
                Swap(a[j],a[j+1]);
            }
        }
    }
};
template<typename T>
void cocktailSort(T arr[], int n) {
    //改进的冒泡排序（鸡尾酒排序），O(n^2)
    bool swapped = true; // 标记是否发生交换
    int start = 0;       // 起始位置
    int end = n - 1;     // 结束位置

    while (swapped) {
        swapped = false;

        // 从左到右冒泡，将最大的数移到末尾
        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                Swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // 如果没有发生交换，说明数组已经有序
        if (!swapped) break;

        // 减少结束位置，因为最后一个元素已经是最大的
        end--;

        swapped = false;

        // 从右到左冒泡，将最小的数移到开头
        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                Swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        // 增加起始位置，因为第一个元素已经是最小的
        start++;
    }
};
template<typename T>
void selectionSort(T arr[], int n) {
    //选择排序，O(n^2)
    for (int i = 0; i < n - 1; i++) {
        // 假设当前元素是最小值
        int minIndex = i;

        // 在未排序部分中找到最小值的索引
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // 如果找到的最小值不是当前元素，则交换
        if (minIndex != i) {
            Swap(arr[i], arr[minIndex]);
        }
    }
};
template<typename T>
void insertionSort(T arr[], int n) {
    //插入排序，O(n^2)
    // 从第二个元素开始（第一个元素默认已排序）
    for (int i = 1; i < n; i++) {
        T key = arr[i]; // 当前待插入的元素
        int j = i - 1;

        // 将当前元素与已排序部分的元素从后向前比较
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]; // 将较大的元素向后移动
            j--;
        }
        // 将当前元素插入到正确的位置
        arr[j + 1] = key;
    }
};
template<typename T>
void shellSort(T arr[], int n) {
    // 初始增量为数组长度的一半
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // 从 gap 开始，对每组进行插入排序
        for (int i = gap; i < n; i++) {
            T temp = arr[i]; // 当前待插入的元素
            int j = i;

            // 对当前组进行插入排序
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap]; // 元素后移
                j -= gap;
            }

            // 插入到正确位置
            arr[j] = temp;
        }
    }
}
template<typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high]; // 选择最后一个元素作为基准值
    int i = low - 1;     // i 是小于基准值的区域的最后一个索引

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]); // 将小于基准值的元素交换到左边
        }
    }

    // 将基准值放到正确的位置
    std::swap(arr[i + 1], arr[high]);
    return i + 1; // 返回基准值的最终位置
}
template<typename T>
int partition2Way(T arr[], int low, int high) {
    T pivot = arr[low]; // 选择第一个元素作为基准值
    int left = low + 1;
    int right = high;

    while (true) {
        // 从左向右找到第一个大于基准值的元素
        while (left <= right && arr[left] <= pivot) left++;

        // 从右向左找到第一个小于基准值的元素
        while (left <= right && arr[right] >= pivot) right--;

        if (left > right) break;

        // 交换左右指针的元素
        std::swap(arr[left], arr[right]);
    }

    // 将基准值放到正确位置
    std::swap(arr[low], arr[right]);
    return right;
}
template<typename T>
void partition3Way(T arr[], int low, int high, int& lt, int& gt) {
    T pivot = arr[low]; // 选择第一个元素作为基准值
    lt = low;           // lt 指向小于基准值的区域的末尾
    gt = high;          // gt 指向大于基准值的区域的开头
    int i = low + 1;    // i 用于遍历数组

    while (i <= gt) {
        if (arr[i] < pivot) {
            std::swap(arr[i], arr[lt]); // 将小于基准值的元素交换到左边
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            std::swap(arr[i], arr[gt]); // 将大于基准值的元素交换到右边
            gt--;
        } else {
            i++; // 等于基准值的元素直接跳过
        }
    }
}
template<typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        // 分区操作，返回基准值的索引
        int pi = partition(arr, low, high);

        // 对左半部分和右半部分递归排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
template<typename T>
void merge(T arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // 左子数组的大小
    int n2 = right - mid;    // 右子数组的大小

    // 创建临时数组
    T* leftArr = new T[n1];
    T* rightArr = new T[n2];

    // 拷贝数据到临时数组
    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // 合并两个临时数组到原数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // 拷贝剩余的元素
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // 释放临时数组
    delete[] leftArr;
    delete[] rightArr;
}
template<typename T>
void mergeSort(T arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // 计算中间点

        // 递归分割左半部分
        mergeSort(arr, left, mid);

        // 递归分割右半部分
        mergeSort(arr, mid + 1, right);

        // 合并两个有序部分
        merge(arr, left, mid, right);
    }
}
template<typename T>
void heapify(T arr[], int n, int i) {
    int largest = i;       // 初始化最大值为根节点
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // 如果右子节点大于当前最大值
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // 如果最大值不是根节点
    if (largest != i) {
        std::swap(arr[i], arr[largest]); // 交换根节点和最大值
        heapify(arr, n, largest);       // 递归调整子树
    }
}
template<typename T>
void heapSort(T arr[], int n) {
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 逐步将堆顶元素与末尾元素交换，并调整堆
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]); // 将堆顶元素移到数组末尾
        heapify(arr, i, 0);        // 调整剩余堆
    }
}
#include <vector>
#include <algorithm> // 用于 std::max

template<typename T>
void countingSort(T arr[], int n) {
    if (n <= 0) return;

    // 找到数组中的最大值和最小值
    T maxVal = *std::max_element(arr, arr + n);
    T minVal = *std::min_element(arr, arr + n);

    // 创建计数数组，大小为 (maxVal - minVal + 1)
    int range = maxVal - minVal + 1;
    std::vector<int> count(range, 0);

    // 统计每个元素的频率
    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }

    // 累加频率，计算每个元素的最终位置
    for (int i = 1; i < range; i++) {
        count[i] += count[i - 1];
    }

    // 构建输出数组
    std::vector<T> output(n);
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    // 将排序结果拷贝回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}
int getDigit(int number, int digitPlace) {
    return (number / digitPlace) % 10;
}
void countingSortForRadix(int arr[], int n, int digitPlace) {
    const int base = 10; // 基数为 10（十进制）
    int count[base] = {0}; // 计数数组
    int* output = new int[n]; // 输出数组

    // 统计每个数字在当前位的出现次数
    for (int i = 0; i < n; i++) {
        int digit = getDigit(arr[i], digitPlace);
        count[digit]++;
    }

    // 累加计数，计算每个数字的最终位置
    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    // 根据当前位的数字，将元素放入正确位置
    for (int i = n - 1; i >= 0; i--) {
        int digit = getDigit(arr[i], digitPlace);
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // 将排序结果拷贝回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output; // 释放动态分配的内存
}
void radixSort(int arr[], int n) {
    // 找到数组中的最大值
    int maxVal = *std::max_element(arr, arr + n);

    // 按每个位（从低位到高位）进行计数排序
    for (int digitPlace = 1; maxVal / digitPlace > 0; digitPlace *= 10) {
        countingSortForRadix(arr, n, digitPlace);
    }
}
#endif //DSA_SORT_H