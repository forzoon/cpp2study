//在一个包含 n 个元素的列表中，使用桶排序找到最大的 k 个元素的实现思路如下：
//基于最小堆的桶排序
#include <queue>
#include <vector>

std::vector<int> findTopKElementsHeap(const int arr[], int n, int k) {
    // 使用最小堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    for (int i = 0; i < n; i++) {
        if (minHeap.size() < k) {
            minHeap.push(arr[i]); // 堆大小小于 k 时直接插入
        } else if (arr[i] > minHeap.top()) {
            minHeap.pop();        // 移除堆顶最小元素
            minHeap.push(arr[i]); // 插入当前元素
        }
    }

    // 将堆中的元素存入结果数组
    std::vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }

    return result;
}


//基于快速选择算法的排序
#include <vector>
#include <algorithm>  

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // 选择最后一个元素作为基准值
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] >= pivot) { // 找第 k 大，降序排列
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSelect(int arr[], int low, int high, int k) {
    if (low < high) {
        int pi = partition(arr, low, high);

        if (pi == k) return; // 找到第 k 大元素的位置
        else if (pi < k) quickSelect(arr, pi + 1, high, k);
        else quickSelect(arr, low, pi - 1, k);
    }
}

std::vector<int> findTopKElementsQuickSelect(int arr[], int n, int k) {
    quickSelect(arr, 0, n - 1, k - 1); // 找到第 k 大元素的位置

    // 提取前 k 个最大的元素
    std::vector<int> result(arr, arr + k);
    return result;
}