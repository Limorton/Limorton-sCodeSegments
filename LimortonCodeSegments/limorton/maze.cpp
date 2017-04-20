/*�Թ����ʵ��*/
#include "Maze.h"

Maze::Maze(){
    #if 0
    cout << "�������Թ����У�1��ʾͨ·��0��ʾ�ϰ���û����һ���ûس�ȷ��" << endl;
    cout << "������ɺ������롮ok����������" << endl;
    //�����Թ�
    string cellstr; //������
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
    row = column = 0;    //���ó�����Ϊ(0,0)
    bool done = exitMaze(row, column);   //�ж��ܷ�Խ

    if(done){
        cout << "�����ɹ��� ·��Ϊ��" << endl;
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; j++)
                cout << cells[i][j];
            cout << endl;
        }//end for
    }//end if
    else
        cout << "������ɣ�����ͨ·" << endl;
}

//�ж�λ��(row, column)�Ƿ��ͨ�У����򷵻�true
bool Maze::valid(int row, int column){
    bool path = false;
    //���λ��(row, column)���Թ��ڣ��Ҹô������ϰ�·��
    if(row >= 0 && row < rows && column >=0 && column < columns
       && cells[row][column] == '1')
        path = true;
    return path;
}

//��λ��(row, column)��������Խ�Թ����ɹ��򷵻�true
bool Maze::exitMaze(int row, int column){
    bool done = false;
    //���λ��(row, column)��ͨ�У�����֮��������������������ǰ��
    if(valid(row, column)){
        //�߹���λ�ñ��Ϊ��B��
        cells[row][column] = 'B';
        //�ִ��յ�ʱ��ʾ��Խ���
        if(row == (rows - 1) && column == (columns - 1))
            done = true;
        //---------------------�ݹ�ʵ������
        else{
            //δ�ִ��յ�ǰ������ѡ��������
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
            //����ʧ�ܣ�ת������
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

            //���ߺ�����ʧ�ܣ�ת������
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
            //���ߡ����ߺ����߶�ʧ�ܣ�ת������
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
            cells[row][column] = 'O';   //��ȷ·�߱��Ϊ'P'
        }
    }//end if
    return done;
}
