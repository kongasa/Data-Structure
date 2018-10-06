#include<cstdio>
#include<iostream>
using namespace std;
#define ll long long

int dp[200001];                           //dp[i] 从i到T的最大长度
ll length[200001];                      //length[i] 以i开头的最大长度的数量

int Max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	int S, T;
	scanf("%d%d", &S, &T);
	int i;
	for (i = S; i <= T; ++i) {
		dp[i] = 1;
		length[i] = 1LL;
	}

	int max_length = 0;
	for (i = T - 1; i >= S; --i) {
		int m;
		int j;
		for (m = 1; m <= 100; ++m) {
			if ((m * i) % 100 != 0) continue;
			if ((j = i + (m * i) / 100) > T) break;
			if (dp[j] + 1 > dp[i]) {
				dp[i] = dp[j] + 1;
				length[i] = length[j];
			}
			else if (dp[j] + 1 == dp[i]) {
				length[i] += length[j];
			}
		}
		max_length = Max(max_length, dp[i]);
	}

	ll count = 0;
	for (i = S; i <= T; ++i) {
		if (dp[i] == max_length) count += length[i];
	}
	//for (i = S; i <= T; ++i) {
	//	printf("dp[i]:%d length[i]:%d\n", dp[i], length[i]);
	//}
	cout << max_length << endl << count << endl;
	return 0;
}