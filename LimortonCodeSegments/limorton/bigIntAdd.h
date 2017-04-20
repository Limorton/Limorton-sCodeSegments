#ifndef BIGINTADD_H_INCLUDED
#define BIGINTADD_H_INCLUDED

#include <list>
#include <string>
#include <iomanip>
using namespace std;

class BigIntAdd
{
 public:
	 friend istream & operator>>(istream & in,BigIntAdd & number);
	 friend ostream & operator<<(ostream & out,const BigIntAdd & number);
	 friend BigIntAdd operator+(BigIntAdd & addend1,BigIntAdd & addend2);
 private:
	 //����һ�������,�����洢����
	 list<short int> myInt;
};

//�������뺯��
istream & operator>>(istream & in,BigIntAdd & number)
{
	string str;
	in>>str;      //���ַ����洢����
	size_t len=str.length();
	size_t q,r,first;

    //if��Ӧ�ڹ�����Ž�����λ��С�����Ľ��
    if(isdigit(str[0]))   //��Ӧ�޷�����
	{
        //�����޷������ķ��Ž�㣬�޷�������Ϊ��������
		number.myInt.push_back(1);
		//���飬��r==0,��ȷ����q���飬Ҳ��q�����
		//��r!=0����ȷ����q+1�����
		q=len/3;
		r=len%3;
		first=r;
		if(r!=0)
		{
			int nodeValue(0);
			size_t i=0;
			for(;i<=r-1;i++)
				nodeValue=10*nodeValue+(str[i]-'0');
              //ע��˴��ı��ʽ��Ӧr!=0���Ǹ����ֵ
			number.myInt.push_back(nodeValue);
		}

	}
	else    //��Ӧ�з�����
	{
		//�����з��������Ž��
		if(str[0]=='-')
			number.myInt.push_back(-1);
		else
			number.myInt.push_back(1);
        //�˴��з�������ӵڶ�Ԫ�ؿ�ʼ����
		q=(len-1)/3;
		r=(len-1)%3;
		first=r+1;
		if(r!=0)
		{
            int nodeValue(0);
			size_t i=1;
			for(;i<=r;i++)
				nodeValue=10*nodeValue+(str[i]-'0');
			number.myInt.push_back(nodeValue);
		}
	}

    //forѭ����Ӧ�ں�������λ���Ľ��
	for(size_t j=0;j<q;j++)
	{
		int nodeValue(0);
        //ÿ������λ����һ�����ĵ�����
		size_t index=first+3*j;
		for(int i=0;i<=2;i++)
			nodeValue=10*nodeValue+(str[index+i]-'0');
		number.myInt.push_back(nodeValue);
	}
	return in;
}

//�����������
ostream & operator<<(ostream & out,const BigIntAdd & number)
{
	list<short int>::const_iterator iter=number.myInt.begin();
	  //ָ����Ž��
    if(*iter==-1)
		out<<'-';   //��Ϊ�����������-�����������������
	if(++iter==number.myInt.end())
		out<<0;     //��Ӧ����Ϊ��
	else            //���ÿ������Ӧ����
	{
		out<<*iter;
		for(iter++;iter!=number.myInt.end();++iter)
			out<<setw(3)
               <<setfill('0')
               <<*iter;
	}
	return out;
}

//�����ӷ�����
BigIntAdd operator+(BigIntAdd & add1,BigIntAdd& add2)
{
    //ȡ�������ķ���
	list<short int>::iterator iter1=add1.myInt.begin();
	list<short int>::iterator iter2=add2.myInt.begin();
	short sign1=*iter1,sign2=*iter2;

	short sumSign;                    //��������
	size_t sz1=add1.myInt.size()-1;   //add1��ֵ���ֵĽ����
	size_t sz2=add2.myInt.size()-1;   //add2��ֵ���ֵĽ����

	//ȷ���������ķ���
	if(sign1*sign2>0)                 //����������ͬ
	{
		if(sign1==-1)                 //������Ϊ����
		{
			sumSign=-1;
			sign1=1;
			sign2=1;
		}
		else                          //������Ϊ����
			sumSign=1;

	}
	else{                              //�������Ų�ͬ
		if(sign1*sign2<0)
			if(sz1==sz2)              //����λ�����
			{
                //�ӵ�һ����ֵ��㣬�����λ
				for(iter1++,iter2++;iter1!=add1.myInt.end();iter1++,iter2++)
				{
					if(*iter1*sign1+*iter2*sign2<0)//�����ľ���ֵ��
					{
						sumSign=-1;
						sign1=-sign1;
						sign2=-sign2;
						break;
					}
					if((*iter1*sign1)+(*iter2*sign2)>0)//�����ľ���ֵ��
					{
						sumSign=1;
						break;
					}
				}
				if(iter1==add1.myInt.end())//����ֵ���
					sumSign=1;
			}
			else{                        //����λ������
				if(sz1*sign1+sz2*sign2<0)//������λ����
				{
					sumSign=-1;
					sign1=-sign1;
					sign2=-sign2;
				}
				else                     //������λ����
					sumSign=1;
			}
	}

    //ȷ������������ֵ����
	list<short int>::reverse_iterator riter1=add1.myInt.rbegin();
    list<short int>::reverse_iterator riter2=add2.myInt.rbegin();
      //�����������������
    BigIntAdd sum;           //�洢������
	short carry=0;           //�洢��λֵ
    //��������Ӧ��Ӳ��ֶ���Ϊ��
	while(riter1!=--add1.myInt.rend()&&riter2!=--add2.myInt.rend())
	{
		short temp=(*riter1*sign1)+(*riter2*sign2)+carry;
		if(temp<0)           //����ֵΪ��
		{
			temp+=short(1000);
			carry=-1;
		}
		else                 //����ֵΪ��
		{
			carry=temp/short(1000);
			temp%=1000;
		}
		sum.myInt.push_front(temp);
		riter1++;
		riter2++;
	}
    //add2�Ķ�Ӧ��Ӳ���Ϊ��
	while(riter1!=--add1.myInt.rend())
	{
		short temp=*riter1+carry;
		if(temp<0)         //����ֵΪ��
		{
			temp+=short(1000);
			carry=-1;
		}
		else               //����ֵΪ��
		{
			carry=temp/1000;
			temp%=1000;
		}
		sum.myInt.push_front(temp);
		riter1++;
	}
    //add1��Ӧ��Ӳ���Ϊ��
	while(riter2!=--add2.myInt.rend())
	{
		short temp=*riter2+carry;
		if(temp<0)          //����ֵΪ��
		{
			temp+=short(1000);
			carry=-1;
		}
		else                //����ֵΪ��
		{
			carry=temp/1000;
			temp%=1000;
		}
		sum.myInt.push_front(temp);
		riter2++;
	}

	if(carry!=0)  //���һ����Ӧ�����������н�λ
		sum.myInt.push_front(carry);

	while(*sum.myInt.begin()==0)
		sum.myInt.pop_front();
      //���λ��Ӧ���û����Ч��ֵʱ��ɾ���ý��
	sum.myInt.push_front(sumSign);
      //�����������������ķ���
	return sum;
}


#endif // BIGINTADD_H_INCLUDED
