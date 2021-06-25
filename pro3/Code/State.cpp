#include "State.h"
#include "Move.h"



State::State() {
	for (int i = 0; i < 19; ++i)
		for (int j = 0; j < 19; ++j)
			board[i][j] = -1;
}

void State::set(int r, int c, int color){
	board[r][c] = color;
}

int State::getPlayer(int r, int c) const{
	return board[r][c];
}

void State::clear() {
	for (int i = 0; i < 19; ++i)
		for (int j = 0; j < 19; ++j)
			board[i][j] = -1;
}


int State::evaluateLocal(int r, int c, int myChess) {
	if (r < 0 || c < 0 || r>18 || c>18) 
		return 0;

	int road_me[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int road_enemy[7] = { 0, 0, 0, 0, 0, 0, 0 };//储存扫描到的不同路数(0-6)的个数
	int num_me, num_enemy;//临时储存扫描到的棋子个数
	int score_value[7] = { 0, 1, 5, 10, 500, 500, 17000 };//己方不同路数对应分值
	int score_threat[7] = { 0, 1, 5, 15, 600, 600, 17000 };//对方不同路数对应分值
	int total_score = 0;

	for (int i = r - 5 > 0 ? r - 5 : 0; i <= r && i + 5 < 19; ++i) {
		num_me = 0, num_enemy = 0;
		for (int m = 0; m < 6; m++) {
			int temp = board[i + m][c];
			if (temp == myChess) ++num_me;
			else if (temp == 1 - myChess) ++num_enemy;
		}
		if (num_me != 0 && num_enemy != 0) {
			num_me = 0, num_enemy = 0;
		}//有不同颜色，num清零
		++road_me[num_me];
		++road_enemy[num_enemy];//横向
	}

	for (int j = c - 5 > 0 ? c - 5 : 0; j <= c && j + 5 < 19; ++j) {
		num_me = 0, num_enemy = 0;
		for (int n = 0; n < 6; n++) {
			int temp = board[r][j + n];
			if (temp == myChess) ++num_me;
			else if (temp == 1 - myChess) ++num_enemy;
		}
		if (num_me != 0 && num_enemy != 0) {
			num_me = 0, num_enemy = 0;
		}//有不同颜色，num清零
		++road_me[num_me];
		++road_enemy[num_enemy];//纵向
	}

	for (int i = r - 5 > 0 ? r - 5 : 0,  j = c - 5 > 0 ? c - 5 : 0;
		i <= r && i + 5 < 19 && j <= c && j + 5 < 19;
		++i, ++j) {
		num_me = 0, num_enemy = 0;
		for (int m = 0, n = 0; m < 6; ++m, ++n) {
			int temp = board[i + m][j + n];
			if (temp == myChess) ++num_me;
			else if (temp == 1 - myChess) ++num_enemy;
		}
		if (num_me != 0 && num_enemy != 0) {
			num_me = 0, num_enemy = 0;
		}//有不同颜色，num清零
		++road_me[num_me];
		++road_enemy[num_enemy];//主对角线
	}


	for (int i = r - 5 > 0 ? r - 5 : 0,  j = c + 5 < 19 ? c + 5 : 18;
		i <= r && i + 5 < 19 && j >= c && j - 5 >=0;
		++i, --j) {
		num_me = 0, num_enemy = 0;
		for (int m = 0, n = 0; m < 6; ++m, ++n) {
			int temp = board[i + m][j - n];
			if (temp == myChess) ++num_me;
			else if (temp == 1 - myChess) ++num_enemy;
		}
		if (num_me != 0 && num_enemy != 0) {
			num_me = 0, num_enemy = 0;
		}//有不同颜色，num清零
		++road_me[num_me];
		++road_enemy[num_enemy];//副对角线
	}

	for (int i = 0; i < 7; i++) {
		total_score += road_me[i] * score_value[i];
		total_score -= road_enemy[i] * score_threat[i];
	}

	return total_score;
}


int State::evaluateGlobal(int myChess) {
	int road_me[7] = { 0, 0, 0, 0, 0, 0, 0 };
	int road_enemy[7] = { 0, 0, 0, 0, 0, 0, 0 };//储存扫描到的不同路数(0-6)的个数
	int num_me, num_enemy;//临时储存扫描到的棋子个数
	int score_value[7] = { 0, 1, 5, 10, 400, 500, 17000 };//己方不同路数对应分值
	int score_threat[7] = { 0, 1, 5, 15, 600, 600, 17000 };//对方不同路数对应分值
	int total_score = 0;

	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 14; ++j) {
			num_me = 0, num_enemy = 0;
			for (int k = 0; k < 6; ++k) {
				int temp = board[i][j + k];
				if (temp == myChess) ++num_me;
				else if (temp == 1 - myChess) ++num_enemy;
			}
			if (num_me != 0 && num_enemy != 0) {
				num_me = 0, num_enemy = 0;
			}//有不同颜色，num清零
			++road_me[num_me];
			++road_enemy[num_enemy];//横向
		}
	}

	for (int i = 0; i < 14; ++i) {
		for (int j = 0; j < 19; ++j) {
			num_me = 0, num_enemy = 0;
			for (int k = 0; k < 6; ++k) {
				int temp = board[i+k][j];
				if (temp == myChess) ++num_me;
				else if (temp == 1 - myChess) ++num_enemy;
			}
			if (num_me != 0 && num_enemy != 0) {
				num_me = 0, num_enemy = 0;
			}//有不同颜色，num清零
			++road_me[num_me];
			++road_enemy[num_enemy];//纵向
		}
	}

	for (int i = 0; i < 14; ++i) {
		for (int j = 0; j < 14; ++j) {
			num_me = 0, num_enemy = 0;
			for (int k = 0; k < 6; ++k) {
				int temp = board[i + k][j + k];
				if (temp == myChess) ++num_me;
				else if (temp == 1 - myChess) ++num_enemy;
			}
			if (num_me != 0 && num_enemy != 0) {
				num_me = 0, num_enemy = 0;
			}//有不同颜色，num清零
			++road_me[num_me];
			++road_enemy[num_enemy];//主对角线
		}
	}

	for (int i = 5; i < 19; ++i) {
		for (int j = 0; j < 14; ++j) {
			num_me = 0, num_enemy = 0;
			for (int k = 0; k < 6; ++k) {
				int temp = board[i - k][j + k];
				if (temp == myChess) ++num_me;
				else if (temp == 1 - myChess) ++num_enemy;
			}
			if (num_me != 0 && num_enemy != 0) {
				num_me = 0, num_enemy = 0;
			}//有不同颜色，num清零
			++road_me[num_me];
			++road_enemy[num_enemy];//副对角线
		}
	}
	
	for (int i = 0; i < 7; i++) {
		total_score += road_me[i] * score_value[i];
		total_score -= road_enemy[i] * score_threat[i];
	}

	return total_score;
}


void State::Display(ostream &out) {
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j)
			out <<left<<setw(3)<< board[i][j];
		out << endl;
	}
}


vector<pair<int, int>> State::getLegalSteps() {
	vector<pair<int, int>> res;
	for (int i = 0; i < 19; i++) 
		for (int j = 0; j < 19; j++) 
			if (board[i][j] == -1 && !isAlone(i, j)){
				pair<int, int> temp = make_pair(i, j);
				res.push_back(temp);
			}			

	return res;
}


bool State::isAlone (int r, int c) const{
	for (int i = r - 2 < 0 ? 0 : r-2; i < 19 && i < r+3; ++i)
		for (int j = c - 2 < 0 ? 0 : c-2; j < 19 && j < c+3; ++j)
			if (board[i][j] != -1) {
				return false;
			}

	return true;
}


State& State::operator=(State& other) {
	for (int i = 0; i < 19; ++i)
		for (int j = 0; j < 19; ++j)
			board[i][j] = other.board[i][j];

	return *this;
}



