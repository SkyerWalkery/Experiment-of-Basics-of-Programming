#include "Expression.h"
#include "Parser.h"
#include "Evaluate.h"
#include "History.h"
#include <iostream>
#include <vector>

using namespace std;


int main() {
    cout << endl
         << "===========================================================" << endl
         << "|        Welcome to use the Expression Calculator!        |\n"
         << "|                  Author: SkyerWalkery                   |\n"
         << "|         WebPage: https://github.com/SkyerWalkery        |\n"
         << "===========================================================" << endl << endl;


    vector<Function> vecFunc;
    vector<Variate> vecVari;
    bool history_ctrl = false;//要打开历史记录功能，请将其置true


    while (true) {
        string inStr;
        getline(cin, inStr);


        History history;
        if(history_ctrl && History::isOn)
            history.record(inStr);

        if (inStr.empty()) {
            continue;
        }
        else if (inStr == "EXIT")
            break;
        else if (inStr == "CLEAR") {
            vecFunc.clear();
            vecVari.clear();
            continue;
        }
        else if (history_ctrl) {
            if (inStr == "HISTORY ON") {
                history.turn(1);
                continue;
            }
            else if (inStr == "HISTORY OFF") {
                history.turn(0);
                continue;
            }
            else if (inStr == "HISTORY SHOW") {
                history.show();
                continue;
            }
            else if (inStr == "HISTORY CLEAR") {
                history.clear();
                continue;
            }
        }

        Expression expr(inStr);
        int toDo = expr.check(vecFunc, vecVari);
        if (!expr.good()) {
            cerr << expr.getErrMsg();
            continue;
        }//Expression自检查时发现错误

        if (toDo == 1) {
            list<Token> mathExpr = expr.getMathExpr();
            if (!expr.good()) {
                cerr << expr.getErrMsg();
                continue;
            }//Expression自检查时发现错误

            Parser parser(mathExpr, vecVari, vecFunc);
            ASTnode *ast = parser.parse();
            if (!parser.good()) {
                cerr << parser.getErrMsg();
                continue;
            }


            Evaluate evaluate;
            double res = evaluate.eval(ast);
            if (!evaluate.good()) {
                cerr << evaluate.getErrMsg();
                continue;
            }
            evaluate.delAST(ast);
            //cout << "\033[32m" << res << "\033[0m" << endl;//Linux专用
            cout << res << endl;
        }

    }
    return 0;
}