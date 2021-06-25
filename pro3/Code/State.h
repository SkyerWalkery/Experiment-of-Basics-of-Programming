#pragma once
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;



class State {
private:
	int board[19][19];//-1:null 0:black 1:white

public:
	State();
	void set(int r, int c, int color);
	int getPlayer(int r, int c) const;
	void clear();//清空棋盘，为下一轮准备
	int evaluateLocal(int r, int c, int myChess);
	//对以r,c为中心的11*11的局部评估,  myChess 0:黑棋  1：白棋, 返回评估值
	int evaluateGlobal(int nyChess);
	//对棋盘全局评估,返回评估值
	void Display(ostream &out);
	vector<pair<int, int>> getLegalSteps();
	bool isAlone(int r, int c) const;//判断某位置周围两圈是否有棋

	State& operator=(State& other);
};


