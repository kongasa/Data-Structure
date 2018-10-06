#include<cstdio>
#include<iostream>
using namespace std;

int price[1001];
int ans[300001];                   //0-no 1-yes
int n;
int dp[40000001];

int Min(int a, int b) {
	return (a < b) ? a : b;
}


int main() {
	scanf("%d", &n);
	int i;
	int min_price = 10000;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &price[i]);
		min_price = Min(min_price, price[i]);
	}

	int m;
	int count = 0;
	int money;

	dp[0] = 1;
	for (i = min_price; i <= 40000001; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i >= j && dp[i - price[j]] == 1) {
				dp[i] = 1;
				break;
			}
		}
	}
	scanf("%d", &m);
	for (i = 1; i <= m; ++i) {
		scanf("%d", &money);
		ans[++count] = dp[money];
	}
	for (i = 1; i <= count; ++i) {
		if (ans[i] == 0) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}