/*迷宫类的实现*/
#include "Maze.h"

Maze::Maze(){
    #if 0
    cout << "请输入迷宫阵列，1表示通路，0表示障碍，没输入一行用回车确认" << endl;
    cout << "输入完成后请输入‘ok’结束输入" << endl;
    //读入迷宫
    string cellstr; //输入行
    cin >> cellstr;
    while(cellstr != "ok"){
        cells.push_back(cellstr);
        columns = cellstr.size();
        cin >> cellstr;
    }
    rows = cells.size();
    #else
    cells.push_back("11111111");
    cells.push_back("1##1##1#");
    cells.push_back("####111#");
    cells.push_back("111##1#1");
    cells.push_back("1#1#1111");
    cells.push_back("1#111#1#");
    cells.push_back("##1####1");
    cells.push_back("1#111111");
    rows = cells.size();
    columns = cells[0].size();
    #endif
}

void Maze::solve(){
    int row, column;
    row = column = 0;    //设置出发点为(0,0)
    bool done = exitMaze(row, column);   //判断能否穿越

    if(done){
        cout << "搜索成功！ 路径为：" << endl;
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; j++)
                cout << cells[i][j];
            cout << endl;
        }//end for
    }//end if
    else
        cout << "搜索完成，但无通路" << endl;
}

//判断位置(row, column)是否可通行，是则返回true
bool Maze::valid(int row, int column){
    bool path = false;
    //如果位置(row, column)在迷宫内，且该处是无障碍路径
    if(row >= 0 && row < rows && column >=0 && column < columns
       && cells[row][column] == '1')
        path = true;
    return path;
}

//从位置(row, column)出发，穿越迷宫，成功则返回true
bool Maze::exitMaze(int row, int column){
    bool done = false;
    //如果位置(row, column)可通行，则标记之，并依次向四周搜索着前进
    if(valid(row, column)){
        //走过的位置标记为‘B’
        cells[row][column] = 'B';
        //抵达终点时表示穿越完成
        if(row == (rows - 1) && column == (columns - 1))
            done = true;
        //---------------------递归实现搜索
        else{
            //未抵达终点前，首先选择向右走
            {
                done = exitMaze(row, column + 1);
                //----------
                for(int i = 0; i < rows; ++i)
                {
                    for(int j = 0; j < columns; j++)
                        cout << cells[i][j];
                    cout << endl;
                }//end for
                Sleep(400);
                system("cls");
            }
            //右走失败，转向下走
            if(!done)
            {
                done = exitMaze(row + 1, column);
                for(int i = 0; i < rows; ++i)
                {
                    for(int j = 0; j < columns; j++)
                        cout << cells[i][j];
                    cout << endl;
                }//end for
                Sleep(400);
                system("cls");
            }

            //右走和下走失败，转向左走
            if(!done)
            {
                done = exitMaze(row, column - 1);
                for(int i = 0; i < rows; ++i)
                {
                    for(int j = 0; j < columns; j++)
                        cout << cells[i][j];
                    cout << endl;
                }//end for
                Sleep(400);
                system("cls");
            }
            //右走、下走和左走都失败，转向上走
            if(!done)
            {
                done = exitMaze(row - 1, column);
                for(int i = 0; i < rows; ++i)
                {
                    for(int j = 0; j < columns; j++)
                        cout << cells[i][j];
                    cout << endl;
                }//end for
                Sleep(400);
                system("cls");
            }
        }
        if(done){
            cells[row][column] = 'O';   //正确路线标记为'P'
        }
    }//end if
    return done;
}
