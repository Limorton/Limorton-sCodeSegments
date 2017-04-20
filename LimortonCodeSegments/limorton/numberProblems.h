#ifndef LIMORTON_NUMBERPROBLEMS_H_INCLUDED
#define LIMORTON_NUMBERPROBLEMS_H_INCLUDED
#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <stack>
//#define NDEBUG
#include <assert.h>
using namespace std;

#ifndef INF
#define INF 1
const int INF_MAX = 0x3f3f3f3f;
const int INF_MIX = -0X3f3f3f3f;
#endif // INF

/** \brief
 *    求2的n次幂, n <= 30
 *    若要增大n，可将int改为 long int / long long int
 * \param n: 2 ^ n
 * \return 2 ^ n
 */
int pow2n(int n){
    assert(n < 31);
    int ans = 1;
    ans = ans << n;
    return ans;
}
/** \brief
 *  Horner Rules: 霍纳规则求多项式的值
 * \param An: 系数数组 a0, a1, ..., an
 * \param x: x
 * \return Sum(Ak * x ^ k | k: 0 -> n)
 */
double Horner(const vector<double>& An, double x){
    double y = 0;
    for(int i = An.size() - 1; i >= 0; --i)
        y = An[i] + x * y;
    return y;
}
/** \brief
 *    十进制转其他进制
 * \param num: 待转换的数
 * \param base: 进制基数
 * \return 转换后的string数
 *
 */
string Dec_to_Base(int num, int base){
    //digitChar 存基数值，此处最多转到16进制
    string digitChar = "0123456789ABCDEF", numStr = "";
    //用于临时存储余数的堆栈
    stack<char> stk;
    //求余数直至余数为零
    do{
        stk.push(digitChar[num % base]);
        num /= base;
    }while(num != 0);

    while (!stk.empty()){
        numStr += stk.top();
        stk.pop();
    }
    return numStr;
}

/**************** format convert ***************************/
/** \brief
 *    int to vector<int>
 * \param n: 待转换的int数
 * \return int数的vector数组形式
 *
 */
vector<int> Int_to_Vector(int n){
    stringstream ss;
    ss << n;
    string str;
    ss >> str;
    ss.clear();
    vector<int> vec;
    vec.resize(str.size());
    for(unsigned int i = 0; i < str.size(); ++i){
        ss << str[i];
        ss >> vec[i];
        ss.clear();
    }
    return vec;
}
///vector<int> 转 int
int Vector_to_Int(const vector<int>& vec){
    int sum = 0;
    for(unsigned int i = 0; i < vec.size(); ++i){
        if(vec[i] == 1)
            sum += pow2n(vec.size() - i - 1);
    }
    return sum;
}
/** \brief
 *    char* to int number
 * \param char* cp: 字符串指针
 * \return int形式
 *
 */
int Chars_to_Int(char* cp){
    int i = 0;
    while(*cp >= '0' && *cp <= '9')
        i = i * 10 + *cp++ - '0';
    return i;
}
/** \brief
 *    string to int number
 * \param str: 待转换的string
 * \return int形式
 *
 */
int Str_To_Int(string str) {
    if(str.empty()) return 0;
    int ans = 0;
    int i = 0;
    int flag = 1;
    if(str[0] == '-'){
        flag = 0;
        i = 1;
    }else if(str[0] == '+'){
        flag = 1;
        i = 1;
    }
    while(i < (int)str.size()){
        if(str[i] >= '0' && str[i] <= '9')
            ans = 10 * ans + str[i] -  '0';
        else
            return 0;
        ++i;
    }
    return flag ? ans : -ans;
}
/** \brief
 *    返回数字的各位数的和，忽略正负号
 * \param num: 待计算的数
 * \return 各位数的和
 *
 */
