#pragma once
int Random(const int mini, const int maxi);//用来生成随机数
void GetTime(char* timestr, const int len);//获取当前时间，并转化成字符串, len为数字位数(>=11)
int IdToInt(const char* idstr, const int len);//将ID字符串转化为int,len为数字位数
void ForFun();