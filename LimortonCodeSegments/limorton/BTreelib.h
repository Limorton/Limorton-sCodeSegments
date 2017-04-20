#ifndef BTREELIB_H_INCLUDED
#define BTREELIB_H_INCLUDED
// FileName: BTreelib.h
// ��������⺯��ͷ�ļ�
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>


#include "BTNode.h"		// use BTNode class

using namespace std;

#if 0
// ����ݹ���ʶ�������visit�����Ƕ��ƺ���, han shu ming zuo wei can shu
template <typename T>
void inOrder(BTNode<T> *t, void visit(T& item));

// ����ݹ���ʶ�������visit�����Ƕ��ƺ���
template <typename T>
void postOrder(BTNode<T> *t, void visit(T& item));

// ���ղ��˳��������ʶ�������visit�Ƕ��ƺ���
template <typename T>
void levelOrder(BTNode<T> *t, void visit(T& item));

// �����ò���count���ۼƶ�����Ҷ�ڵ�ĵ���Ŀ,count����ʼ��Ϊ0
template <typename T>
void countLeaf(BTNode<T> *t, int& count);

// ���ض����������
template <typename T>
int depth (BTNode<T> *t);

// ������t�ĸ����������µĸ�����ָ��
template <typename T>
BTNode<T> *copyTree(BTNode<T> *t);

// ������ɾ���������Ľڵ�
template <typename T>
void deleteTree(BTNode<T> *t);

// ��deleteTree()ɾ���������нڵ㣬���������ڵ㸳ֵΪ��
template <typename T>
void clearTree(BTNode<T> * & t);

// ��ֱ��ʾ������������ڵ�ֵ
//�ڵ�ֵ�Ŀ�Ȳ�����dataWidth,��Ļ���ΪscreenWidth
template <typename T>
void displayTree(const BTNode<T> *t, const int dataWidth=1,const int screenWidth=64);

//�ڶ�������Ϊ����ָ�룬ֻ��Ҫ����һ���������ͺͲ������Ͷ�ƥ��ĺ���ָ����ʵ�μ���
template <typename T>
void inOrder(BTNode<T> *t, void visit(T& item))
{
   // ������Ϊ��ʱ���ݹ������ֹ
   if (t != NULL)
   {
      inOrder(t->left, visit);	// ����������
      visit(t->data);	// ���ʽڵ�
      inOrder(t->right, visit);	// ����������
   }
}

template <typename T>
void postOrder(BTNode<T> *t, void visit(T& item))
{
   // ������Ϊ��ʱ���ݹ������ֹ
   if (t != NULL)
   {
      postOrder(t->left, visit);	// ����������
      postOrder(t->right, visit);	// ����������
      visit(t->data);			// ���ʽڵ�
   }
}

template <typename T>
void levelOrder(BTNode<T> *t, void visit(T& item))
{
   // �洢ÿ���ڵ���ֵܽڵ㵽�����У��������԰�������һ���˳���������
   queue<BTNode<T> *> q;
   BTNode<T> *p;

   // �ڶ����в�����ڵ�����ʼ������
   q.push(t);

   // �����������̣�ֱ�����п�
   while(!q.empty())
   {
      // �Ӷ�����ɾ��ǰ�˽ڵ㣬�����ʽڵ�
      p = q.front();
      q.pop();
      visit( p->data);

	  // ����������ӽڵ㣬�������뵽����
      if(p->left != NULL)
			q.push(p->left);
      // ����������ӽڵ㣬���뵽���У�ʹ���������ֵ�
      if(p->right != NULL)
			q.push(p->right);
   }
}

//���ò���count����ʼ��Ϊ0
template <typename T>
void countLeaf (BTNode<T> *t, int& count)
{
   if (t != NULL)
   {
      // ���t�Ƿ�ΪҶ�ڵ�
      // ����ǣ�count��1
      if (t->left == NULL && t->right == NULL)
         count++;
      countLeaf(t->left, count);	// ����������������
      countLeaf(t->right, count);	// ����������������
   }
}

//ʹ�ú�������㷨���������
template <typename T>
int depth (BTNode<T> *t)
{
   int depthLeft, depthRight, depthval;
   if (t == NULL)
	  // ��������ȶ�Ϊ-1
	  depthval = -1;
   else
	{
		//����t�������������
		depthLeft= depth(t->left);
		//����t�������������
		depthRight= depth(t->right);
		//��tΪ�����������Ϊ��1+ �����������������ȣ�
		depthval = 1 +
			(depthLeft > depthRight ? depthLeft : depthRight);
   }
   return depthval;
}

