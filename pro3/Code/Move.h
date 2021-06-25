#pragma once
#include<utility>
using namespace std;



class Move {
public:
	int r1;
	int c1;
	int r2;
	int c2;
	int delta_score;
	int global_score;//该移动后对应全局评分
	int final_score;//对应进行一个回合后（自己走一步对自己有利的，对方走一步对对方有利的）, 所得的全局评分

	Move();
	Move(int r1, int c1, int r2, int c2, int delta_score, int global_score = 0);
	pair<pair<int, int>, pair<int, int>> getStep();//将两步落子打包返回
	bool operator>(Move& other);//用于排序
	bool operator<(Move& other);//用于排序
};