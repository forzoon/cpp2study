#pragma once
#include "iostream"
using Rank = unsigned int; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）


template <typename T> class Vector { //向量模板类
protected:
   Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
   void copyFrom ( T const* A, Rank lo, Rank hi ); //复制数组区间A[lo, hi)
   void expand(); //空间不足时扩容
   void shrink(); //装填因子过小时压缩
   bool bubble ( Rank lo, Rank hi ); //扫描交换
   void bubbleSort ( Rank lo, Rank hi ); //起泡排序算法
   Rank maxItem ( Rank lo, Rank hi ); //选取最大元素
   void selectionSort ( Rank lo, Rank hi ); //选择排序算法
   void merge ( Rank lo, Rank mi, Rank hi ); //归并算法
   void mergeSort ( Rank lo, Rank hi ); //归并排序算法
   void heapSort ( Rank lo, Rank hi ); //堆排序（稍后结合完全堆讲解）
   Rank partition ( Rank lo, Rank hi ); //轴点构造算法
   void quickSort(); //快速排序算法
   void shellSort ( Rank lo, Rank hi ); //希尔排序算法
public:
// 构造方法
   Vector ( Rank c = DEFAULT_CAPACITY ) //容量为c的空向量
   { _elem = new T[_capacity = c]; _size = 0; }
   Vector ( Rank c, Rank s, T v ) //容量为c、规模为s、所有元素初始为v；s<=c
   { _elem = new T[_capacity = c]; for ( _size = 0; _size < s; _elem[_size++] = v ); }
   Vector ( T const* A, Rank n ) { copyFrom ( A, 0, n ); } //数组整体复制
   Vector ( T const* A, Rank lo, Rank hi ) { copyFrom ( A, lo, hi ); } //区间
   Vector ( Vector<T> const& V ) { copyFrom ( V._elem, 0, V._size ); } //向量整体复制
   Vector ( Vector<T> const& V, Rank lo, Rank hi ) { copyFrom ( V._elem, lo, hi ); } //区间
// 析构方法
   ~Vector() { delete [] _elem; } //释放内部空间
// 只读访问接口
   Rank size() const { return _size; } //规模
   bool empty() const { return !_size; } //判空
   Rank find ( T const& e ) const { return find ( e, 0, _size ); } //无序向量整体查找
   Rank find ( T const& e, Rank lo, Rank hi ) const; //无序向量区间查找
   Rank select( Rank k ) { return quickSelect( _elem, _size, k ); } //从无序向量中找到第k大的元素
   Rank search( T const& e ) const //有序向量整体查找
   { return ( 0 >= _size ) ? -1 : search ( e, 0, _size ); }
   Rank search ( T const& e, Rank lo, Rank hi ) const; //有序向量区间查找
   int disordered() const;
   void print() const; //打印向量内容
// 可写访问接口
   T& operator[] ( Rank r ); //重载下标操作符，可以类似于数组形式引用各元素
   const T& operator[] ( Rank r ) const; //仅限于做右值的重载版本
   Vector<T> & operator= ( Vector<T> const& ); //重载赋值操作符，以便直接克隆向量
   T remove ( Rank r ); //删除秩为r的元素
   Rank remove ( Rank lo, Rank hi ); //删除秩在区间[lo, hi)之内的元素
   Rank insert ( Rank r, T const& e ); //插入元素
   Rank insert ( T const& e ) { return insert ( _size, e ); } //默认作为末元素插入
   void sort ( Rank lo, Rank hi ); //对[lo, hi)排序
   void sort() { sort ( 0, _size ); } //整体排序
   void unsort ( Rank lo, Rank hi ); //对[lo, hi)置乱
   void unsort() { unsort ( 0, _size ); } //整体置乱
   Rank dedup(); //无序去重
   Rank uniquify(); //有序去重
// 遍历
   void traverse ( void (* ) ( T& ) ); //遍历（使用函数指针，只读或局部性修改）
   template <typename VST> void traverse ( VST& ); //遍历（使用函数对象，可全局性修改）
};//Vector

template<typename T>
void swap(T& a,T& b){
    T c=a;
    a=b;b=c;
}
//类函数实现
template<typename T>
void Vector<T>::print() const {
    std::cout << "Vector size: " << _size << ", capacity: " << _capacity << "\n";
    for (int i = 0; i < _size; i++) {
        std::cout << _elem[i] << " ";
    }
    std::cout << "\n";
}
template<typename T>
void Vector<T>::copyFrom(const T *A, Rank lo, Rank hi) {//复制
    //这里做一个优化，判断_capacity的取值
    _elem=new T[_capacity= 2*(hi-lo)>DEFAULT_CAPACITY?2*(hi-lo):DEFAULT_CAPACITY];
    _size=0;
    while(lo<hi)
        _elem[_size++]=A[lo++];
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V) {//重载=
    if(_elem) delete _elem;
    copyFrom(V._elem,0,V._size);
    return *this;
}

//分摊时间复杂度O(1)
template<typename T>
void Vector<T>::expand() {
    if(_size<_capacity) return;
    if(_capacity<DEFAULT_CAPACITY) _capacity=DEFAULT_CAPACITY;
    T* oldelem=_elem;
    _elem=new T[_capacity=_capacity<<1];
    for(int i=0;i<_size;i++)_elem[i]=oldelem[i];
    delete [] oldelem;
}

