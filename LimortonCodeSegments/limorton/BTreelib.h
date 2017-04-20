#ifndef BTREELIB_H_INCLUDED
#define BTREELIB_H_INCLUDED
// FileName: BTreelib.h
// 二叉树类库函数头文件
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <queue>


#include "BTNode.h"		// use BTNode class

using namespace std;

#if 0
// 中序递归访问二叉树，visit函数是定制函数, han shu ming zuo wei can shu
template <typename T>
void inOrder(BTNode<T> *t, void visit(T& item));

// 后序递归访问二叉树，visit函数是定制函数
template <typename T>
void postOrder(BTNode<T> *t, void visit(T& item));

// 按照层次顺序遍历访问二叉树，visit是定制函数
template <typename T>
void levelOrder(BTNode<T> *t, void visit(T& item));

// 在引用参数count中累计二叉树叶节点的的数目,count被初始化为0
template <typename T>
void countLeaf(BTNode<T> *t, int& count);

// 返回二叉树的深度
template <typename T>
int depth (BTNode<T> *t);

// 生成树t的副本，返回新的副本的指针
template <typename T>
BTNode<T> *copyTree(BTNode<T> *t);

// 遍历并删除二叉树的节点
template <typename T>
void deleteTree(BTNode<T> *t);

// 用deleteTree()删除树的所有节点，并将树根节点赋值为空
template <typename T>
void clearTree(BTNode<T> * & t);

// 垂直显示二叉树，输出节点值
//节点值的宽度不大于dataWidth,屏幕宽度为screenWidth
template <typename T>
void displayTree(const BTNode<T> *t, const int dataWidth=1,const int screenWidth=64);

//第二个参数为函数指针，只需要传递一个返回类型和参数类型都匹配的函数指针作实参即可
template <typename T>
void inOrder(BTNode<T> *t, void visit(T& item))
{
   // 当子树为空时，递归遍历终止
   if (t != NULL)
   {
      inOrder(t->left, visit);	// 遍历左子树
      visit(t->data);	// 访问节点
      inOrder(t->right, visit);	// 遍历右子树
   }
}

template <typename T>
void postOrder(BTNode<T> *t, void visit(T& item))
{
   // 当子树为空时，递归遍历终止
   if (t != NULL)
   {
      postOrder(t->left, visit);	// 遍历左子树
      postOrder(t->right, visit);	// 遍历右子树
      visit(t->data);			// 访问节点
   }
}

template <typename T>
void levelOrder(BTNode<T> *t, void visit(T& item))
{
   // 存储每个节点的兄弟节点到队列中，这样可以按树的下一层的顺序访问它们
   queue<BTNode<T> *> q;
   BTNode<T> *p;

   // 在队列中插入根节点来初始化队列
   q.push(t);

   // 继续迭代过程，直到队列空
   while(!q.empty())
   {
      // 从队列中删除前端节点，并访问节点
      p = q.front();
      q.pop();
      visit( p->data);

	  // 如果存在左子节点，将它插入到队列
      if(p->left != NULL)
			q.push(p->left);
      // 如果存在右子节点，插入到队列，使它紧邻其兄弟
      if(p->right != NULL)
			q.push(p->right);
   }
}

//引用参数count被初始化为0
template <typename T>
void countLeaf (BTNode<T> *t, int& count)
{
   if (t != NULL)
   {
      // 检查t是否为叶节点
      // 如果是，count增1
      if (t->left == NULL && t->right == NULL)
         count++;
      countLeaf(t->left, count);	// 左子树遍历，计数
      countLeaf(t->right, count);	// 右子树遍历，计数
   }
}

//使用后序遍历算法决定树深度
template <typename T>
int depth (BTNode<T> *t)
{
   int depthLeft, depthRight, depthval;
   if (t == NULL)
	  // 空树的深度定为-1
	  depthval = -1;
   else
	{
		//查找t的左子树的深度
		depthLeft= depth(t->left);
		//查找t的右子树的深度
		depthRight= depth(t->right);
		//以t为根的树的深度为：1+ （两棵子树的最大深度）
		depthval = 1 +
			(depthLeft > depthRight ? depthLeft : depthRight);
   }
   return depthval;
}

template <typename T>
BTNode<T> *copyTree(BTNode<T> *t)
{
   // newNode 指向算法产生的新节点，
   //newLptr和newRptr指向newNode的左、右子树
   BTNode<T> *newLeft, *newRight, *newNode;

   // 到达空树时停止递归遍历
   if (t == NULL)
      return NULL;

   // 自底向上构造新树：先构造两个子树，然后构造父节点。
   // 在节点t，生成左子树的副本，将其根节点指针赋值给newLeft
   newLeft = copyTree(t->left);
   // 生成右子树的副本，将其根节点指针赋值给newRight
   newRight = copyTree(t->right);

   // 生成新节点，其节点值与t的值相同，其子节点是被复制的t的子树
   newNode = new BTNode<T> (t->data, newLeft, newRight);

   // 返回新复制的树的根节点的指针
   return newNode;
}

