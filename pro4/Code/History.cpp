#include "History.h"

bool History::isOn = false;


bool History::record(string str){
	fstream fout("History.txt", fstream::out | fstream::app);
	if (!fout.good())
		return false;
	fout << str << std::endl;
	fout.close();
	return true;
}

bool History::clear(){
	fstream fout("History.txt", fstream::out | fstream::trunc);
	if (!fout.good())
		return false;
	return true;
}

bool History::show(){
	fstream fin("History.txt", fstream::in);
	if (!fin.good())
		return false;

	string inStr;
	getline(fin, inStr);
	while (fin.good()) {
		cout << inStr << std::endl;
		getline(fin, inStr);
	}
	fin.close();
	return true;
}


void History::turn(int op){
	switch (op){
	case 0:isOn = false; break;
	case 1:isOn = true; break;
	default:
		break;
	}
}
