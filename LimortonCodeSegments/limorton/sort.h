#ifndef LIMORTON_SORT_H_INCLUDED
#define LIMORTON_SORT_H_INCLUDED
#include <iostream>
#include <random>
//#define NDEBUG
#include <assert.h>
//#include <vector>
#ifndef INF
#define INF 1
const int INF_MAX = 0x3f3f3f3f;
const int INF_MIX = -0X3f3f3f3f;
#endif // INF
enum sort_comp{
    smaller = 0,
    bigger = 1
};
/*****************插入排序 ************************/
/** \brief
 *    插入排序-int数组
 * \param A: 待排数组--A[low..high]
 * \param low: --A[low..high]
 * \param high: --A[low..high]
 * \param comp: smaller-从大到小排 bigger-从小到大排
 * \return 无，传入数组变为排序后的数组
 */
void Insertion_Sort(int* A, int low, int high, sort_comp comp){
    for(int j = low + 1; j <= high; ++j){
        int key = A[j];
        //insert A[j] into the sorted sequence A[0, ..., j - 1]
        int i = j - 1;
        while(i >= 0 && (comp == bigger ? A[i] > key : A[i] < key)){
            A[i + 1] = A[i];
            --i;
        }
        A[i + 1] = key;
    }
}
/** \brief
 *    直接选择排序-int数组
 * \param A: 待排数组
 * \param low: 待排数组区间左边界
 * \param high: 待排数组区间右边界(不包含)
 * \param comp: smaller-从大到小排 bigger-从小到大排
 * \return 无，传入数组变为排序后的数组
 *
 */
void Selection_Sort(int* A, int low, int high, sort_comp comp){
    for(int j = low; j < high - 1; ++j){
        // fin min / max
        int k = j;
        for(int i = j + 1; i < high; ++i){
            if(comp == bigger ? A[i] < A[k] : A[i] > A[k]){
                k = i;
            }
        }
        // exchange
        // 为什么判断后再异或？直接异或会有为零(不用交换)的情况（因为 j = k, 所以在第二步仍与自己异或，导致最终为0）
        // 也可用 + ，不过会有溢出的可能，而用 ^ 则不会
        if(j != k){
            A[j] = A[j] ^ A[k];
            A[k] = A[j] ^ A[k];
            A[j] = A[j] ^ A[k];
        }
    }
}
/*****************归并排序 ************************/
void Merge(int* A, int p, int q, int r, sort_comp comp);
/** \brief
 *    归并排序-int数组: O(n * lg n)
 *    FIXME: bigger能输出正确结果，但是smaller输出错误结果
 * \param A: 待排数组
 * \param low: 待排数组区间左边界
 * \param high: 待排数组区间右边界(不包含)
 * \param comp: smaller-从大到小排 bigger-从小到大排
 * \return 无，传入数组变为排序后的数组
 */
void Merge_Sort(int* A, int low, int high, sort_comp comp){
    int mid;
    if(low < high){ // 当 low == high 时“触底”，停止递归，进入基本情况，直接求解，然后合并
        mid = (low + high) / 2;
        // 分解问题
        Merge_Sort(A, low, mid, comp);
        Merge_Sort(A, mid + 1, high, comp);
        // 合并问题
        Merge(A, low, mid, high, comp);
    }
}
void Merge(int* A, int p, int q, int r, sort_comp comp){
    int n1 = q - p + 1;
    int n2 = r - q;
    int* L = new int[n1];
    int* R = new int[n2];
    for(int i = 0; i < n1; ++i){
        L[i] = A[p + i];
    }
    for(int i = 0; i < n2; ++i){
        R[i] = A[q + 1 + i];
    }
    for(int i = 0, j = 0, k = p; k <= r; ++k){
        if( i < n1 && j < n2){
            if((comp == bigger) ? (L[i] <= R[j]) : (L[i] >= R[j])){
            //if(L[i] <= R[j]){
                A[k] = L[i];
                ++i;
                continue;
            }
            else{
                A[k] = R[j];
                ++j;
                // 计算逆序对 int ans = 0;
                //ans += q - n1 + 1;
                continue;
            }
        }
        if(i >= n1 && j < n2){
            A[k] = R[j];
            ++j;
            continue;
        }
        if(i < n1 && j >= n2){
            A[k] = L[i];
            ++i;
            continue;
        }
    }
    delete []L;
    delete []R;
}
/** \brief
 *   冒泡排序
 * \param A: 待排数组--A[low..high]
 * \param low: --A[low..high]
 * \param high: --A[low..high]
 * \param comp: smaller-从大到小排 bigger-从小到大排
 * \return 无，传入数组变为排序后的数组
 */
