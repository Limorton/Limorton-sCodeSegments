/*�Թ���*/
#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

class Maze{
public:
    Maze();
    void solve();
private:
    vector<string> cells;   //���ڴ洢�Թ���ͼ���Լ����ߺ�ĸ���״̬
    int rows, columns;   //�Թ�������������
    bool exitMaze(int row, int column);  //��λ��(row, column)��������Խ�Թ����ɹ��򷵻�true
    bool valid(int row, int column);     //�����ж�λ��(row, column)�Ƿ��ͨ�У��Ƿ���true
};

#endif // MAZE_H
