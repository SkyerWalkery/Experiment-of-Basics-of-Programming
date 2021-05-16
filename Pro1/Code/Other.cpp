#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
#include "other.h"



int Random(const int mini, const int maxi) {
	int rand_num;
	srand((int)time(NULL));
	rand_num = rand();
	rand_num = (rand() % (maxi - mini + 1)) + mini;//mini到maxi的闭区间
	return rand_num;
}


void GetTime(char* timestr, const int len) {
	time_t timer;
	time(&timer);
	struct tm* stimer = localtime(&timer);
	strftime(timestr, len, "%Y-%m-%d", stimer);
}//len必须大于等于11


int IdToInt(const char* idstr, const int len) {
	int res = 0;
	int temp = 1;
	if (len < 2)return 0;
	for (int i = strlen(idstr)-1; i > 0; i--, temp*=10) {
		res += (idstr[i] - '0') * temp;
	}
	return res;
}


void ForFun() {
	cout << "Loading......" << endl;
	_sleep(500);
	cout << "10%......" << endl;
	_sleep(100);
	cout << "20%......" << endl;
	_sleep(50);
	cout << "30%......" << endl;
	_sleep(50);
	cout << "40%......" << endl;
	_sleep(400);
	cout << "50%......" << endl;
	_sleep(700);
	cout << "60%......" << endl;
	_sleep(300);
	cout << "70%......" << endl;
	_sleep(200);
	cout << "80%......" << endl;
	_sleep(200);
	cout << "90%......" << endl;
	_sleep(600);
	cout << "100%" << endl;
	_sleep(300);
}



