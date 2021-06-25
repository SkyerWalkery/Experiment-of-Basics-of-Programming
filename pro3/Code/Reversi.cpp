#define _CRT_SECURE_NO_WARNINGS
#include "Reversi.h"

#define random(x) (rand()%x)
#define ROWS 19
#define COLS 19
#define ROUNDS 2


Reversi::Reversi(){
    client_socket = ClientSocket();
    oppositeColor = ownColor = -1;
	path = nullptr;
	isSave = false;
	state.set(9, 9, 1);
}

Reversi::~Reversi(){}
void Reversi::setOwnColor(int color)
{
	if (color != 0 && color != 1)
		return;
	ownColor = color;
	oppositeColor = 1 - color;
}
;

/*
 send id and password to server by socket
 rtn != 0 represents socket transfer error
 */
void Reversi::authorize(const char *id , const char *pass)
{
    client_socket.connectServer();
    std::cout << "Authorize " << id << std::endl;
    char msgBuf[BUFSIZE];
    memset(msgBuf , 0 , BUFSIZE);
    msgBuf[0] = 'A';
    memcpy(&msgBuf[1] , id , 9);
    memcpy(&msgBuf[10] , pass , 6);
    int rtn = client_socket.sendMsg(msgBuf);
    if (rtn != 0) printf("Authorized Failed!\n");
}

// 用户id输入，服务器上需要有对应的账号密码：对应文件 players-0.txt
void Reversi::gameStart()
{
    char id[12] = {0}, passwd[10] = {0};
	strcpy(id, ID);
	strcpy(passwd, PASSWORD);
    authorize(id, passwd);
    
    printf("Game Start!\n");

    
    for (int round = 0 ; round < ROUNDS ; round++){
        roundStart(round);
		state.set(9, 9, 1);//先置一白棋于中间
		if (isSave)
			saveChessBoard(2);

        oneRound();

        roundOver(round);
		state.clear();////清空棋盘，为下一轮准备
		if (isSave)
			saveChessBoard(1);
    }
    gameOver();
    client_socket.close();
}

void Reversi::gameOver()
{
    printf("Game Over!\n");
}

