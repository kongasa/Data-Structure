#include<cstdio>

int p[1001];
int w[1001];
int v[1001];
int dp[1001][1001];

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d %d %d", &p[i], &w[i], &v[i]);
	}

	for (int vv = 1; vv <= m; ++vv) {
		for (i = 1; i <= n; ++i) {
			for (int k = 0; k <= p[i]; ++k) {
				if (vv < k * w[i]) {
					continue;
				}
				dp[i][vv] = max(dp[i][vv], dp[i - 1][vv - k * w[i]] + k * v[i]);
			}
		}
	}
	printf("%d", dp[n][m]);
	return 0;
}