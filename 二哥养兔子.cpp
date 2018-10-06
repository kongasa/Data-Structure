#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int Max = 10000;

class bint {
private:
	char num[Max];
	int length;
public:
	bint() :length(0) {
		for (int i = 0; i < Max; ++i) num[i] = '0';
	}
	bint(const int x);
	bint(const bint &other);
	bint(const char*);
	bint &operator=(const bint other);
	bint operator*(bint other);
	void print(int i);
	void print() { print(0); cout << endl; }
	bint operator+(bint other);
};

bint::bint(const int x) {
	int a = 10;
	length = 0;
	int t = x;
	for (int i = 0; i < Max; ++i) num[i] = '0';
	while (t) {
		num[length++] = t % 10 + '0';
		t /= 10;
	}
	if (x == 0) length = 1;
}

bint::bint(const char *other) {
	for (int i = 0; i < Max; ++i) num[i] = '0';
	int len = strlen(other);
	length = len;
	for (int i = 0; i < len; ++i) {
		num[i] = other[len - i - 1];
	}
}

bint::bint(const bint &other) {
	for (int i = 0; i < Max; ++i) num[i] = '0';
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

bint bint::operator+(bint other) {
	bint ans;
	int i, j;
	int carry = 0;
	int tmp;
	for (i = 0, j = 0; i < length && j < other.length; ++i, ++j) {
		tmp = num[i] - '0' + other.num[j] - '0' + carry;
		if (tmp >= 10) {
			tmp -= 10;
			carry = 1;
		}
		else carry = 0;
		ans.num[i] = tmp + '0';
	}
	for (; i < length; ++i) {
		tmp = num[i] - '0' + carry;
		if (tmp >= 10) {
			tmp -= 10;
			carry = 1;
		}
		else carry = 0;
		ans.num[i] = tmp + '0';
	}
	for (; j < other.length; ++j) {
		tmp = other.num[j] - '0' + carry;
		if (tmp >= 10) {
			tmp -= 10;
			carry = 1;
		}
		else carry = 0;
		ans.num[j] = tmp + '0';
	}
	ans.length = (length > other.length) ? length : other.length;
	if (carry == 1) {
		ans.num[ans.length++] = '1';
	}
	return ans;
}

#define ll bint

ll dp[1001][4];

int main() {
	int a, b, c, N;
	scanf("%d%d%d%d", &a, &b, &c, &N);
	dp[0][1] = 1;
	int i;
	for (i = 1; i <= N; ++i) {
		dp[i][1] = dp[i - 1][1] * a;
		dp[i][1] = dp[i][1] + dp[i - 1][2] * b;
		dp[i][1] = dp[i][1] + dp[i - 1][3] * c;
		dp[i][2] = dp[i - 1][1];
		dp[i][3] = dp[i - 1][2] + dp[i - 1][3];
	}
	(dp[N][1] + dp[N][2] + dp[N][3]).print();
	return 0;
}