//发一次消息，走哪一步，等两个消息，1.自己的步数行不行 2.对面走了哪一步 
void Reversi::roundStart(int round)
{
    printf("Round %d Ready Start!\n" , round);
    
    // first time receive msg from server
    int rtn = client_socket.recvMsg();
    if (rtn != 0) return ;
    if(strlen(client_socket.getRecvMsg()) < 2)
        printf("Authorize Failed!\n");
    else
        printf("Round start received msg %s\n", client_socket.getRecvMsg());
    switch (client_socket.getRecvMsg()[1]) {
            // this client : black chessman
        case 'B':
            ownColor = 0;
            oppositeColor = 1;
            rtn = client_socket.sendMsg("BB");
            printf("Send BB -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        case 'W':
            ownColor = 1;
            oppositeColor = 0;
            rtn = client_socket.sendMsg("BW");
            printf("Send BW -> rtn: %d\n", rtn);
            if (rtn != 0) return ;
            break;
        default:
            printf("Authorized Failed!\n");
            break;
    }
}

void Reversi::oneRound()
{
	//cout << "place1" << endl;
    int STEP = 1;
    switch (ownColor) {
        case 0:
            while (STEP < 10000) {
                
				pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message
                
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first.first, chess.first.second, chess.second.first, chess.second.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
                
                if (observe() >= 1) break;    // see white move
                STEP++;
				if(isSave)
					saveChessBoard(0);
            }
            printf("One Round End\n");
            break;
        case 1:
            while (STEP < 10000) {
                
                if (observe() >= 1) break;    // see black move
                
				pair<pair<int, int>, pair<int, int>> chess = step();                        // take action, send message
                // lazi only excute after server's message confirm  in observe function
                generateOneStepMessage(chess.first.first,chess.first.second,chess.second.first, chess.second.second);
                
                
                if (observe() >= 1) break;     // receive RET Code
				if(isSave)
					saveChessBoard(0);
                STEP++;
            }
            printf("One Round End\n");
            break;
            
        default:
            break;
    }

}

void Reversi::roundOver(int round)
{
    printf("Round %d Over!\n", round);
    // reset initializer

    ownColor = oppositeColor = -1;
}

int Reversi::observe()
{
	int rtn = 0;
	int recvrtn = client_socket.recvMsg();
	if (recvrtn != 0) return 1;
	printf("receive msg %s\n", client_socket.getRecvMsg());
	switch (client_socket.getRecvMsg()[0]) {
	case 'R':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case 'Y':   // valid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P':   // update chessboard
			{
				int desRow1 = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol1 = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int desRow2 = (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
				int desCol2 = (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
				int color = (client_socket.getRecvMsg()[11] - '0');
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow1, desCol1, desRow2, desCol2, color);

				//printf("a valid step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
				break;
			}
			case 'N':   // R0N: enemy wrong step
			{
				//
				//printf("a true judgement of no step\n");
				break;
			}
			}

			break;
		case 'W':
			// invalid step
			switch (client_socket.getRecvMsg()[2]) {
			case 'P': {
				int desRow1 = (client_socket.getRecvMsg()[3] - '0') * 10 + client_socket.getRecvMsg()[4] - '0';
				int desCol1 = (client_socket.getRecvMsg()[5] - '0') * 10 + client_socket.getRecvMsg()[6] - '0';
				int desRow2 = (client_socket.getRecvMsg()[7] - '0') * 10 + client_socket.getRecvMsg()[8] - '0';
				int desCol2 = (client_socket.getRecvMsg()[9] - '0') * 10 + client_socket.getRecvMsg()[10] - '0';
				int color = (client_socket.getRecvMsg()[11] - '0');
				//printf("Invalid step , server random a true step of : (%d %d) (%d %d)\n", desRow1, desCol1, desRow2, desCol2);
				//你应该在这里处理desRow和desCol，推荐使用函数
				handleMessage(desRow1, desCol1, desRow2, desCol2, color);
				break;
			}
			case 'N': {
				printf("a wrong judgement of no step\n");
				break;
			}
			default:
				break;
			}
			break;
		case '1':

			printf("Error -1: Msg format error!\n");
			rtn = -1;
			break;
		case '2':

			printf("Error -2: Corrdinate error!\n");
			rtn = -2;
			break;
		case '4':

			printf("Error -4: Invalid step!\n");
			rtn = -4;
			break;
		default:

			printf("Error -5: Other error!\n");
			rtn = -5;
			break;
		}
		break;
	}
	case 'E':
	{
		switch (client_socket.getRecvMsg()[1]) {
		case '0':
			// game over
			rtn = 2;
			break;
		case '1':
// round over
rtn = 1;
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	return rtn;
}

void Reversi::generateOneStepMessage(int row1, int col1, int row2, int col2)
{
	char msg[BUFSIZE];
	memset(msg, 0, sizeof(msg));

	//put row and col in the message
	msg[0] = 'S';
	msg[1] = 'P';
	msg[2] = '0' + row1 / 10;
	msg[3] = '0' + row1 % 10;
	msg[4] = '0' + col1 / 10;
	msg[5] = '0' + col1 % 10;
	msg[6] = '0' + row2 / 10;
	msg[7] = '0' + row2 % 10;
	msg[8] = '0' + col2 / 10;
	msg[9] = '0' + col2 % 10;
	msg[10] = '\0';

	//print
	printf("generate one step at possition (%2d,%2d,%2d,%2d) : %s\n", row1, col1, row2, col2, msg);


	client_socket.sendMsg(msg);
}

/*-------------------------last three function--------------------------------
* step : find a good position to lazi your chess.
* saveChessBoard : save the chess board now.
* handleMessage: handle the message from server.
*/

pair<pair<int, int>, pair<int, int>> Reversi::step1() {

	/*******   Version1   ******************************/
	vector<pair<int, int>> not_alone_steps = state.getLegalSteps();//对可下棋的地方初步筛选
	int not_alone_size = not_alone_steps.size();
	vector<Move> myMoves;//搜索树的第一层
	unsigned int width1 = 8;//第一层的搜索宽度

	for (int i = 0; i < not_alone_size - 1; ++i) {
		for (int j = i + 1; j < not_alone_size; ++j) {
			int r1 = not_alone_steps[i].first, c1 = not_alone_steps[i].second;
			int r2 = not_alone_steps[j].first, c2 = not_alone_steps[j].second;

			int prev_score = state.evaluateLocal(r1, c1, ownColor) + state.evaluateLocal(r2, c2, ownColor);
			//评估落子之前的备选的俩位置
			state.set(r1, c1, ownColor), state.set(r2, c2, ownColor);
			//模拟落子
			int after_score = state.evaluateLocal(r1, c1, ownColor) + state.evaluateLocal(r2, c2, ownColor);
			//评估落子之后的备选的俩位置
			state.set(r1, c1, -1), state.set(r2, c2, -1);
			//撤销模拟的落子

			int delta_score = after_score - prev_score;
			Move move0(r1, c1, r2, c2, delta_score);
			myMoves.push_back(move0);
		}
	}//把第一层全部遍历，保存结果
	sort(myMoves.rbegin(), myMoves.rend());//用反向迭代器实现降序

	if (myMoves.size() > width1) {
		myMoves.erase(myMoves.begin() + width1, myMoves.end());
	}//保留表现最好的width1条记录 

	for (auto it_my = myMoves.begin(); it_my < myMoves.end(); ++it_my) {
		if (it_my->delta_score > 10000) {
			return it_my->getStep();
		}//大概率出现己方或对方四路或五路, 直接贪心算法, 不再用博弈树 */

		state.set(it_my->r1, it_my->c1, ownColor), state.set(it_my->r2, it_my->c2, ownColor);
		//模拟自己落子
		vector<pair<int, int>> enemy_not_alone_steps = state.getLegalSteps();//对可下棋的地方初步筛选
		int enemy_not_alone_size = enemy_not_alone_steps.size();
		int min_global_score = 1000000;//最低全局得分
		vector<Move> enemyMoves;//搜索树的第二层
		unsigned int width2 = 8;//第二层的搜索宽度

		for (int i = 0; i < enemy_not_alone_size - 1; i++) {
			for (int j = i + 1; j < enemy_not_alone_size; j++) {
				int r3 = enemy_not_alone_steps[i].first, c3 = enemy_not_alone_steps[i].second;
				int r4 = enemy_not_alone_steps[j].first, c4 = enemy_not_alone_steps[j].second;

				int prev_score = state.evaluateLocal(r3, c3, oppositeColor) + state.evaluateLocal(r4, c4, oppositeColor);
				//评估落子之前的备选的俩位置
				state.set(r3, c3, oppositeColor), state.set(r4, c4, oppositeColor);
				//模拟落子
				int after_score = state.evaluateLocal(r3, c3, oppositeColor) + state.evaluateLocal(r4, c4, oppositeColor);
				int global_score = state.evaluateGlobal(ownColor);
				//评估落子之后的备选的俩位置
				state.set(r3, c3, -1), state.set(r4, c4, -1);
				//撤销模拟的落子

				int delta_score = after_score - prev_score;
				Move move1(r3, c3, r4, c4, delta_score, global_score);
				enemyMoves.push_back(move1);
			}
		}

		sort(enemyMoves.rbegin(), enemyMoves.rend());//用反向迭代器实现降序
		if (enemyMoves.size() > width2) {
			enemyMoves.erase(enemyMoves.begin() + width2, enemyMoves.end());
		}//保留表现最好的width2条记录 

		for (auto enemy_it = enemyMoves.begin(); enemy_it < enemyMoves.end(); enemy_it++) 
			if (enemy_it->global_score < min_global_score) 
				min_global_score = enemy_it->global_score;

		enemyMoves.clear();
		it_my->final_score = min_global_score;
		state.set(it_my->r1, it_my->c1, -1), state.set(it_my->r2, it_my->c2, -1);
		//撤销自己落子
	}

	vector<Move>::iterator it_best_move = myMoves.begin();
	for (auto it_my = myMoves.begin(); it_my < myMoves.end(); ++it_my) {
		if (it_my->final_score > it_best_move->final_score)
			it_best_move = it_my;
	}

	//cout << r1 << " " << c1 << " " << r2 << " " << c2 << endl;
	//state.Display();
	return it_best_move->getStep();
	/*******   Version1   ******************************/

}


pair<pair<int, int>, pair<int, int>> Reversi::step() {
	int depth = 2, width = 10;//博弈树深度与宽度
	this->path = new Move[depth + 1];//博弈树中选出的最佳路线，path[i]储存搜索深度为depth - i的走法
	alpha_beta(depth, width, -1000000, 1000000, true);//构造树
	Move this_step = path[depth];
	delete[] path;//释放内存
	this->path = nullptr;
	return this_step.getStep();
}



void Reversi::saveChessBoard(int option){
	switch (option) {
	case 0: {
		fstream fout("dat", ios::out | ios::app | ios::binary);
		if (!fout.is_open()) {
			cout << "error";
			return;
		}
		fout.write((char*)&state, sizeof(State));
		fout.close();
	}break;//将棋局存入二进制文件

	case 1: {
		char fname[50] = "\0";
		if (!getFName(fname)) {
			cout << "error1" << endl;
			return;
		}
		fstream fout(fname, ios::out);
		fstream fin("dat", ios::in | ios::binary);
		if (!fin.is_open() || !fout.is_open()) {
			cout << "error2\n";
			return;
		}

		State state0;
		fin.read((char*)&state0, sizeof(State));
		while (fin.good() && fout.good()) {
			for (int i = 0; i < 19; i++) {
				for (int j = 0; j < 19; j++) {
					char temp;
					switch (state0.getPlayer(i, j)) {
					case -1:temp = 'O'; break;
					case 0:temp = 'B'; break;
					case 1:temp = 'W'; break;
					default: temp = '\0'; break;
					}
					fout << '|' << temp;
				}
				fout << "|\n" << "---------------------------------------\n";
			}
			fout << "\n\n";
			fin.read((char*)&state0, sizeof(State));
		}
		fin.close(), fout.close();
	}break;//将二进制文件内容转化为可读的文本文件

	case 2: {
		fstream f("dat", ios::trunc|ios::in|ios::out);
		f.close();
	}//清空二进制文件中的内容
	}
}


bool Reversi::getFName(char str[]) {
	time_t t = time(NULL);
	if (strftime(str, 49, "%Y_%m_%d_%H_%M_%S.txt", localtime(&t)) == 0)
		return false;
	return true;
}


void Reversi::handleMessage(int row1, int col1, int row2, int col2, int color) {
	state.set(row1, col1, color);
	state.set(row2, col2, color);
}


vector<Move> Reversi::generateSteps(unsigned int width, int color) {
	vector<Move> res;
	vector<pair<int, int>> step_vec = state.getLegalSteps();//所有可能走法
	int step_size = step_vec.size();
	if (step_size == 0)
		return res;

	for (int i = 0; i < step_size - 1; ++i) {
		for (int j = i + 1; j < step_size; ++j) {
			int r1 = step_vec[i].first, c1 = step_vec[i].second;
			int r2 = step_vec[j].first, c2 = step_vec[j].second;

			int prev_score = state.evaluateLocal(r1, c1, color) + state.evaluateLocal(r2, c2, color);
			//评估落子之前的备选的俩位置
			state.set(r1, c1, ownColor), state.set(r2, c2, color);
			//模拟落子
			int after_score = state.evaluateLocal(r1, c1, color) + state.evaluateLocal(r2, c2, color);
			//评估落子之后的备选的俩位置
			state.set(r1, c1, -1), state.set(r2, c2, -1);
			//撤销模拟的落子

			int delta_score = after_score - prev_score;
			Move move0(r1, c1, r2, c2, delta_score);
			res.push_back(move0);
		}
	}//把第一层全部遍历，保存结果
	sort(res.rbegin(), res.rend());//用反向迭代器实现降序

	auto it = res.begin();
	for (unsigned int i = 0; it != res.end() && i < width; it++, i++);
	if (res.size() > width) {
		res.erase(it, res.end());
	}//保留表现最好的width条记录 

	return res;
}


int Reversi::alpha_beta(int depth, int width, int alpha, int beta, bool isMax) {
	if (depth > 0) {
		Move best_child;
		vector<Move> child_list;
		int sub_beta;

		if (isMax) {
			child_list = generateSteps(width, ownColor);
			for (auto it_child = child_list.begin(); it_child != child_list.end(); ++it_child) {
				Move move0 = *it_child;
				if (move0.delta_score > 10000) {
					path[depth] = move0;
					return state.evaluateGlobal(ownColor);
				}//局部评分达到阈值，极有可能六连（游戏结束），直接结束该branch

				state.set(move0.r1, move0.c1, ownColor), state.set(move0.r2, move0.c2, ownColor);
				sub_beta = alpha_beta(depth - 1, width, alpha, beta, false);
				if (sub_beta > alpha) {
					alpha = sub_beta;
					best_child = move0;
				}//更新下界
				state.set(move0.r1, move0.c1, -1), state.set(move0.r2, move0.c2, -1);
				if (beta <= alpha) {
					break;
				}//剪枝
			}

			path[depth] = best_child;//存储该层的最佳走法
			return alpha;
		}

		else {
			child_list = generateSteps(width, ownColor);
			for (auto it_child = child_list.begin(); it_child != child_list.end(); ++it_child) {
				Move move0 = *it_child;
				if (move0.delta_score > 10000) {
					path[depth] = move0;
					return state.evaluateGlobal(ownColor);
				}//局部评分达到阈值，极有可能六连（游戏结束），直接结束该branch
				state.set(move0.r1, move0.c1, oppositeColor), state.set(move0.r2, move0.c2, oppositeColor);
				sub_beta = alpha_beta(depth - 1, width, alpha, beta, true);
				if (sub_beta < beta) {
					beta = sub_beta;
					best_child = move0;
				}//更新上界
				state.set(move0.r1, move0.c1, -1), state.set(move0.r2, move0.c2, -1);
				if (beta <= alpha) {
					break;
				}//剪枝
			}

			path[depth] = best_child;//存储该层的最佳走法
			return beta;
		}


	}

	else
		return state.evaluateGlobal(ownColor);//到达叶节点（到达指定深度）

}



