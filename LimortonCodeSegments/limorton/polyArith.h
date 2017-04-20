#ifndef POLYARITH_H_INCLUDED
#define POLYARITH_H_INCLUDED
#include <list>
#include <iostream>
#include <cassert>

using namespace std;

//�������ʽ������
class term{
public:
    int coef;   //����ʽϵ��
    int exp;    //����ʽָ��
    term(int c = 0, int e = 0):coef(0), exp(0){}
};

//�������ʽ��
class PolyArith{
private:
    list<term> m_poly_list_first;   //�洢��һ������ʽ
    list<term> m_poly_list_second;  //�洢�� 2 ������ʽ
    list<term> m_poly_list_result;  //�洢������
    //˽�г�Ա���������ڳ˷�ʱ��
    list<term> Poly_add(list<term>& poly_list_first, list<term>& poly_list_second);
public:
    //���뺯���������������ʽ
    void Poly_input();
    //����������������ʽ
    void Poly_output();
    //�ӷ�����,�˴���������
    void Poly_add();
    //�˷�����
    void Poly_multi();
};

list<term> PolyArith::Poly_add(list<term>& poly_list_first, list<term>& poly_list_second){
    list<term> poly_list_result;
    list<term>::iterator iter_first = poly_list_first.begin();
    list<term>::iterator iter_second = poly_list_second.begin();
    //��whileѭ��������������������û��ָ����β������
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
    cout << "�������һ������ʽ������" << endl;
    cin >> n;
    cout << "�����������һ������ʽ��ÿ���ϵ����ָ����" << endl;
    for(int i = 1; i <= n; i++){
        term t_temp;
        cin >> t_temp.coef >> t_temp.exp;
        m_poly_list_first.push_back(t_temp);
    }
    n = 0;
    cout << "������ڶ�������ʽ������" << endl;
    cin >> n;
    cout << "����������ڶ�������ʽ��ÿ���ϵ����ָ����" << endl;
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
            list<term> poly_list_temp; //���Դ洢����ʽ���м�������
            list<term>::iterator iter_second =\
            m_poly_list_second.begin();
            for(;iter_second!=m_poly_list_second.end();\
                iter_second++)
            {
                term t_temp;           //���Դ洢����м�������
                term t_first = (term)*iter_first;
                term t_second = (term)*iter_second;
                //�˴�ʵ�ֶ���ʽ������
                t_temp.coef = t_first.coef*t_second.coef;   //ϵ�����
                t_temp.exp = t_first.exp + t_second.exp;    //ָ�����
                poly_list_temp.push_back(t_temp);
            }
            //�˴�����˽�г�Ա����Poly_add����
            poly_list_result = Poly_add(poly_list_temp,poly_list_result);
        }
        //����������ֵ��˽�����ݳ�Ա���������
        m_poly_list_result = poly_list_result;
}


#endif // POLYARITH_H_INCLUDED
