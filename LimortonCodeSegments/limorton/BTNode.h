#ifndef BTNODE_H_INCLUDED
#define BTNODE_H_INCLUDED
// 表示二叉树的节点
#if 0
template <typename T>
class BTNode
{
   public:
		// BTNode 是类的实现，使得数据成为公有成员简化了类函数的构造，
		//结合BTNode的应用场合，并不违反面向对象设计原则
		T data;
		BTNode<T> *left, *right;

		// 默认构造函数。数据项未被初始化，左、右指针为空
		BTNode():left(NULL),right(NULL)
		{}

        // 标准构造函数，初始化数据成员，左、右子树指针的默认参数值都为NULL
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
