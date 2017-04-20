/*迷宫类*/
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
    vector<string> cells;   //用于存储迷宫地图，以及行走后的各处状态
    int rows, columns;   //迷宫的行数和烈数
    bool exitMaze(int row, int column);  //从位置(row, column)出发，穿越迷宫，成功则返回true
    bool valid(int row, int column);     //用于判断位置(row, column)是否可通行，是返回true
};

#endif // MAZE_H
