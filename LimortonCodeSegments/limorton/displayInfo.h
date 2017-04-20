#ifndef DISPLAYINFO_H_INCLUDED
#define DISPLAYINFO_H_INCLUDED
#include <iostream>
//using namespace std;

void cout_Info(const string& str){
    std::cout << "# " << str << std::endl;
}

/** \brief 输出单个元素
 *
 */
template<typename T>
void cout_A(T a){
    std::cout << a << std::endl;
}

/** \brief 输出数组元素
 *
 * \param 数组名
 * \param 数组大小
 * \return NULL
 *
 */
template<typename T>
void cout_Array(const T& vec, int n){
    for(int i = 0; i < n; ++i){
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}


#endif // DISPLAYINFO_H_INCLUDED
