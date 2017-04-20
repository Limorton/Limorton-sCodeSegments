/**农夫过河问题演示，涉及深度优先搜索与广度优先搜索**/
#ifndef NONGFUGUOHE_H
#define NONGFUGUOHE_H
#include <iostream>
#include <bitset>
#include <vector>
#include <queue>

using namespace std;

//过河者，共4种对象
enum Wader{
    cabbage,    //默认为1
    goat,       //默认为2
    wolf,       //默认为3
    farmer      //默认为4
};
//过河状态类型，bit分别对应4种过河对象
typedef bitset<4> bitvec;

//判断待过河的对象wader是否与农夫farmer在河的同一侧
//state为当前状态
inline bool withFarmer(int wader, bitvec& state){
    return (state[farmer] == state[wader]);
}

//判断状态是否安全，state是当前状态
bool is_safe(const bitvec& state){
    //sheep eats cabbage
    if((state[cabbage] == state[goat]) && \
       (state[farmer ]) != state[goat])
        return false;
    //wolf eats sheep
    if((state[wolf] == state[goat]) && \
       (state[farmer ]) != state[goat])
        return false;
    //other states
    return true;
}



//搜索并显示实际方案
void displayRoute(const vector<int>&path){
    //如果path[15]状态没有前驱则表示无法成功达到目标状态
    if(path[15] == -1){
        cout << "该过河问题无解" << endl;
        return;
    }
    //将整数表示的路径转换为布尔矢量表示的状态路径
    //存储状态路径的容器
    deque<bitvec> statePath;
    for(int i = 15; i >0; i = path[i])
        statePath.push_front(i);
        //反向插入，完成路径从初始状态到目的状态的转换
        //隐式类型转换：int -> bitset<4>
    //将初始状态插入
    statePath.push_front(0);
    //当前状态变量与转换变量
    bitvec current, next, trans;
    bool crossed = true;
    int step = 1;
    for(unsigned int i = 1; i < statePath.size(); i++){
        current = statePath[i - 1];
        next = statePath[i];
        //状态变量中的变化位
        trans = current ^ next;
        //获取状态发生变化的对象
        int wader = -1;
        for(int i = 0; i <= 2; i++){
            if(trans.test(i)){
                wader = i;
                break;
            }
        }
        cout << "步骤" << step++ << ":";
        switch(wader){
        case goat:
            cout << "农夫把羊带" << (crossed ? "到河彼岸":"回河此岸") << endl;
            break;
        case cabbage:
            cout << "农夫把白菜带" << (crossed ? "到河彼岸":"回河此岸") << endl;
            break;
        case wolf:
            cout << "农夫把狼带" << (crossed ? "到河彼岸":"回河此岸") << endl;
            break;
        case -1:
            cout << "农夫独自" << (crossed ? "到河彼岸":"回河此岸") << endl;
            break;
        }
        crossed = !crossed;
    }
    cout << "\n过河问题求解成功！" << endl;
}
//搜索过河的方法路径
void findRoute(vector<int>& path){
    //待发现的各个状态
    /*深度优先搜索使用stack存储，广度优先搜索使用queue存储*/
    stack<int> discovering;
    //queue<int> discovering;
    //初始状态为0000
    discovering.push(0x00);
    //初始状态路径初始化
    path[0] = 0;
    //搜索下一个状态，并且尚未达到最终状态
    while(!discovering.empty() && (path[15] == -1)){
        //获取当前待发现状态，隐式转换 int -> bitset<4>
        bitvec curState = discovering.top();
        //bitvec curState = discovering.front();
        discovering.pop();
        //农夫到河对岸去，伴随农夫的对象
        //依次尝试羊、白菜、狼
        for(int compain = 0; compain <= 3; ++compain){
            //伴随农夫过河的只能是与农夫在同一河边的
            if(withFarmer(compain, curState)){
                //农夫过河后的新状态
                bitvec nextState = curState;
                //农夫必定过河
                nextState.flip(farmer);
                if(compain != farmer)
                    nextState.flip(compain);
                //将状态矢量转换为整型以作为队列元素和路径下标
                int nextIndex = nextState.to_ulong();
                //如果新状态是安全的，并且尚未被发现，则新状态进入下一状态队列
                if(is_safe(nextState) && (path[nextIndex] == -1)){
                    //建立当前状态与下一状态的联系
                    path[nextIndex] = curState.to_ulong();
                    //将新状态入栈
                    discovering.push(nextIndex);
                }
            }
        }
    }//end while
    path[0] = -1;
}
#endif // NONGFUGUOHE_H