template <typename T>
BTNode<T> *copyTree(BTNode<T> *t)
{
   // newNode ָ���㷨�������½ڵ㣬
   //newLptr��newRptrָ��newNode����������
   BTNode<T> *newLeft, *newRight, *newNode;

   // �������ʱֹͣ�ݹ����
   if (t == NULL)
      return NULL;

   // �Ե����Ϲ����������ȹ�������������Ȼ���츸�ڵ㡣
   // �ڽڵ�t�������������ĸ�����������ڵ�ָ�븳ֵ��newLeft
   newLeft = copyTree(t->left);
   // �����������ĸ�����������ڵ�ָ�븳ֵ��newRight
   newRight = copyTree(t->right);

   // �����½ڵ㣬��ڵ�ֵ��t��ֵ��ͬ�����ӽڵ��Ǳ����Ƶ�t������
   newNode = new BTNode<T> (t->data, newLeft, newRight);

   // �����¸��Ƶ����ĸ��ڵ��ָ��
   return newNode;
}

template <typename T>
void deleteTree(BTNode<T> *t)
{
    // ���������ɾ��t������������Ȼ��ɾ���ڵ�t
    if (t != NULL)
    {
        deleteTree(t->left);
        deleteTree(t->right);
        delete t;
    }
}

template <typename T>
void clearTree(BTNode<T> * & t)
{
	deleteTree(t);
	t = NULL; //��ʱ��ΪNULL
}

//�����ṹ
//���displayTree�нڵ����꣨x��y���ļ�¼
struct Info
{
    //Ĭ�Ϲ��캯��
    Info() {}
    //��ʼ�����캯��
    Info(int indent, int level):xIndent(indent),yLevel(level) {};
    int xIndent,yLevel;
};

