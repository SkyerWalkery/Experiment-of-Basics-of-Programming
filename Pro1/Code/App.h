#pragma once
#include<iostream>
#include<vector>
#include<cstdio>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;
#include "User.h"
#include "Goods.h"
#include "Order.h"
#include "Other.h"
#include "Mail.h"


enum AppState{DEFAULT, USER_MAIN, ADMINIS_MAIN, USER_FROZEN, USER_SELL, USER_SELL_GOODS, USER_SELL_GOODS_MANAG, USER_BUY, USER_BUY_DIREC, USER_INFO, MAIL, MAIL_INBOX};
/*

*/


class Application {
	vector<User> users;//所有用户信息集合
	vector<Goods> goodss;//所有商品信息集合
	vector<Order> orders;//所有订单信息集合
	vector<Mail> mails;//所有邮件集合
	int users_num;//用户数量
	int goodss_num;//商品数量
	int orders_num;//订单数量
	AppState appstate;
	vector<User>::iterator user_on;//指向当前登录的用户
	vector<User>::iterator user_off;//指向当前管理员试图操作的用户
	vector<Goods>::iterator goods_on;//指向当前操作的商品
	vector<Mail>::iterator mail_on;
public:
	Application();
	void Save();
	void Window(int option);
	void Start();
	void SignUp();
	void Login(int option);//登录,0为正常登录,1为忘记密码
	void Buy();
	void Release();//发布商品
	void CheckGoodss(int option);//查看商品,0为全部商品,1为卖家商品,2为上架的的商品
	void CheckOrders(int option);//查看订单,0为全部,1为买家,2为卖家
	void CheckUsers(int option);//查看用户,0为全部,1为自己
	void CheckMails(int option);//查看邮件,0为全部,1为收件人的,2为发件人的
	void GoodsManag(int option);//修改商品信息
	void UserManag(int option);//修改用户信息
	void MailManag(int option);//管理邮件,0为已读所有,1为已读指定
	void BindGoods();//绑定操作商品
	void BindUserOff();//绑定管理员操作的用户
	void BindMail();//绑定操作邮件
	void TopUp();//充值
	void SearchGoods();//搜索商品
	void NewMail();//写邮件
	int CheckPass(const char* cstr);//检测密码安全性，详见函数定义
	void CloseAcc();//注销账号
	void Notify(int option, int id);//通知
	
	
};