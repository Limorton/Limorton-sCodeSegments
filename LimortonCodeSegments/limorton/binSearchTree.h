/***********************************************************
*��������������ʵ��
*�������Ķ���
*
*
***********************************************************/

#ifndef BINARY_SEARCH_TREE_CLASS
#define BINARY_SEARCH_TREE_CLASS
#ifndef NULL
#include <cstddef>
#endif  // NULL

#include <iostream>
#include <iomanip>		// ���� setw()
#include <string>
#include <queue>
#include <utility>		// pair ��
#include "except.h"		// �쳣��exception����

using namespace std;

/// �������ڵ������
template <typename T>
class BSTNode
{
public:
    // BSTNode����ʵ�ֶ�����������
    // ʹ���ݹ����Լ��ຯ���Ĺ���
    T data;
    // �ڵ�����
    BSTNode<T> *left, *right, *parent;
    // ָ���ӽڵ��ָ���ָ�򸡽ڵ��ָ��

    // Ĭ�Ϲ��캯����������δ����ʼ��������ָ���Լ���ָ���Ϊ��
    BSTNode():left(NULL),right(NULL),parent(NULL)
    {}
    // ���캯��
    BSTNode (const T& item, BSTNode<T> *lptr = NULL,
          BSTNode<T> *rptr = NULL, BSTNode<T> *pptr = NULL):
            data(item), left(lptr), right(rptr), parent(pptr)
    {}
};

/// ��������
template <typename T>
class BinSearchTree
{
public:
    // ����������Ƕ����
    #include "BSTiterator.h"

    BinSearchTree();
    // Ĭ�Ϲ��캯������ʼ����rootΪNULL��sizeΪ0
    BinSearchTree(T *first, T *last);
    // ���캯������ָ����[first, last)��ָԪ�ز��뵽����
    BinSearchTree(const BinSearchTree<T>& tree);
    // ���ƹ��캯��
    ~BinSearchTree();
    // ��������
    BinSearchTree<T>& operator= (const BinSearchTree<T>& rhs);
    // ��ֵ�����

    iterator find(const T& item);
    // ����item. ����ҵ����򷵻�����ָ�����ĵ�������
    //���򷵻�end()
    const_iterator find(const T& item) const;
    // �����㷨�ĳ����汾

    int empty() const;
    // ָ�����Ƿ�Ϊ��
    int size() const;
    // �����������������Ŀ

    pair<iterator, bool> insert(const T& item);
    // ���item�������У�����룬������
    // pair���������������ָ��item����������Ϊtrue��
    //���item������ �����ص�pair�������������ָ��
    //�Ѿ����ڵ� item����������Ϊ��
    // ��������: ���item�������У����Ĵ�С��1

    int erase(const T& item);
    // ���item�����У�ɾ���������� 1
    // ���򣬷��� 0
    // ��������: ���item�����У����Ĵ�С��1

    void erase(iterator pos);
    // ɾ��pos��ָ����
    // ǰ������: ���ǿգ�posָ��������Чλ��
    // ������գ������׳�underflowError �쳣
    // �����������Ч�������׳�referenceError�쳣
    // �������������Ĵ�С�� 1

    void erase(iterator first, iterator last);
    // ɾ��[first, last)����������
    // ǰ������: ���ǿ�
    // ������գ������׳�underflowError �쳣
    // �������������Ĵ�С��С[first, last)��Ԫ�ص���Ŀ

    iterator begin();
    // ����ָ���������������Ԫ�صĵ�����
    const_iterator begin() const;
    // �����汾
    iterator end();
    // ����ָ��������β��֮���λ�õĵ�����
    const_iterator end() const;
    // �����汾

    void display(const int dataWidth = 1,const int screenWidth=64);
    // ��ʾ���ĺ���
    // dataWidth������ڵ�ֵ����Ҫ������ַ���
    // screenWidth����Ļ���

private:
    BSTNode<T> *root;
    // ָ��������ָ��
    int treeSize;
    // ����Ԫ�ص���Ŀ