template <typename T>
void displayTree(BTNode<T> *t, const int dataWidth,const int screenWidth=64)
{
   // �洢ÿ���ڵ�Ķ���
   queue<BTNode<T> *> q;
   //��Žڵ��ӡ��Ϣ�Ķ��У�

   queue<Info>QI;
   BTNode<T> *currNode;
   Info currInfo;
   int units (screenWidth/dataWidth);
   int offset = units/2;
   //��ǰ�ڵ��������
   int currlevel = -1;
   //��ǰ�ڵ��ͬ���ǰһ�ڵ��������
   int preX;

   //�����Ϊ�գ��˳�
   if (t == NULL)
      return;

   // �ڶ���q�в�����ڵ�����ʼ������
   q.push(t);
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

#else
template <class T>
void inOrder(BTNode<T> *t, void visit(T& item)){
    if(t != nullptr){
        inOrder(t -> left, visit);
        visit(t -> data);
        inOrder(t -> right, visit);
    }
}

template <class T>
void postOrder(BTNode<T> *t, void visit(T& item)){
    if(t != nullptr){
        postOrder(t -> left, visit);
        postOrder(t -> right, visit);
        visit(t -> data);
    }
}

template <class T>
void levelOrder(BTNode<T> *t, void visit(T& item)){
    queue<BTNode<T> *> q;
    BTNode<T> *p;
    q.push(t);
    while(!q.empty()){
        p = q.front();
        q.pop();
        visit(p -> data);

        if(p -> left != nullptr)
            q.push(p -> left);
        if(p -> right != nullptr)
            q.push(p -> right);
    }
}

template <class T>
void countLeaf(BTNode<T> *t, int& count){
    if(t != nullptr){
       if(t -> left == nullptr && t -> right == nullptr)
            count++;
       countLeaf(t -> left, count);
       countLeaf(t -> right, count);
    }
}

template <class T>
int depth(BTNode<T> *t){
    int depthLeft, depthRight, depthval;
    if(t == nullptr)
        depthval = -1;
    else{
        depthLeft = depth(t -> left);
        depthRight = depth(t -> right);
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
    }
    return depthval;
}

template <class T>
BTNode<T> *copyTree(BTNode<T> *t){
    BTNode<T> *newLeft, *newRight, *newNode;

    if(t == nullptr){
        return nullptr;
    }

    newLeft = copyTree(t -> left);
    newRight = copyTree(t -> right);
    newNode = new BTNode<T>(t ->data, newLeft, newRight);
    return newNode;
}

template <class T>
void deleteTree(BTNode<T> *t){
    if(t != nullptr){
        deleteTree(t -> left);
        deleteTree(t -> right);
        delete t;
    }
}

template <class T>
void clearTree(BTNode<T> * & t){
    deleteTree(t);
    t = nullptr;
}
//C++��struct��C�е�struct����������
//���CSDN���ͣ�http://blog.csdn.net/yuliu0552/article/details/6717915
struct Info{
    Info(){}
    Info(int indent, int level):xIndent(indent), yLevel(level){};
    int xIndent, yLevel;
};

template <class T>
void displayTree(BTNode<T> *t, const int dataWidth, const int screenWidth = 64){
    queue<BTNode<T> *> q;
    queue<Info> QI;
    BTNode<T> *currNode;
    Info currInfo;
    int units(screenWidth / dataWidth);
    int offset = units / 2;
    int currlevel = -1;
    int preX;
    if(t == nullptr)
        return;
    q.push(t);
    QI.push(Info(offset, 0));
    while(!q.empty()){
        currNode = q.front();
        q.pop();
        currInfo = QI.front();
        QI.pop();
        if(currInfo.yLevel != currlevel){
            cout << "\n\n";
            preX = 0;
            offset /= 2;
            currlevel = currInfo.yLevel;
        }
        cout << setw((currInfo.xIndent - preX)* dataWidth)
            << currNode -> data;
        if(currNode -> left != nullptr){
            q.push(currNode -> left);
            QI.push(Info(currInfo.xIndent - offset, currInfo.yLevel + 1));
        }
        if(currNode -> right != nullptr){
            q.push(currNode -> right);
            QI.push(Info(currInfo.xIndent + offset, currInfo.yLevel + 1));
        }
        preX = currInfo.xIndent;
    }//end while
}
#endif // 0

// File: testBTree.cpp

// �˳�����ʾ�������ĸ����㷨
// ���ȹ���һ�ö�����������Ļ�ϴ�ֱ���
// ���򡢺��򼰲�α���������
// �������ĸ߶ȣ�������Ҷ�ڵ����
// ����֤�˸��ơ�ɾ���������Ĳ���

#include <iostream>

#include "BTNode.h"   // BTNode��
#include "BTreelib.h" // BTNode��

using namespace std;

//ʵ�ú���makeCharTree������һ�����ַ�Ϊ�ڵ����ݵĶ�����
BTNode<char> *makeCharTree();

//�����㷨��visit����������ڵ�����ֵ
void printChar(char& elem)
{
    string seperator = "  ";
    cout <<  elem << seperator;
}

int TEST_TREE()
{
  //�������ĸ�
    BTNode<char> *root1, *root2;

  // ���������
  root1 = makeCharTree();

  // ��ʾ��
  cout << "ԭʼ����ͼʾ��" << endl;
  const int charWidth=1;
  const int ScreenWidth=64;
  displayTree(root1, charWidth,ScreenWidth);
  cout << endl << endl;

  //�ڵ���������
    cout << "���������" ;
    inOrder(root1, printChar);
    cout << endl;

    //�ڵ�ĺ������
    cout << "���������" ;
    postOrder(root1, printChar);
    cout << endl;

    //�ڵ�Ĳ�α���
    cout << "��α�����" ;
    levelOrder(root1, printChar);
    cout << endl<<endl;

    //Ҷ������
    int leafCount = 0;
    countLeaf(root1, leafCount);
    cout << "Ҷ�ڵ���Ŀ�ǣ�"
         << leafCount << endl;
    cout << "��������ǣ�"
         << depth (root1) <<endl;

  //����root1�ĸ�������Ϊroot2
  root2 = copyTree(root1);

  // ��ʾ���ĸ���
  cout << "ԭʼ���ĸ�����ͼʾ��" << endl;
  displayTree(root2, charWidth,ScreenWidth);
  cout << endl;

  // ���������
  clearTree(root1);
  clearTree(root2);

  cout << "��root1���õ�clearTree֮���ͼʾ��" << endl;
  displayTree(root1, charWidth,ScreenWidth);
  cout << endl << endl;

    cout<<"���س�����������:" << endl;
    cin.get();
  return 0;
}


BTNode<char> *makeCharTree()
{
  // 9 BTNode ָ�룬ָ��9���ڵ���
  BTNode<char> *root, *b, *c, *d, *e, *f, *g, *h, *i;
  g = new BTNode<char> ('G');
  h = new BTNode<char> ('H');
  i = new BTNode<char> ('I');
  d = new BTNode<char> ('D',(BTNode<char> *)NULL, g);
  e = new BTNode<char> ('E',h, i);
  f = new BTNode<char> ('F');
  b = new BTNode<char> ('B',d, (BTNode<char> *)NULL);
  c = new BTNode<char> ('C',e, f);
  root = new BTNode<char> ('A',b, c);
  return root;
}


#endif // BTREELIB_H_INCLUDED
