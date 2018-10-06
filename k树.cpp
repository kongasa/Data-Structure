#include<cstdio>

class my_int {
private:
	char num[201];
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

my_int dp[1000][1000];              //dp[i][j]为第j层第i类节点的个数
my_int sum[1000][1000];             



int main() {
	int k, h;
	scanf("%d %d", &k, &h);
	int i;
	int j;

	dp[1][1] = 1;
	for (i = 1; i <= k; ++i) {
		sum[i][1] = 1;
	}

	for (i = 2; i <= h; ++i) {
		for (j = 1; j <= k; ++j) {
			dp[j][i] = sum[k - j + 1][i - 1];
		}
		for (j = 1; j <= k; ++j) {
			sum[j][i] = sum[j][i] + sum[j - 1][i];
			sum[j][i] = sum[j][i] + dp[j][i];
		}
	}
	sum[k][h].print();
	return 0;
}