    BSTNode<T> *getBSTNode(const T& item, BSTNode<T> *lptr, BSTNode<T> *rptr, BSTNode<T> *pptr);
    // �����½ڵ㣬����ָ������ָ��
    // ����ڴ����ʧ�ܣ������׳�memoryAllocationError�쳣

    BSTNode<T> *copyTree(BSTNode<T> *t);
    // �����ƹ��캯���͵ݹ������ʹ�õĵݹ麯��
    // �Ե�ǰ����Ϊ����������һ����

    void deleteTree(BSTNode<T> *t);
    // �����������͵ݹ������ʹ�õĵݹ麯��
    // ɾ���������нڵ�

    BSTNode<T> *findNode(const T& item) const;
    // �����в���item������������У�����ָ�����Ľڵ��ָ��
    // ���򣬷���NULL
    // ��find()��erase()ʹ��

    //�����ṹ
    //���display�нڵ����꣨x��y���ļ�¼
    struct Info
    {
        //Ĭ�Ϲ��캯��
        Info() {}
        //��ʼ�����캯��
        Info(int indent, int level):xIndent(indent),yLevel(level)
        {};
        int xIndent,yLevel;
    };
};
///�½����
template <typename T>
BSTNode<T> *BinSearchTree<T>::getBSTNode(const T& item, BSTNode<T> *lptr,BSTNode<T> *rptr, BSTNode<T> *pptr)
{
	BSTNode<T> *newNode;

	// ��ʼ�����ݺ�����ָ����
	newNode = new BSTNode<T> (item, lptr, rptr, pptr);
	if (newNode == NULL)
		throw memoryAllocationError
          ("BinSearchTree: memory allocation failure");
	return newNode;
}

///������
template <typename T>
BSTNode<T> *BinSearchTree<T>::copyTree(BSTNode<T> *t)
{
	BSTNode<T> *newlptr, *newrptr, *newNode;

	// ���������Ϊ�գ�����NULL
	if (t == NULL)
		return NULL;

	// ���Ƹ�t������������������ֵ��newlptr
	newlptr = copyTree(t->left);

	// ���Ƹ�t������������������ֵ��newrptr
	newrptr = copyTree(t->right);

	// ����洢�ռ����ǰ���ڵ�newNode��������ֵ
	// ָ����ʹָ����������
	// ��newNode���ڵ��Ѿ���������ָ�븳ֵ
	// ���newNode�����������ڵ㣬��ָ��ΪNULL
	newNode = getBSTNode(t->data, newlptr, newrptr, NULL);

	// ��ǰ�ڵ�������һ�ǿ������ĸ��ڵ�
	if (newlptr != NULL)
		newlptr->parent = newNode;
	if (newrptr != NULL)
		newrptr->parent = newNode;

	return newNode;
}

/// ɾ����ǰ����洢����
template <typename T>
void BinSearchTree<T>::deleteTree(BSTNode<T> *t)
{
	// �����ǰ���ڵ�ǿգ����������˳��ɾ�����ڵ�
	if (t != NULL)
	{
		deleteTree(t->left);
		deleteTree(t->right);
		delete t;
	}
}

/// �����в���item������������У�����ָ�����Ľڵ��ָ�룬���򣬷���NULL
template <typename T>
BSTNode<T> *BinSearchTree<T>::findNode(const T& item) const
{
	// �Ӹ�root��ʼ��ʹtѭ�����������
	BSTNode<T> *t = root;

	// ������ʱѭ����ֹ
	// ���ҵ�Ŀ�Ľڵ�ʱѭ����ֹ
	while(t != NULL && !(item == t->data))
		if (item < t->data)
			t = t->left;
		else
			t = t->right;

	// ���ؽڵ�ָ�룬��δ�ҵ�������NULL
	return t;
}

///���캯��1
template <typename T>
BinSearchTree<T>::BinSearchTree(): root(NULL),treeSize(0)
{}
///���캯��2
template <typename T>
BinSearchTree<T>::BinSearchTree(T *first, T *last): root(NULL),treeSize(0)
{
	T *p = first;

	// ��[first, last)�и��������
	while (p != last)
	{
		insert(*p);
		p++;
	}
}

