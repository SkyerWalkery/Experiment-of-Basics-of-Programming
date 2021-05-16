#include "App.h"
#include "Other.h"
#include<cstdio>
using namespace std;
void UserDataToTxt();
void GoodsDataToTxt();
void OrderDataToTxt();
void MailDataToTxt();

int main(){
    Application app;
    app.Start();
    app.Save();
	UserDataToTxt();
	GoodsDataToTxt();
	OrderDataToTxt();
	MailDataToTxt();

    return 0;
}


void UserDataToTxt() {
	FILE* puser = fopen("Data\\User_Data.dat", "rb");
	FILE* p2 = fopen("Data\\User_Data.txt", "w+");
	if (!puser||!p2) {
		cout << "Error in place 5";//PLACE5
		exit(-1);
	}
	User user0;
	fread(&user0, sizeof(User), 1, puser);
	while (!feof(puser)) {
		fprintf(p2, "%d %s %s %s %s %lf %d\n", user0.id, user0.name, user0.password, user0.contact, user0.address, user0.money, (user0.identity));
		fread(&user0, sizeof(User), 1, puser);
	}
	fclose(puser);
	fclose(p2);
}


void GoodsDataToTxt() {
	FILE* pgoods = fopen("Data\\Goods_Data.dat", "rb");
	FILE* p2 = fopen("Data\\Goods_Data.txt", "w+");
	if (!pgoods || !p2) {
		cout << "Error in place 6";//PLACE6
		exit(-1);
	}
	Goods goods0;
	fread(&goods0, sizeof(Goods), 1, pgoods);
	while (!feof(pgoods)) {
		fprintf(p2, "%d %s %lf %d %d %s %s %d\n", goods0.id, goods0.name, goods0.price, goods0.seller_id, goods0.seller_credit, goods0.arrivetime, goods0.descrip, goods0.goodsstate);
		fread(&goods0, sizeof(Goods), 1, pgoods);
	}
	fclose(pgoods);
	fclose(p2);
}


void OrderDataToTxt() {
	FILE* porder = fopen("Data\\Order_Data.dat", "rb");
	FILE* p2 = fopen("Data\\Order_Data.txt", "w+");
	if (!porder || !p2) {
		cout << "Error in place 9";//PLACE9
		exit(-1);
	}
	Order order0;
	fread(&order0, sizeof(Order), 1, porder);
	while (!feof(porder)) {
		fprintf(p2, "%d %d %d %d %lf %s\n", order0.id, order0.goods_id, order0.seller_id, order0.buyer_id, order0.amount, order0.dealtime);
		fread(&order0, sizeof(Order), 1, porder);
	}
	fclose(porder);
	fclose(p2);
}


void MailDataToTxt() {
	ifstream in_mail("Data\\Mail_Data.dat", ios::in | ios::binary);
	ofstream out2("Data\\Mail_Data.txt", ios::out | ios::trunc);
	if (!in_mail.is_open() || !out2.is_open()) {
		cout << "Error in place 13";//PLACE13
		exit(-1);
	}
	Mail mail0;
	in_mail.read((char*)&mail0, sizeof(Mail));
	while (in_mail.good()) {
		out2 << mail0.id << " " << mail0.sender_id << " " << mail0.reci_id << " " << mail0.sender_name << " " << mail0.reci_name << " " << mail0.mail_time << " " << mail0.content << " " << (int)mail0.isread << endl;
		in_mail.read((char*)&mail0, sizeof(Mail));
	}
	in_mail.close();
	out2.close();
}