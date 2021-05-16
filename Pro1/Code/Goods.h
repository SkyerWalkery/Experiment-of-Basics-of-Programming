#pragma once
const int GOODS_NAME_LEN = 15;
const int ARRIVE_TIME_LEN = 10;
const int GOODS_DESCRIP_LEN = 100;
enum GoodState{SOLDOUT, WITHDRAWN, AVAILABLE};


class Goods {
public:
	Goods(const int _id, const char* _name, const double _price, const int _seller_id, const int _seller_credit, const char* _arrivetime, const char* _descrip, GoodState _state);
	Goods();


	int id;//6个字符，开头字符为大写字母M，后5位为数字，此处省略M
	char name[GOODS_NAME_LEN+1];//商品名，不超过10个字符，中文汉字或英文字母
	double price; //价格，大于零的小数，精确到小数点后一位
	int seller_id;//卖家ID，6个字符，开头字符为大写字母U，后5位为数字
	int seller_credit;//卖家信用分
	char arrivetime[ARRIVE_TIME_LEN+1];//上架时间yyyy-mm-dd
	char descrip[GOODS_DESCRIP_LEN + 1];//商品的描述信息,不超过100个字符
	GoodState goodsstate;//表示商品状态的枚举类型
};