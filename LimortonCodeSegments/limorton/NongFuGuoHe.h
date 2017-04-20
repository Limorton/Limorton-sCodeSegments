/**ũ�����������ʾ���漰�����������������������**/
#ifndef NONGFUGUOHE_H
#define NONGFUGUOHE_H
#include <iostream>
#include <bitset>
#include <vector>
#include <queue>

using namespace std;

//�����ߣ���4�ֶ���
enum Wader{
    cabbage,    //Ĭ��Ϊ1
    goat,       //Ĭ��Ϊ2
    wolf,       //Ĭ��Ϊ3
    farmer      //Ĭ��Ϊ4
};
//����״̬���ͣ�bit�ֱ��Ӧ4�ֹ��Ӷ���
typedef bitset<4> bitvec;

//�жϴ����ӵĶ���wader�Ƿ���ũ��farmer�ںӵ�ͬһ��
//stateΪ��ǰ״̬
inline bool withFarmer(int wader, bitvec& state){
    return (state[farmer] == state[wader]);
}

//�ж�״̬�Ƿ�ȫ��state�ǵ�ǰ״̬
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



//��������ʾʵ�ʷ���
void displayRoute(const vector<int>&path){
    //���path[15]״̬û��ǰ�����ʾ�޷��ɹ��ﵽĿ��״̬
    if(path[15] == -1){
        cout << "�ù��������޽�" << endl;
        return;
    }
    //��������ʾ��·��ת��Ϊ����ʸ����ʾ��״̬·��
    //�洢״̬·��������
    deque<bitvec> statePath;
    for(int i = 15; i >0; i = path[i])
        statePath.push_front(i);
        //������룬���·���ӳ�ʼ״̬��Ŀ��״̬��ת��
        //��ʽ����ת����int -> bitset<4>
    //����ʼ״̬����
    statePath.push_front(0);
    //��ǰ״̬������ת������
    bitvec current, next, trans;
    bool crossed = true;
    int step = 1;
    for(unsigned int i = 1; i < statePath.size(); i++){
        current = statePath[i - 1];
        next = statePath[i];
        //״̬�����еı仯λ
        trans = current ^ next;
        //��ȡ״̬�����仯�Ķ���
        int wader = -1;
        for(int i = 0; i <= 2; i++){
            if(trans.test(i)){
                wader = i;
                break;
            }
        }
        cout << "����" << step++ << ":";
        switch(wader){
        case goat:
            cout << "ũ������" << (crossed ? "���ӱ˰�":"�غӴ˰�") << endl;
            break;
        case cabbage:
            cout << "ũ��Ѱײ˴�" << (crossed ? "���ӱ˰�":"�غӴ˰�") << endl;
            break;
        case wolf:
            cout << "ũ����Ǵ�" << (crossed ? "���ӱ˰�":"�غӴ˰�") << endl;
            break;
        case -1:
            cout << "ũ�����" << (crossed ? "���ӱ˰�":"�غӴ˰�") << endl;
            break;
        }
        crossed = !crossed;
    }
    cout << "\n�����������ɹ���" << endl;
}
//�������ӵķ���·��
void findRoute(vector<int>& path){
    //�����ֵĸ���״̬
    /*�����������ʹ��stack�洢�������������ʹ��queue�洢*/
    stack<int> discovering;
    //queue<int> discovering;
    //��ʼ״̬Ϊ0000
    discovering.push(0x00);
    //��ʼ״̬·����ʼ��
    path[0] = 0;
    //������һ��״̬��������δ�ﵽ����״̬
    while(!discovering.empty() && (path[15] == -1)){
        //��ȡ��ǰ������״̬����ʽת�� int -> bitset<4>
        bitvec curState = discovering.top();
        //bitvec curState = discovering.front();
        discovering.pop();
        //ũ�򵽺Ӷ԰�ȥ������ũ��Ķ���
        //���γ����򡢰ײˡ���
        for(int compain = 0; compain <= 3; ++compain){
            //����ũ����ӵ�ֻ������ũ����ͬһ�ӱߵ�
            if(withFarmer(compain, curState)){
                //ũ����Ӻ����״̬
                bitvec nextState = curState;
                //ũ��ض�����
                nextState.flip(farmer);
                if(compain != farmer)
                    nextState.flip(compain);
                //��״̬ʸ��ת��Ϊ��������Ϊ����Ԫ�غ�·���±�
                int nextIndex = nextState.to_ulong();
                //�����״̬�ǰ�ȫ�ģ�������δ�����֣�����״̬������һ״̬����
                if(is_safe(nextState) && (path[nextIndex] == -1)){
                    //������ǰ״̬����һ״̬����ϵ
                    path[nextIndex] = curState.to_ulong();
                    //����״̬��ջ
                    discovering.push(nextIndex);
                }
            }
        }
    }//end while
    path[0] = -1;
}
#endif // NONGFUGUOHE_H