template<typename T>
void Vector<T>::shrink() {
    if(_capacity<DEFAULT_CAPACITY<<1) return;
    if(_size<<2>_capacity)  return;//25%界限
    T* oldelem=_elem;_elem=new T[_capacity=_capacity>>1];
    for(int i=0;i<_size;i++)_elem[i]=oldelem[i];
    delete [] oldelem;
}

template<typename T>
T& Vector<T>::operator[](Rank r) {
    return _elem[r];
}

template<typename T>
void permute(Vector<T>& V){//这个算法就是元素出现在每个位置上的概率是1/i,即为全排列的概率
    for(int i=V._size;i>0;i--)
        swap(V[i-1],V[rand()%i]);
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    T* V=_elem+lo;
    for(Rank i=hi-lo;i>0;i--)
        swap(V[i-1],V[rand()%i]);
}

template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const {
    while ((lo<hi--)&&(e!=_elem[hi]));//这里从后向前，然后hi--无论真假都会执行
    return hi;
}

template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) {
    expand();//判断是够需要扩容
    for(Rank i=_size;i>r;i--)_elem[i]=_elem[i-1];
    _elem[r]=e;_size++;
    return r;
}

template<typename T>
Rank Vector<T>::remove(Rank lo, Rank hi) {
    if(lo==hi) return 0;
    _size-=(hi-lo);
    while(hi<_size) _elem[lo++]=_elem[hi++];
    shrink();
    return hi-lo;
}

template<typename T>
T Vector<T>::remove(Rank r) {
    T e=_elem[r];
    remove(r,r+1);
    return  e;
}

template<typename T>
Rank Vector<T>::dedup() {
    int oldsize=_size,i=1;
    while(i<_size) (find(_elem[i],0,i)<0)?i++: remove(i);
    return  oldsize-_size;
}

template<typename T>
void Vector<T>::traverse(void (*func)(T &) ) {
    //遍历器
    for(int i=0;i<_size;i++)
        func(_elem[i]);
}

template<typename T>
struct Increase{//这里重载()实现自增
    virtual void operator() (T& e){
        e++;
    }
};

template<typename T>
int Vector<T>::disordered() const {
    int n=0;
    for(int i=1;i<_size;i++)
        if(_elem[i-1]>_elem[i]) n++;
    return n;//返回逆序数
}

template<typename T>
Rank Vector<T>::uniquify() {
    //第一种思路是判断删除，remove()
    //第二种思路是直接赋值
    int i=0,j=0;
    while(++j<_size)
        if(_elem[i]!=_elem[j])
            _elem[i++]=_elem[j];
    return j-i;//这里返还的是删除的元素
}

template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    return (rand()%2)?binSearch(_elem,e,lo,hi):fibSearch(_elem,e,lo,hi);
}

template<typename T>
Rank binSearch(T* _elem,T& e,Rank lo,Rank hi){
    while(lo<hi){
        Rank mi=(lo+hi)>>1;
        if(e<_elem[mi]) hi=mi;
        else if(e>_elem[mi]) lo=mi;
        else return mi;
    }
    return -1;
}

//实现一个Fib序列，然后再划分
struct Fib{
    long long operator() (int n){
        //long long时,n<93
        if(n==0) return 0;
        if(n==1) return 1;
        long long pre=0;
        long long sus=1;
        while(n-->1){
            sus=pre+sus;
            pre=sus-pre;
        }
        return sus;
    }
};

template<typename T>
Rank fibSearch(T* _elem,T& e,Rank lo,Rank hi){
    int k=0;
    Fib fib;
    while(fib(k)<hi-lo) k++;
    while(lo<hi){
        while(fib(k)>hi-lo) k--;
        Rank mi=lo+fib(k)-1;//这里的mi为fib(k)个元素
        if(_elem[mi]<e) lo=mi+1;
        else if (_elem[mi]>e) hi=mi;
        else return mi;
    }
    return -1;
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    switch (rand()%5) {
        case 1:
            bubbleSort(lo,hi);
            break;
        case 2:
            selectionSort(lo,hi);
            break;
        case 3:
            mergeSort(lo,hi);
            break;
        case 4:
            heapSort(lo,hi);
            break;
        default:
            quickSort();
            break;
    }

}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while(!bubble(lo,hi--));//相当于加入了判断机制，并没有一直循环
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted=true;
    while (++lo<hi)
        if(_elem[lo-1]>_elem[lo]){
            swap(_elem[lo-1],_elem[lo]);
            sorted= false;
        }
    return sorted;
}
template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if(hi-lo<2)return;
    int mi=(hi+lo)>>1;
    mergeSort(lo,mi);
    mergeSort(mi,hi);
    merge(lo,mi,hi);
}
template<typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A=_elem+lo;
    T* B=new T[hi-lo];
    T* C=_elem+mi;
    for(int i=0;i<hi-lo;i++) B[i]=A[i];
    for(int i=0,j=0,k=0;j<mi-lo||k<hi-mi;){
        if(j<(mi-lo)&&!(k<(hi-mi))||B[j]<=C[k]) A[i++]=B[j++];
        if(!(j<(mi-lo))&&k<(hi-mi)||B[j]>C[k]) A[i++]=C[k++];
    }
    delete [] B;
}
//实现堆排序
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
template<typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {
    T* A=_elem+lo;
    ::heapSort(A,hi-lo);
}
