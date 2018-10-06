#include <iostream>
#include <cmath>
using namespace std;

struct Sum {
	int value;
	int expo;
	void print() { cout << value << '(' << expo << ')'; }
	Sum() :value(1), expo(0) {}
};

class Seq_list {
private:
	int max_size, length;
	Sum *data;
	void double_space() {
		max_size *= 2;
		Sum *p = data;
		data = new Sum[max_size];
		for (int i = 0; i < length; ++i) data[i] = p[i];
		delete[] p;
	}
public:
	Seq_list():max_size(10), length(0), data(new Sum [max_size]){}
	void push_back(Sum s) {
		if (length == max_size) double_space();
		data[length++] = s;
	}
	int top() { return data[length - 1].value; }
	~Seq_list() { delete[] data; }
	void print() {
		for (int i = 0; i < length; ++i) data[i].print();
	}
	Sum &operator[](int i) {
		return data[i];
	}
	int get_length() { return length; }
};

bool is_prime(int N) {
	for (int i = 3; i * i <= N; i += 2)
		if (N % i == 0) return false;
	return true;
}

int get_min_prime(int N) {
	if (N % 2 == 0) return 2;
	int i;
	for (i = 3; i * i <= N; i +=2)
		if (N % i == 0 && is_prime(i)) return i;
	return -1;
}

int main() {
	int N, a;
	cin >> N;
	cout << N << "=";
	Sum p;
	Seq_list prime_divisor;

	while (true) {
		a = get_min_prime(N);
		if (a == -1) {
			if (N == 1) break;
			if (prime_divisor.top() == N) ++prime_divisor[prime_divisor.get_length() - 1].expo;
			else {
				p.value = N;
				p.expo = 1;
				prime_divisor.push_back(p);
			}
			break;
		}
		N /= a;
		if (prime_divisor.top() == a) ++prime_divisor[prime_divisor.get_length() - 1].expo;
		else {
			p.value = a;
			p.expo = 1;
			prime_divisor.push_back(p);
		}
	}
	prime_divisor.print();
	return 0;
}