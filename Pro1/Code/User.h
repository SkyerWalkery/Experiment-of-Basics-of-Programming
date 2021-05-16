#pragma once
const int USER_NAME_LEN = 15;
const int USER_PASS_LEN = 20;
const int USER_CONTACT = 20;
const int USER_ADD_LEN = 20;
enum Identity{NORMAL, ADMINIS, FROZEN};//FROZEN表用户被管理员冻结


class User{
public:
	User(const int _id, const char* _name, const char* _password, const char* _contact, const char* _address, const double _money, const int _credit, Identity _identity);
	User();


	int id;//6个字符，开头字符为大写字母U，后5位为数字，此处省略U
	char name[USER_NAME_LEN+1];//用户名，不超过10个字符，中文汉字或英文字母
	char password[USER_PASS_LEN+1];//密码，不超过20个字符，只由小写字母和数字组成
	char contact[USER_CONTACT+1];//联系方式，不超过20个字符，由数字组成
	char address[USER_ADD_LEN+1]; //地址，不超过20个字符，中文汉字或英文字母
	double money;//余额，保留一位小数
	int credit;//信用分
	Identity identity;
};