void Bubble_Sort(int* A, int low, int high, sort_comp comp){
    for(int i = low; i <= high; ++i){
        for(int j = low + 1; j <= high; ++j){
            if(comp == bigger ? A[j] < A[j - 1] : A[j] > A[j - 1]){
                A[j - 1] = A[j - 1] ^ A[j];
                A[j] = A[j - 1] ^ A[j];
                A[j - 1] = A[j - 1] ^ A[j];
            }
        }
    }
}
/***************** 最大堆 + 堆排序 ************************/
/** \brief
 *  维护最大堆（维护最大堆的性质）--O(lg n) n:数组A的大小，lg n 为堆(树)的高度
 * \param A：最大堆数组
 * \param i：根结点
 * \param heap_size: A中堆元素的个数
 * \return
 */
void Max_Heapify(int* A, int i, int heap_size){
    int largest;
    int l = 2 * i;
    int r = 2 * i + 1;
    if(l <= heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if(r <= heap_size && A[r] > A[largest])
        largest = r;
    if(largest != i){
        A[i] = A[i] ^ A[largest];
        A[largest] = A[i] ^ A[largest];
        A[i] = A[i] ^ A[largest];
        Max_Heapify(A, largest, heap_size);
    }
}
/** \brief
 *  建最大堆--O(n)
 * \param A: 待排的数组
 * \param n: A的大小
 * \param heap_size: A中堆元素的个数
 * \return A成为最大堆数组
 */
void Build_Max_Heap(int* A, int n){
    int heap_size = n - 1;
    for(int i = n / 2; i >= 0; --i){
        Max_Heapify(A, i, heap_size);
    }
}
/** \brief
 *  堆排序--O(n * lg n)
 * \param A: 待排的数组
 * \param n: A的大小
 * \return
 */
void Heap_Sort(int* A, int n){
    int heap_size = n - 1;
    Build_Max_Heap(A, n);
    for(int i = n - 1; i >= 1; --i){
        A[0] = A[0] ^ A[i];
        A[i] = A[0] ^ A[i];
        A[0] = A[0] ^ A[i];
        --heap_size;
        Max_Heapify(A, 0, heap_size);
    }
}
/***************** TODO: 最大堆 + 最大优先队列 ************************/
class PriorityQueue{
private:
    int heap_size;
    vector<int> A;
public:
    PriorityQueue(int n = 0): heap_size(n){A.resize(n);}
    void Max_Heapify(int i);
    int Maximum();
    void Insert(int key);
    int Heap_Extract_Max();
    void Heap_Increase_Key(int i, int key);
};
/** \brief
 *  维护最大堆（维护最大堆的性质）
 * \param i int 根结点
 * \return void
 *
 */
void PriorityQueue::Max_Heapify(int i){
    int largest;
    int l = 2 * i;
    int r = 2 * i + 1;
    if(l <= heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if(r <= heap_size && A[r] > A[largest])
        largest = r;
    if(largest != i){
        A[i] = A[i] ^ A[largest];
        A[largest] = A[i] ^ A[largest];
        A[i] = A[i] ^ A[largest];
        Max_Heapify(largest);
    }
}
/** \brief
 *  返回最大优先队列的队首元素
 * \return int: 队首对象的关键字(此处就是简单的int值)
 *
 */
int PriorityQueue::Maximum(){
    return A[0];
}
/** \brief
 *  去掉并返回队列的队首元素
 * \return int
 *
 */
int PriorityQueue::Heap_Extract_Max(){
    if(heap_size < 0){
        std::cerr << "Heap Underflow" << std::endl;
        return -1;
    }
    int Max = A[0];
    A[0] = A[heap_size - 1];
    --heap_size;
    this->Max_Heapify(0);
    return Max;
}
/** \brief
 *  增加 i 的优先级
 * \param i int: A[i]
 * \param key int: A[i] = key
 * \return void
 *
 */
void PriorityQueue::Heap_Increase_Key(int i, int key){
    if(key < A[i])
        std::cerr << "new key is smaller than current key" << std::endl;
    A[i] = key;
    while(i > 0 && A[i / 2] < A[i]){
        A[i] = A[i] ^ A[i / 2];
        A[i / 2] = A[i] ^ A[i / 2];
        A[i] = A[i] ^ A[i / 2];
        i = i / 2;
    }
}
/** \brief
 *  插入一个新键值
 * \param key int: 新键值
 * \return void
 *
 */
void PriorityQueue::Insert(int key){
    A.resize(A.size() + 1);
    ++heap_size;
    A[heap_size - 1] = INF_MIX;
    Heap_Increase_Key(heap_size - 1, key);
}
/***************** 快速排序 ************************/
/** \brief
 *  对子数组A[p..r]进行原址重排，以A[r]为界，将比A[r]小的放在左边，比A[r]大的分在右边
 * \param A int*--A[p..r]
 * \param p int--A[p..r]
 * \param r int--A[p..r]
 * \return int--A[r]在重排后的数组下标
 */
int Partition(int* A, int p, int r){
    int x = A[r];
    int i = p - 1;
    for(int j = p; j < r; ++j){
        if(A[j] <= x){
            ++i;
            if(i != j){
                A[i] = A[i] ^ A[j];
                A[j] = A[i] ^ A[j];
                A[i] = A[i] ^ A[j];
            }
        }
    }
    if(i + 1 != r){
        A[i + 1] = A[i + 1] ^ A[r];
        A[r] = A[i + 1] ^ A[r];
        A[i + 1] = A[i + 1] ^ A[r];
    }
    return i + 1;
}
/** \brief
 *  对子数组A[p..r]进行原址重排--随机化版
 * \param A int* A[p..r]
 * \param p int A[p..r]
 * \param r int A[p..r]
 * \return int--A[r]在重排后的数组下标
 *
 */
int Random_Partition(int* A, int p, int r){
    // 随机化版的快速排序--随机选择一个数与A[r]交换
    int ri = rand() % (r - p + 1) + p;
    if(r != ri){
        A[r] = A[r] ^ A[ri];
        A[ri] = A[r] ^ A[ri];
        A[r] = A[r] ^ A[ri];
    }
    return Partition(A, p, r);
}
/** \brief
 *  快速排序
 * \param A int* 待排数组
 * \param p int: 数组头
 * \param r int: 数组尾
 * \return void
 *
 */
void Quick_Sort(int* A, int p, int r){
    if(p < r){
        int q = Random_Partition(A, p, r);
        Quick_Sort(A, p, q - 1);
        Quick_Sort(A, q + 1, r);
    }
}
/***************** 计数排序 ************************/
/** \brief
 *  计数排序--O(k + n), 当 k = O(n)时，算法时间复杂度为O(n)
 * \param A int*--待排数组
 * \param B int*--排序后的输出
 * \param n int --A的大小
 * \param k int --数值的范围
 * \return void
 *
 */
void Countint_Sort(int* A, int* B, int n, int k){
    int* C = new int[k + 1];
    for(int i = 0; i <= k; ++i)
        C[i] = 0;
    for(int j = 0; j < n; ++j)
        ++C[A[j]];
    // C[i] now contains the number of elements equal to i
    for(int i = 1; i <= k; ++i)
        C[i] += C[i - 1];
    // C[i] now contains the number of elements less than or equal to i
    for(int j = n - 1; j >= 0; --j){
        B[C[A[j]] - 1] = A[j];  // C[A[j]] >= 1
        --C[A[j]];
    }
    delete[] C;
}
/***************** 基数排序 ************************/
#define RADIX_10 10    //整形排序，进制数
#define KEYNUM_31 10     //关键字个数，这里为整形位数
/** \brief
 *  找到num的从低到高的第pos位的数据
 * \param num int 一个整形数据
 * \param pos int 表示要获得的整形的第pos位数据
 * \return int 第pos位数据
 *
 */
int GetNumInPos(int num,int pos)
{
	int temp = 1;
	for (int i = 0; i < pos - 1; i++)
		temp *= 10;

	return (num / temp) % 10;
}
/** \brief
 *  基数排序
 * \param pDataArray int* 无序数组
 * \param iDataNum int 无序数据个数
 * \return void
 *
 */
void RadixSort(int* pDataArray, int iDataNum)
{
	int *radixArrays[RADIX_10];    //分别为0~9的序列空间
	for (int i = 0; i < 10; i++)
	{
		radixArrays[i] = (int *)malloc(sizeof(int) * (iDataNum + 1));
		radixArrays[i][0] = 0;    //index为0处记录这组数据的个数
	}

	for (int pos = 1; pos <= KEYNUM_31; pos++)    //从个位开始到31位对各位上进行排序
	{
		for (int i = 0; i < iDataNum; i++)    //分配过程，计数排序过程1
		{
			int num = GetNumInPos(pDataArray[i], pos);
			int index = ++radixArrays[num][0];
			radixArrays[num][index] = pDataArray[i];
		}

		for (int i = 0, j =0; i < RADIX_10; i++)    //收集，计数排序过程2
		{
			for (int k = 1; k <= radixArrays[i][0]; k++)
				pDataArray[j++] = radixArrays[i][k];
			radixArrays[i][0] = 0;    //复位
		}
	}
	for (int i = 0; i < 10; i++)
	{
		free(radixArrays[i]);
	}
}
/***************** 桶排序  *************************/
//int a[]= {1,255,8,6,25,47,14,35,58,75,96,158,657};
//const int len=sizeof(a)/sizeof(int);
//int b[10][len+1]= {0}; //将b全部置0
//int numOfDigits(int a[])
//{
//    int largest=0;
//    for(int i=0; i<len; i++) //获取最大值
//        if(a[i]>largest)
//            largest=a[i];
//    int digits=0;//digits为最大值的位数
//    while(largest)
//    {
//        digits++;
//        largest/=10;
//    }
//    return digits;
//}
//void distributeElments(int a[],int b[10][len+1],int digits)
//{
//    int divisor=10;//除数
//    for(int i=1; i<digits; i++)
//        divisor*=10;
//    for(int j=0; j<len; j++)
//    {
//        int numOfDigist=(a[j]%divisor-a[j]%(divisor/10))/(divisor/10);
////numOfDigits为相应的(divisor/10)位的值,如当divisor=10时,求的是个位数
//        int num=++b[numOfDigist][0];//用b中第一列的元素来储存每行中元素的个数
//        b[numOfDigist][num]=a[j];
//    }
//}
//void collectElments(int a[],int b[10][len+1])
//{
//    int k=0;
//    for(int i=0; i<10; i++)
//        for(int j=1; j<=b[i][0]; j++)
//            a[k++]=b[i][j];
//}
//void zeroBucket(int b[][len+1])
//{
//    for(int i=0; i<10; i++)
//        for(int j=0; j<len+1; j++)
//            b[i][j]=0;
//}
//void bucketSort(int a[])
//{
//    int digits=numOfDigits(a);
//    for(int i=1; i<=digits; i++)
//    {
//        distributeElments(a,b,i);
//        collectElments(a,b);
//        if(i!=digits)
//            zeroBucket(b);
//    }
//}
/***************** 线性查找  *************************/
/** \brief
 *  返回数组A[p..r]中第i小的元素--O(n)
 * \param A int*--A[p..r]
 * \param p int--A[p..r]
 * \param r int--A[p..r]
 * \param i int
 * \return int--A[p..r]中第i小的元素
 */
int Randomized_Select(int* A, int p, int r, int i){
    if(p == r)
        return A[p];
    if(i > r)
        return -1;
    int q = Random_Partition(A, p, r);
    int k = q - p + 1;
    if(i == k)
        return A[q];
    else if(i < k)
        return Randomized_Select(A, p, q - 1, i);
    else
        return Randomized_Select(A, q + 1, r, i - k);
}
/***************** 二分查找  *************************/
/** \brief
 *  二分查找法
 * \param *A: 数组
 * \param obj: 要找的数
 * \param A_start: 待排数组区间左边界
 * \param A_end: 待排数组区间右边界(不包含)
 * \return 存在返回 true 否则返回 false
 *
 */
int Binary_Serach(int* A, int A_start, int A_end, int obj){
    if(A_start <= A_end){
        int A_mid = (A_start + A_end) / 2;
        if(A[A_mid] == obj)
            return A_mid;
        else if(A[A_mid] > obj)
            return Binary_Serach(A, A_start, A_mid - 1, obj);
        else
            return Binary_Serach(A, A_mid + 1, A_end, obj);
    }
    return -1;
}
#endif // LIMORTON_SORT_H_INCLUDED
