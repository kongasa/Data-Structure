#include <iostream>
using namespace std;

class Divide_by_zero{};

class Long_int {
	friend ostream &operator<<(ostream &os,const  Long_int &n);
private:
	char *num;
	int length;
	int max_size;
	
	void double_space();
public:
	Long_int(int init_size = 10);
	Long_int(const Long_int &other);
	void push_back(char ch);
	Long_int operator/(Long_int &other);
	bool operator<(Long_int &other);
	~Long_int();
};

Long_int::Long_int(int init_size) :length(0), max_size(init_size) {
	num = new char[max_size];
}

Long_int::Long_int(const Long_int &other) {
	delete num;
	length = other.length;
	max_size = other.max_size;
	num = new char[max_size];
	for (int i = 0; i < length; i++)
		num[i] = other.num[i];
}

void Long_int::double_space() {
	char *p = num;
	max_size *= 2;
	num = new char[max_size];
	for (int i = 0; i < length; i++)
		num[i] = p[i];
}

void Long_int::push_back(char ch) {
	if (length == max_size) double_space();
	num[length++] = ch;
}

Long_int::~Long_int() {
	delete[] num;
}

ostream &operator<<(ostream &os, const Long_int &n) {
	for (int i = 0; i < n.length; i++)
		os << n.num[i];
	return os;
}

Long_int Long_int::operator/(Long_int &other) {
	if (other.length == 1 && other.num[0] == '0') throw Divide_by_zero();

	Long_int result;
}

bool Long_int::operator<(Long_int &other) {
	if (length < other.length) return true;
	else if (length > other.length) return false;
	else {
		for (int i = 0; i < length; i++) {
			if (num[i] < other.num[i]) return true;
			if (num[i] > other.num[i]) return false;
		}
		return false;
	}
}