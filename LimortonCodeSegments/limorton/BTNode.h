#ifndef BTNODE_H_INCLUDED
#define BTNODE_H_INCLUDED
// ��ʾ�������Ľڵ�
#if 0
template <typename T>
class BTNode
{
   public:
		// BTNode �����ʵ�֣�ʹ�����ݳ�Ϊ���г�Ա�����ຯ���Ĺ��죬
		//���BTNode��Ӧ�ó��ϣ�����Υ������������ԭ��
		T data;
		BTNode<T> *left, *right;

		// Ĭ�Ϲ��캯����������δ����ʼ��������ָ��Ϊ��
		BTNode():left(NULL),right(NULL)
		{}

        // ��׼���캯������ʼ�����ݳ�Ա����������ָ���Ĭ�ϲ���ֵ��ΪNULL
		BTNode (const T& item, BTNode<T> *lptr = NULL,
				 BTNode<T> *rptr = NULL):
					data(item), left(lptr), right(rptr)
		{}
};

#else
template<class T>
class BTNode{
public:
    T data;
    BTNode<T> *left, *right;

    BTNode():left(nullptr),right(nullptr){}

    BTNode(const T& item, BTNode<T> *lptr = nullptr, BTNode<T> *rptr = nullptr): data(item), left(lptr), right(rptr){}
};
#endif // 0
#endif // BTNODE_H_INCLUDED