template <typename T>
void deleteTree(BTNode<T> *t)
{
    // 后序遍历，删除t的左、右子树，然后删除节点t
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
	t = NULL; //此时根为NULL
}

//辅助结构
//存放displayTree中节点坐标（x，y）的记录
struct Info
{
    //默认构造函数
    Info() {}
    //初始化构造函数
    Info(int indent, int level):xIndent(indent),yLevel(level) {};
    int xIndent,yLevel;
};

template <typename T>
void displayTree(BTNode<T> *t, const int dataWidth,const int screenWidth=64)
{
   // 存储每个节点的队列
   queue<BTNode<T> *> q;
   //存放节点打印信息的队列；

   queue<Info>QI;
   BTNode<T> *currNode;
   Info currInfo;
   int units (screenWidth/dataWidth);
   int offset = units/2;
   //当前节点的列坐标
   int currlevel = -1;
   //当前节点的同层的前一节点的行坐标
   int preX;

   //如果树为空，退出
   if (t == NULL)
      return;

   // 在队列q中插入根节点来初始化队列
   q.push(t);
   //在队列QI中插入根节点坐标初始化队列
   QI.push(Info(offset,0));

   // 继续迭代过程，直到队列空
   while(!q.empty())
   {
      // 从队列中删除前端节点，并访问节点
      currNode = q.front();
      q.pop();
      currInfo = QI.front();
      QI.pop();
      if( currInfo.yLevel != currlevel )
      {
           //换两行
           cout<<"\n\n" ;
          //新行，起始位置为0
          preX = 0;
          //子女节点的偏移量为 上层节点的1/2
          offset /= 2;
          //更新当前节点坐标层次
          currlevel = currInfo.yLevel;
      }

      //在相应位置输出节点队列头部元素的值，类型为T，
      //我们假定类型T定义了合适的<<操作符
      cout<<setw((currInfo.xIndent-preX)*dataWidth)
          <<currNode->data;

      if( currNode->left != NULL )
      {
          //左子节点入队
          q.push(currNode->left) ;
          //左子节点位置信息入队
          QI.push(Info(currInfo.xIndent-offset,currInfo.yLevel+1));
      }
      if( currNode->right != NULL )
      {
          //右子节点入队
          q.push(currNode->right) ;
          //右子节点位置信息入队
          QI.push(Info(currInfo.xIndent+offset,currInfo.yLevel+1));
      }
      preX = currInfo.xIndent;
   } //while循环
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
//C++中struct对C中的struct进行了扩充
//详见CSDN博客：http://blog.csdn.net/yuliu0552/article/details/6717915
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

// 此程序演示二叉树的各种算法
// 首先构建一棵二叉树，在屏幕上垂直输出
// 中序、后序及层次遍历二叉树
// 计算树的高度，并计算叶节点个数
// 并验证了复制、删除二叉树的操作

#include <iostream>

#include "BTNode.h"   // BTNode类
#include "BTreelib.h" // BTNode库

using namespace std;

//实用函数makeCharTree，生成一棵以字符为节点数据的二叉树
BTNode<char> *makeCharTree();

//遍历算法的visit函数，输出节点数据值
void printChar(char& elem)
{
    string seperator = "  ";
    cout <<  elem << seperator;
}

int TEST_TREE()
{
  //二叉树的根
    BTNode<char> *root1, *root2;

  // 构造二叉树
  root1 = makeCharTree();

  // 显示树
  cout << "原始树的图示：" << endl;
  const int charWidth=1;
  const int ScreenWidth=64;
  displayTree(root1, charWidth,ScreenWidth);
  cout << endl << endl;

  //节点的中序遍历
    cout << "中序遍历：" ;
    inOrder(root1, printChar);
    cout << endl;

    //节点的后序遍历
    cout << "后序遍历：" ;
    postOrder(root1, printChar);
    cout << endl;

    //节点的层次遍历
    cout << "层次遍历：" ;
    levelOrder(root1, printChar);
    cout << endl<<endl;

    //叶结点计数
    int leafCount = 0;
    countLeaf(root1, leafCount);
    cout << "叶节点数目是："
         << leafCount << endl;
    cout << "树的深度是："
         << depth (root1) <<endl;

  //生成root1的副本，根为root2
  root2 = copyTree(root1);

  // 显示树的副本
  cout << "原始树的副本的图示：" << endl;
  displayTree(root2, charWidth,ScreenWidth);
  cout << endl;

  // 清空两棵树
  clearTree(root1);
  clearTree(root2);

  cout << "对root1调用的clearTree之后的图示：" << endl;
  displayTree(root1, charWidth,ScreenWidth);
  cout << endl << endl;

    cout<<"按回车键结束程序:" << endl;
    cin.get();
  return 0;
}


BTNode<char> *makeCharTree()
{
  // 9 BTNode 指针，指向9个节点项
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
