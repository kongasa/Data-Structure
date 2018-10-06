#include<cstdio>
#include<iostream>
using namespace std;

long long int tree[100001];
int orig_numbers[100001];
//int trans_nums[100001];

int lowbit(int x) {
	return (x & (-x));
}

void update(int x, int n) {
	int y = x;
	while (y <= n) {
		++tree[y];
		y += lowbit(y);
	}
}

long long int get_sum(int x) {                         //第x个元素之前元素的和
	long long int ans = 0LL;
	while (x > 0) {
		ans += tree[x];
		x -= lowbit(x);
	}
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
//	int tmp;
	long long int sum = 0LL;
	int Max = 0;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &orig_numbers[i]);
		if (orig_numbers[i] > Max) {
			Max = orig_numbers[i];
		}
	}

	for (i = n; i >= 1; --i) {
		update(orig_numbers[i], Max);
		sum += get_sum(orig_numbers[i] - 1);
	}
	printf("%lld", sum);
	return 0;
}