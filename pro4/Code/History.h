#ifndef HISTORY_H
#define HISTORY_H

#include <fstream>
#include <string>
#include <iostream>
using std::fstream; using std::string; using std::cout;


class History {
public:
	static bool isOn;

	bool record(string str);
	bool clear();
	bool show();
	static void turn(int op);
};







#endif // !HISTORY_H