///���ƹ��캯��
template <typename T>
BinSearchTree<T>::BinSearchTree(const BinSearchTree<T>& tree): treeSize(tree.treeSize)
{
	// ����������ǰ����
	root = copyTree(tree.root);
}

///��������
template <typename T>
BinSearchTree<T>::~BinSearchTree()
{
	// ���ڴ����ͷ����ڵ�
	deleteTree(root);

	// ����Ϊ����
	root = NULL;
	treeSize = 0;
}
///���� = �����
template <typename T>
BinSearchTree<T>& BinSearchTree<T>::operator= (const BinSearchTree<T>& rhs)
{
	// �������Ҹ�ֵ�����
	if (this == &rhs)
		return *this;

	// �ͷ�������ռ�ڴ棬ɾ��������
	deleteTree(root);

	// ������rhs�����ж���
	root = copyTree(rhs.root);

	// �������Ĵ�С
	treeSize = rhs.treeSize;

	// ���ص�ǰ���������
	return *this;
}

///����Ŀ��Ԫ��
///item: Ŀ��Ԫ��
///���أ�Ŀ��Ԫ�ص������� δ�ҵ����� end()
template<typename T>
typename BinSearchTree<T>::iterator BinSearchTree<T>::find(const T& item)
{
	BSTNode<T> *curr;

	// ����findNode��������Ŀ����
	curr = findNode (item);

	// ������ҳɹ������ص�ǰֵ�ĵ�����
	// ���򣬷���end()
	if (curr != NULL)
		return iterator(curr, this);
	else
		return end();
}
///����Ŀ��Ԫ��(������)
///item: Ŀ��Ԫ��
///���أ�Ŀ��Ԫ�ص������� δ�ҵ����� end()
template <typename T>
typename BinSearchTree<T>::const_iterator BinSearchTree<T>::find(const T& item) const
{
	BSTNode<T> *curr;

	// ����findNode��������Ŀ����
	curr = findNode (item);

	// ������ҳɹ������ص�ǰֵ�ĳ���������
	// ���򣬷���end()
	if (curr != NULL)
		return const_iterator(curr, this);
	else
		return end();
}
///�ж����Ƿ�Ϊ��
template <typename T>
int BinSearchTree<T>::empty() const
{
	return root == NULL;
}
///�������Ĵ�С
template <typename T>
int BinSearchTree<T>::size() const
{
	return treeSize;
}
///����Ŀ��Ԫ��
///����pair���󣬵���������ָ���½ڵ㣬��������Ϊtrue
template <typename T >
pair<typename BinSearchTree<T> ::iterator, bool> BinSearchTree<T>::insert(const T& item)
{
	// t�Ǳ����ĵ�ǰ�ڵ㣬parent��ǰһ�ڵ�
	BSTNode<T> *t = root, *parent = NULL, *newNode;

	// ������ʱ��ֹ
	while(t != NULL)
	{
		// ����parentָ�룬Ȼ��ȥ��������������
		parent = t;
		// �������ƥ�䣬����pair��
    	//����������ָ������item����������Ϊfalse
		if (item == t->data)
			return pair<iterator, bool> (iterator(t, this), false);
		else if (item < t->data)
			t = t->left;
		else
			t = t->right;
	}

	// �����µ�Ҷ���
	newNode = getBSTNode(item,NULL,NULL,parent);

	// ������ڵ�Ϊ�գ������ڵ���Ϊ���ڵ�
	// ���ּ��ǲ���ǰΪ����������
	if (parent == NULL)
		root = newNode;
	else if (item < parent->data)
		// ��Ϊ���ӽڵ����
		parent->left = newNode;
	else
		// ��Ϊ���ӽڵ����
		parent->right = newNode;

	// ���Ĵ�С�� 1
	treeSize++;

	// ����pair���󣬵���������ָ���½ڵ㣬��������Ϊtrue
	return pair<iterator, bool> (iterator(newNode, this), true);
}
///ɾ��ĳ���
///pos: Ҫɾ���Ľ���ָ��
template <typename T>
void BinSearchTree<T>::erase(iterator pos)
{
	// dNodePtr ָ��ָ�򽫱�ɾ���Ľڵ�D
	// pNodePtr ָ��ָ��ڵ� D�ĸ��ڵ�P
	// rNodePtr ָ��ָ���滻�ڵ�D�Ľڵ�R
	BSTNode<T> *dNodePtr = pos.nodePtr, *pNodePtr, *rNodePtr;

	if (treeSize == 0)
 		throw
			underflowError("BinSearchTree erase(): tree is empty");

	if (dNodePtr == NULL)
 		throw
			referenceError("BinSearchTree erase(): invalid iterator");

	pNodePtr = dNodePtr->parent;

	// ���D��һ���ӽڵ�Ϊ��
	// �滻�ڵ�����һ���ӽڵ�
	if (dNodePtr->left == NULL || dNodePtr->right == NULL)
	{
		if (dNodePtr->right == NULL)
			rNodePtr = dNodePtr->left;
		else
			rNodePtr = dNodePtr->right;

		// ���rNodePtrΪNULL����D�ڵ���Ҷ�ڵ㣬 ���ÿ����滻
		if (rNodePtr != NULL)
			// R�ĸ��ڵ����ΪD�ĸ��ڵ�
			rNodePtr->parent = pNodePtr;
	}
	// �ڵ�D����������������
	else
	{
		// ���ҽڵ�D���滻�ڵ�R����ʹR��������
		// ����ѡ������������ߵĽڵ����滻��
		// ����ڵ�ֵ�Ǵ���D �Ľڵ�����С��
		// �ҵ��󽫸ýڵ�����жϿ�
		// unlink the node from the tree.

		// pOfRNodePtr ָ��ָ���滻�ڵ�ĸ��ڵ�
		BSTNode<T> *pOfRNodePtr = dNodePtr;

		// ���ܵ��滻�ڵ��ڽڵ�D��������
		rNodePtr = dNodePtr->right;

		// ���Žڵ�D���ӽڵ���������½�
		// �½������б�����ǰ�ڵ�����ĸ��ڵ�
		// ��������Ҷ��㣬ͣ�£��ҵ����滻�ڵ�
		while(rNodePtr->left != NULL)
		{
			pOfRNodePtr = rNodePtr;
			rNodePtr = rNodePtr->left;
		}

  		//D�����ӽڵ㲻����������������
		if (pOfRNodePtr == dNodePtr)
		{
			// ��ɾ���ڵ�����ӽڵ����滻�ڵ�
			// ��D�ڵ������������R�ڵ��������
			rNodePtr->left = dNodePtr->left;
			// R�ڵ�ĸ��ڵ����ΪD�ڵ�ĸ��ڵ�
			rNodePtr->parent = pNodePtr;
			// ��D����������ڵ�R����
			dNodePtr->left->parent = rNodePtr;
		}
		else
		{
			// D�ڵ�����ӽڵ���������зǿյ�����
			// ͨ����R�ڵ����������ΪR�ڵ�ĸ��ڵ����������
			// ��R�ڵ�����жϿ�����
			pOfRNodePtr->left = rNodePtr->right;

			// R�ڵ�����ӽڵ�ĸ��ڵ����ΪR�ڵ�ĸ��ڵ�
			if (rNodePtr->right != NULL)
				rNodePtr->right->parent = pOfRNodePtr;

			// ���滻�ڵ�R������ԭ�ڵ�D��λ��
			// ʹD���ӽڵ��ΪR���ӽڵ�
			rNodePtr->left = dNodePtr->left;
			rNodePtr->right = dNodePtr->right;
			// R�ڵ�ĸ��ڵ���ΪD�ڵ�ĸ��ڵ�
			rNodePtr->parent = pNodePtr;
			// ʹ�¹�����R�ڵ���ӽڵ�ĸ��ڵ�ָ��ָ��ڵ�R
			rNodePtr->left->parent = rNodePtr;
			rNodePtr->right->parent = rNodePtr;
		}
	}

	// ��ɽڵ�R���µĸ��ڵ������

	// �ڵ�D�Ǹ��ڵ������
	if (pNodePtr == NULL)
		root = rNodePtr;
	// ��R��P����ȷ��֧����
	else if (dNodePtr->data < pNodePtr->data)
		pNodePtr->left = rNodePtr;
	else
		pNodePtr->right = rNodePtr;

	// ���ڴ���ɾ���ڵ�D�����Ĵ�С�� 1
	delete dNodePtr;
	treeSize--;
}
///ɾ��Ŀ��Ԫ��
///item: Ҫɾ����Ԫ��
///���أ��ɹ�ɾ������1�����򷵻�0
template <typename T>
int BinSearchTree<T>::erase(const T& item)
{
	int numberErased = 1;
	// �����в���Ŀ����
	BSTNode<T> *p  = findNode(item);

	// ������ҳɹ���ɾ��
	if (p != NULL)
		erase(iterator(p,this));
	else
		numberErased = 0;

	return numberErased;
}
///ɾ��һ��Ԫ��
///first: ��ʼ������
///last: ��ֹ������
template <typename T>
void BinSearchTree<T>::erase(iterator first, iterator last)
{
	if (treeSize == 0)
 		throw
			underflowError("BinSearchTree erase(): tree is empty");

	iterator p = first;

	if (first == begin() && last == end())
	{
		// ���Ǳ�Ҫ��ɾ��������
		deleteTree(root);

		// ����Ϊ��
		root = NULL;
		treeSize = 0;
	}
	else
		// ɾ�������������ÿ��Ԫ��
		while (p != last)
			erase(p++);
}
///���ض������Ŀ�ͷ
template <typename T>
typename BinSearchTree<T>::iterator BinSearchTree<T>::begin()
{
	BSTNode<T> *curr = root;

	// ������ǿգ���������ĵ�һ���ڵ��ǴӾ�����ڵ�����Ľڵ�
	if (curr != NULL)
		while (curr->left != NULL)
			curr = curr->left;

	// ͨ��˽�й��캯�����ɷ���ֵ
	return iterator(curr, this);
}
///���ض������Ŀ�ͷ(������)
template <typename T>
typename BinSearchTree<T>::const_iterator BinSearchTree<T>::begin() const
{
	const BSTNode<T> *curr = root;

	// ������ǿգ���������ĵ�һ���ڵ��ǴӾ�����ڵ�����Ľڵ�
	if (curr != NULL)
		while (curr->left != NULL)
			curr = curr->left;

	// ͨ��˽�й��캯�����ɷ���ֵ
	return const_iterator(curr, this);
}
///���ض������Ľ�β
template <typename T>
typename BinSearchTree<T>::iterator BinSearchTree<T>::end()
{
	// �Ժ�ֵΪNULL��BSTNodeָ��ĵ�����ָʾ��������λ��
	return iterator(NULL, this);
}
///���ض������Ľ�β(������)
template <typename T>
typename BinSearchTree<T>::const_iterator BinSearchTree<T>::end() const
{
	// �Ժ�ֵΪNULL��BSTNodeָ��ĵ�����ָʾ��������λ��
	return const_iterator(NULL, this);
}
///��ʾ������
template <typename T>
void BinSearchTree<T>::display(const int dataWidth,const int screenWidth)
{
	// �洢ÿ���ڵ�Ķ���
   queue<BSTNode<T> *> q;
   //��Žڵ��ӡ��Ϣ�Ķ��У�
   queue<Info>QI;
   BSTNode<T> *currNode;
   Info currInfo;
   int units (screenWidth/dataWidth);
   int offset = units/2;
   //��ǰ�ڵ��������
   int currlevel = -1;
   //��ǰ�ڵ��ͬ���ǰһ�ڵ��������
   int preX;

   //�����Ϊ�գ��˳�
   if ((*this).empty())
      return;

   // �ڶ���q�в�����ڵ�����ʼ������
   q.push(root);
   //�ڶ���QI�в�����ڵ������ʼ������
   QI.push(Info(offset,0));

   // �����������̣�ֱ�����п�
   while(!q.empty())
   {
      // �Ӷ�����ɾ��ǰ�˽ڵ㣬�����ʽڵ�
      currNode = q.front();
      q.pop();
      currInfo = QI.front();
      QI.pop();
      if( currInfo.yLevel != currlevel )
      {
           //������
           cout<<"\n\n" ;
          //���У���ʼλ��Ϊ0
          preX = 0;
          //��Ů�ڵ��ƫ����Ϊ �ϲ�ڵ��1/2
          offset /= 2;
          //���µ�ǰ�ڵ�������
          currlevel = currInfo.yLevel;
      }

      //����Ӧλ������ڵ����ͷ��Ԫ�ص�ֵ������ΪT��
      //���Ǽٶ�����T�����˺��ʵ�<<������
      cout<<setw((currInfo.xIndent-preX)*dataWidth)
          <<currNode->data;

      if( currNode->left != NULL )
      {
          //���ӽڵ����
          q.push(currNode->left) ;
          //���ӽڵ�λ����Ϣ���
          QI.push(Info(currInfo.xIndent-offset,currInfo.yLevel+1));
      }
      if( currNode->right != NULL )
      {
          //���ӽڵ����
          q.push(currNode->right) ;
          //���ӽڵ�λ����Ϣ���
          QI.push(Info(currInfo.xIndent+offset,currInfo.yLevel+1));
      }
      preX = currInfo.xIndent;
   } //whileѭ��
}

