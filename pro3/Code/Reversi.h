#ifndef Reversi_h
#define Reversi_h
#include <stdio.h>
#include <ctime>
#include <fstream>
#include "ClientSocket.h"
#include "State.h"
#include "Move.h"
using namespace std;



class Reversi{
private:
    ClientSocket client_socket;
    int ownColor;
    int oppositeColor;

    /******Added By Skyer_Walkery*****/
    State state;
    Move* path;
    bool isSave;
    /******Added By Skyer_Walkery*****/


	//function 

	 // according to chessman position (row , col) , generate one step message in order to send to server
    void generateOneStepMessage(int row1 , int col1, int row2, int col2);

public:
	pair<pair<int, int>, pair<int, int>> step();

    pair<pair<int, int>, pair<int, int>> step1();

    
    void saveChessBoard(int option);
    //储存棋盘，功能详见定义。若要开启，请将本类成员isSave改为true（在构造函数初始化）。

    bool getFName(char str[]);

	void handleMessage(int row1, int col1, int row2, int col2, int color);

    int alpha_beta(int depth, int width, int alpha, int beta, bool isMax);

    vector<Move> generateSteps(unsigned int width, int color);//产生执color颜色棋的一方最有可能的width种走法
public:
    Reversi();
    ~Reversi();

	void setOwnColor(int color);

    void authorize(const char *id , const char *pass);
    
    void gameStart();
    
    void gameOver();
    
    void roundStart(int round);
    
    void oneRound();
    
    void roundOver(int round);
    
    int observe();
    
};

#endif /* Reversi_h */
