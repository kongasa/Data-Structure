#include<cstdio>

class my_int {
private:
	char num[3000];
	int length;
public:
	my_int() {
		num[0] = '0';
		length = 1;
	}
	my_int(const my_int &other) {
		length = other.length;
		for (int i = 0; i < length; ++i) {
			num[i] = other.num[i];
		}
	}
	my_int operator+(my_int &other);
	my_int &operator=(my_int other) {
		if (this == &other) return *this;
		length = other.length;
		for (int i = 0; i < length; ++i) {
			num[i] = other.num[i];
		}
		return *this;
	}
	my_int &operator=(int x) {
		length = 1;
		num[length - 1] = '0' + x;
		return *this;
	}
	void print(int i) {
		if (i == length - 1) {
			printf("%c", num[i]);
		}
		else {
			print(i + 1);
			printf("%c", num[i]);
		}
	}
	void print() {
		print(0);
		printf("\n");
	}
};

my_int my_int::operator+(my_int &other) {
	my_int ans;
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

const int N = 10001;
my_int dp[N][2];

int main() {
	dp[1][0] = dp[1][1] = 1;
	dp[2][0] = dp[2][1] = 2;
	int n;
	scanf("%d", &n);
	int i;
	for (i = 3; i <= n; ++i) {
		dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
		dp[i][0] = dp[i - 2][1] + dp[i - 1][1];
	}
	(dp[n][0] + dp[n][1]).print();
	return 0;
}