/// �˳�����ʾ������������Ļ�������
int TEST_BST()
{
	// �������ù��캯������һ�ö�������������������"insight"
	// ֮��Ը�������������insert()��erase()��display()
	cout <<"********************��ʾ�������������ܵ�Ӧ�ó���************************"<<endl;

	//�˲�����ʾ���Ĺ�������
	char* ch = (char *)"insight";
	BinSearchTree<char> t(ch, ch+7);
	BinSearchTree<char>::iterator iter;
	const int charWidth=1;
	const int ScreenWidth=80;
	cout << "��ʼ��:" << endl;
	t.display(charWidth,ScreenWidth);
	cout << endl << endl;
	cout << "������������Ԫ��Ϊ:"<<endl;
	for(iter = t.begin();iter !=t.end();iter++)
		cout<< *iter;
	cout <<endl;

	//�˲�����ʾ���Ĳ������
	BinSearchTree<char>::iterator tIter;
	pair<BinSearchTree<char>::iterator, bool> p;
	string str = "codimg" ;
	cout << "��ʼ����"<<str <<"��������"<<endl;
	for( unsigned int i = 0; i < str.length(); i++ )
	{
		p = t.insert(str[i]);
		if(p.second == false)
			cout << str[i] << "���ظ���ĸ" << endl;
	}
	cout << "��ʱ��Ϊ��" << endl;
	t.display(charWidth,ScreenWidth);
	cout << endl <<endl;
		cout << "������������ʱ��Ԫ��Ϊ��"<<endl;
	for(iter = t.begin();iter !=t.end();iter++)
		cout<< *iter;
	cout <<endl;

	//�˲�����ʾ����ɾ������
	cout <<"����ڵ�ɾ��,ֱ����Ϊ�գ���ʼ����"<<endl;
	iter = t.begin();
	while(iter != t.end())
	{
		cout << *iter<<"��ɾ�������"<<endl;
		t.erase(iter++);
		t.display(charWidth,ScreenWidth);
		cout<<endl<<endl;
	}

	cout<<"�밴�س�����������:" ;
	cin.get();
	return 0;
}

#endif  // BINARY_SEARCH_TREE_CLASS
