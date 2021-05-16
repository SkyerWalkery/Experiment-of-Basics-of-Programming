#include<iostream>
#include<cstring>
using namespace std;
#include "Order.h"


Order::Order(const int _id, const int _goods_id, const int _seller_id, const int _buyer_id, const double _amount, const char* _dealtime) {
	id = _id;
	goods_id = _goods_id;
	seller_id = _seller_id;
	buyer_id = _buyer_id;
	amount = _amount;
	strcpy(dealtime, _dealtime);
}

Order::Order() {
	id = -1;
	goods_id = -1;
	seller_id = -1;
	buyer_id = -1;
	amount = -1;
}
