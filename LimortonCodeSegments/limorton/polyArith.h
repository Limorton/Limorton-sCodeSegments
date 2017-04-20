#ifndef POLYARITH_H_INCLUDED
#define POLYARITH_H_INCLUDED
#include <list>
#include <iostream>
#include <cassert>

using namespace std;

//定义多项式的项类
class term{
public:
    int coef;   //多项式系数
    int exp;    //多项式指数
    term(int c = 0, int e = 0):coef(0), exp(0){}
};

//定义多项式类
class PolyArith{
private:
    list<term> m_poly_list_first;   //存储第一个多项式
    list<term> m_poly_list_second;  //存储第 2 个多项式
    list<term> m_poly_list_result;  //存储运算结果
    //私有成员函数，用在乘法时用
    list<term> Poly_add(list<term>& poly_list_first, list<term>& poly_list_second);
public:
    //输入函数，用以输入多项式
    void Poly_input();
    //输出函数，输出多项式
    void Poly_output();
    //加法函数,此处不带参数
    void Poly_add();
    //乘法函数
    void Poly_multi();
};

list<term> PolyArith::Poly_add(list<term>& poly_list_first, list<term>& poly_list_second){
    list<term> poly_list_result;
    list<term>::iterator iter_first = poly_list_first.begin();
    list<term>::iterator iter_second = poly_list_second.begin();
    //该while循环针对两个链表迭代器都没有指到结尾的情形
    while(iter_first != poly_list_first.end() &&
          iter_second != poly_list_second.end()){
        term t_temp;
        term t_first = (term)* iter_first;
        term t_second = (term)* iter_second;
        if(t_first.exp > t_second.exp){
            poly_list_result.push_back(t_first);
            iter_first++;
        }
        else if(t_second.exp > t_first.exp){
            poly_list_result.push_back(t_second);
            iter_second++;
        }
        else{
            t_temp.coef = t_first.coef + t_second.coef;
            t_temp.exp = t_first.exp;
            poly_list_result.push_back(t_temp);
            iter_first++;
            iter_second++;
        }
          }
        //
        for(; iter_first != poly_list_first.end(); iter_first++){
            poly_list_result.push_back(*iter_first);
        }
        //
        for(; iter_second != poly_list_second.end(); iter_second++){
            poly_list_result.push_back(*iter_second);
        }

    return poly_list_result;
}

void PolyArith::Poly_input(){
    int n;
    cout << "请输入第一个多项式的项数" << endl;
    cin >> n;
    cout << "按降幂输入第一个多项式的每项的系数和指数：" << endl;
    for(int i = 1; i <= n; i++){
        term t_temp;
        cin >> t_temp.coef >> t_temp.exp;
        m_poly_list_first.push_back(t_temp);
    }
    n = 0;
    cout << "请输入第二个多项式的项数" << endl;
    cin >> n;
    cout << "按降幂输入第二个多项式的每项的系数和指数：" << endl;
    for(int i = 1; i <= n; i++){
        term t_temp;
        cin >> t_temp.coef >> t_temp.exp;
        m_poly_list_second.push_back(t_temp);
    }
}

void PolyArith::Poly_output(){
    list<term>::iterator iter = m_poly_list_result.begin();
    for(; iter != m_poly_list_result.end();){
        term t_temp = *iter;
        cout << t_temp.coef << "x^" << t_temp.exp;
        if(++iter != m_poly_list_result.end())
            cout << "+";
    }
    cout << endl;
}

void PolyArith::Poly_add(){
    list<term>::iterator iter_first = m_poly_list_first.begin();
        list<term>::iterator iter_second =\
        m_poly_list_second.begin();
        while(iter_first != m_poly_list_first.end()&&\
            iter_second != m_poly_list_second.end())
        {
            term t_temp;
            term t_first = (term)*iter_first;
            term t_second = (term)*iter_second;
            if(t_first.exp>t_second.exp)
            {
                m_poly_list_result.push_back(t_first);
                iter_first++;
            }
            else if(t_second.exp>t_first.exp)
            {
                m_poly_list_result.push_back(t_second);
                iter_second++;
            }
            else
            {
                t_temp.coef=t_first.coef+t_second.coef;
                t_temp.exp=t_first.exp;
                m_poly_list_result.push_back(t_temp);
                iter_first++;
                iter_second++;
            }
        }
        for(;iter_first != m_poly_list_first.end();iter_first++)
        {
            m_poly_list_result.push_back(*iter_first);
        }
        for(;iter_second != m_poly_list_second.end();iter_second++)
        {
            m_poly_list_result.push_back(*iter_second);
        }
}

void PolyArith::Poly_multi(){
    list<term> poly_list_result;
        list<term>::iterator iter_first = m_poly_list_first.begin();
        for(;iter_first!=m_poly_list_first.end();iter_first++)
        {
            list<term> poly_list_temp; //用以存储多项式的中间运算结果
            list<term>::iterator iter_second =\
            m_poly_list_second.begin();
            for(;iter_second!=m_poly_list_second.end();\
                iter_second++)
            {
                term t_temp;           //用以存储项的中间运算结果
                term t_first = (term)*iter_first;
                term t_second = (term)*iter_second;
                //此处实现多项式项的相乘
                t_temp.coef = t_first.coef*t_second.coef;   //系数相乘
                t_temp.exp = t_first.exp + t_second.exp;    //指数相加
                poly_list_temp.push_back(t_temp);
            }
            //此处调用私有成员函数Poly_add（）
            poly_list_result = Poly_add(poly_list_temp,poly_list_result);
        }
        //将运算结果赋值给私有数据成员，用以输出
        m_poly_list_result = poly_list_result;
}


#endif // POLYARITH_H_INCLUDED
