#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

class bint {
private:
	char num[1000];
	int length;
public:
	bint() :length(0){
		for (int i = 0; i < 1000; ++i) num[i] = '0';
	}
	bint(const int x);
	bint(const bint &other);
	bint(const char*);
	bint &operator=(const bint other);
	bint operator*(bint other);
	void print(int i);
	void print() { print(0); cout << endl; }
};

bint::bint(const int x) {
	int a = 10;
	length = 0;
	int t = x;
	for (int i = 0; i < 1000; ++i) num[i] = '0';
	while (t) {
		num[length++] = t % 10 + '0';
		t /= 10;
	}
	if (x == 0) length = 1;
}

bint::bint(const char *other) {
	for (int i = 0; i < 1000; ++i) num[i] = '0';
	int len = strlen(other);
	length = len;
	for (int i = 0; i < len; ++i) {
		num[i] = other[len - i - 1];
	}
}

bint::bint(const bint &other) {
	for (int i = 0; i < 1000; ++i) num[i] = '0';
	length = other.length;
	for (int i = 0; i < length; ++i) {
		num[i] = other.num[i];
	}
}

bint &bint::operator=(const bint other) {
	if (this == &other) return *this;
	length = other.length;
	for (int i = 0; i < length; ++i) {
		num[i] = other.num[i];
	}
	return *this;
}

bint bint::operator*(bint other) {
	bint ans;
	if ((length == 1 && num[0] == '0') || other.length == 1 && other.num[0] == '0') {
		ans.length = 1;
		return ans;
	}
	for (int i = 0; i < other.length; ++i) {
		int mu;
		int carry1 = 0;
		int sum;
		int carry2 = 0;
		int k;
		for (k = 0; k < length; ++k) {
			mu = (other.num[i] - '0') * (num[k] - '0') + carry1;
			if (mu >= 10) {
				carry1 = mu / 10;
				mu %= 10;
			}
			else carry1 = 0;

			sum = mu + ans.num[i + k] - '0' + carry2;
			if (sum >= 10) {
				sum -= 10;
				carry2 = 1;
			}
			else carry2 = 0;
			ans.num[i + k] = sum + '0';
		}
		if (carry1 != 0) {
			ans.num[i + k] = carry1 + '0';
			ans.length = i + k + 1;
		}
		else ans.length = i + k;
		if (carry2 != 0) {
			ans.num[i + k] += 1;
			ans.length = i + k + 1;
		}
//		else ans.length = i + k;
	}
	return ans;
}

void bint::print(int i) {
	if (i == length - 1) {
		printf("%c", num[i]);
	}
	else {
		print(i + 1);
		printf("%c", num[i]);
	}
}

int main() {
	char a[1000];
	char b[1000];
	cin >> a >> b;
	bint c(a);
	bint d(b);
	bint e;
	e = c * d;
	e.print();
	return 0;
}