int Digits_Sum(int num){
    if(num < 0)
        num = -num;
    int sum = 0;
    while(num % 10 || num / 10){
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

/*******************  算法导论 ***************************/
/** \brief
 *  求具有最大和的连续子数组--分治算法O(n*lg(n))
 *  允许结果为空子数组，即若全部元素为负数，返回0
 * \param arr: 数值数组
 * \param left: 待排数组区间左边界
 * \param right: 待排数组区间右边界(不包含)
 * \return 最大子数组的和
 */
int Max_SubArray(const vector<int> arr, int left, int right){
    int max_left, max_right;
    int max_left_mid, max_mid_right;
    int sum_left, sum_right;
    // 基本情况, 允许结果为空子数组
    if(left == right){
        if(arr[left] > 0)
            return arr[left];
        else
            return 0;
    }
    // 求含中间边界的最大值
    int mid = (left + right) >> 1;
    max_left_mid = INF_MIX;
    sum_left = INF_MIX;
    for(int i = mid; i >= left; --i){
        sum_left += arr[i];
        if(sum_left > max_left_mid)
            max_left_mid = sum_left;
    }
    max_mid_right = INF_MIX;
    sum_right = INF_MIX;
    for(int i = mid + 1; i <= right; ++i){
        sum_right += arr[i];
        if(sum_right > max_mid_right)
            max_mid_right = sum_right;
    }
    // 分解问题
    max_left = Max_SubArray(arr, left, mid);
    max_right = Max_SubArray(arr, mid + 1, right);
    // 合并问题
    return (max_left > max_right \
            ? (max_left > (max_left_mid + max_mid_right) ? max_left : (max_left_mid + max_mid_right)) \
            : (max_right > (max_left_mid + max_mid_right) ? max_right : (max_left_mid + max_mid_right)));
}
void Test_Max_SubArray(){
    vector<int> vec(5);
    vec[0] = -1;
    vec[1] = -1;
    vec[2] = -9;
    vec[3] = -2;
    vec[4] = -3;
    cout << "Max_SubArray: " << Max_SubArray(vec, 0, 4) << endl;
}
/** \brief
 *      求具有最大和的连续子数组--线性时间的算法O(n)--(具有联机算法特性：联机算法是在任意时刻算法
 *  对要操作的数据只读入（扫描）一次，一旦被读入并处理，它就不需要在被记忆了。而在此处理
 *  过程中算法能对它已经读入的数据立即给出相应子序列问题的正确答案。)
 * \param arr: 数值数组
 * \return ans: 最大子数组
 */
int FindGreatestSumOfSubArray(vector<int> arr) {
    int sub_max = INF_MIX;
    int sub_temp = 0;
    for(unsigned int i = 0; i < arr.size(); ++i){
        sub_temp += arr[i];
        if(sub_temp > sub_max){
            sub_max = sub_temp;
            continue;
        }
        if(sub_temp < 0){
            sub_temp = 0;
        }
    }
    return sub_max;
}
/** \brief
 *  搜索Young矩阵1--线性排除法--O(m + n)
 * \param matrix vector<vector<int>>&
 * \param target int: 要搜索的元素
 * \return bool: true-找到 false-无此元素
 *
 */
bool searchMatrix1(vector<vector<int>>& matrix, int target) {
    if(matrix.empty())
        return false;
    int m = matrix.size(), n = matrix[0].size();
    for(int a = 0, b = n - 1; a < m && b >= 0;){
        if(matrix[a][b] == target)
            return true;
        else if(matrix[a][b] > target){
            b--;
        }
        else{
            a++;
        }
    }
    return false;
}
/// 二分法查找中线上最后一个小于target的值
int helpMatrix(vector<int>& a, int y1, int y2, int target){
    int left = y1, right = y2;
    while(left <= right){
        int midy = (left + right) >> 1;
        if(a[midy] <= target)
            left = midy + 1;
        else
            right = midy - 1;
    }
    return left - 1;
}
///分治法搜索矩阵
bool findMartix(vector<vector<int>>& matrix, int x1, int y1, int x2, int y2, int target){
    if(x1 > x2 || y1 > y2)
            return false;
    int midx = (x1 + x2) >> 1;
//    int midy = (y1 + y2) >> 1;
//    if(matrix[midx][midy] == target)
//        return true;
//    return (matrix[midx][midy] > target)?
//    (findMartix(matrix, x1, y1, midx-1, y2, target) || findMartix(matrix, midx, y1, x2, midy-1, target)):
//    (findMartix(matrix, x1, midy + 1, x2, y2, target) || findMartix(matrix, midx + 1, y1, x2, midy, target));
    // 二分查找中线上临界点
    int indy = helpMatrix(matrix[midx], y1, y2, target);
    if(indy >= y1 && matrix[midx][indy] == target)
        return true;
    else
        return findMartix(matrix, x1, indy + 1, midx - 1, y2, target) ||
        findMartix(matrix, midx + 1, y1, x2, indy, target);
}
/** \brief
 *  搜索Young矩阵2--分治法--O(m + n)
 * \param matrix vector<vector<int>>&
 * \param target int: 要搜索的元素
 * \return bool: true-找到 false-无此元素
 *
 */
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    if(matrix.empty())
        return false;
    int m = matrix.size(), n = matrix[0].size();
    return findMartix(matrix, 0, 0, m - 1, n - 1, target);
}
#endif // LIMORTON_NUMBERPROBLEMS_H_INCLUDED
