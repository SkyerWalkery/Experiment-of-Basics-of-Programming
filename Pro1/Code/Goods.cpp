#include <iostream>
#include <cstring>
#include "Goods.h"
using namespace std;




Goods::Goods(const int _id, const char* _name, const double _price, const int _seller_id, const int _seller_credit, const char* _arrivetime, const char* _descrip, GoodState _state = GoodState::AVAILABLE) {
	id = _id;
	strcpy(name, _name);
	seller_id = _seller_id;
	seller_credit = _seller_credit;
	strcpy(arrivetime, _arrivetime);
	price = _price;
	goodsstate = _state;
	strcpy(descrip, _descrip);
}

Goods::Goods() {
	price = -1;
	goodsstate = WITHDRAWN;
}
