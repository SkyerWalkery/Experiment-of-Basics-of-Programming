#include"Move.h"


Move::Move():Move(-1, -1, -1, -1, -1, -1) {

}//委托构造


Move::Move(int r1, int c1, int r2, int c2, int delta_score, int global_score) {
	this->r1 = r1, this->c1 = c1, this->r2 = r2, this->c2 = c2;
	this->delta_score = delta_score, this->global_score = global_score;
	final_score = 0;
}


pair<pair<int, int>, pair<int, int>> Move::getStep() {
	pair<int, int> step1 = make_pair(r1, c1);
	pair<int, int> step2 = make_pair(r2, c2);
	return make_pair(step1, step2);
}


bool Move::operator>(Move& other) {
	return this->delta_score > other.delta_score;
}


bool Move::operator<(Move& other) {
	return this->delta_score < other.delta_score;
}