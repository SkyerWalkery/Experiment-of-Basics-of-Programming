#pragma once
const int DEAL_TIME_LEN = 10;


class Order {
public:
	Order(const int _id, const int _goods_id, const int _seller_id, const int _buyer_id, const double _amount, const char* _dealtime);
	Order();


	int id; //订单ID,6个字符，开头字符为大写字母T，后5位为数字
	int goods_id; //商品ID,6个字符，开头字符为大写字母M，后5位为数字
	int seller_id; //卖家ID,6个字符，开头字符为大写字母U，后5位为数字
	int buyer_id; //买家ID,6个字符，开头字符为大写字母U，后5位为数字
	double amount; //交易金额,大于零的小数，精确到小数点后一位
	char dealtime[DEAL_TIME_LEN + 1];//交易时间yyyy-mm-dd

};
