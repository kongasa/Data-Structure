#include<cstdio>

int p[1005];
int w[1005];
int v[1005];
int dp[1005];
int used[1005][1005];                  //uesd[i][j] = m表示容量为i，取得最好情况时第j个还剩下m可用

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int i;
	int use;
	bool flag;
	for (i = 1; i <= n; ++i) {
		scanf("%d %d %d", &p[i], &w[i], &v[i]);
	}

	for (i = 1; i <= m; ++i) {
		use = 0;
		flag = false;
		int tmp;
		for (int j = 1; j <= n; ++j) {
			if (i < w[j] || used[i - w[j]][j] == p[j]) {
				continue;
			}
			if (dp[i - w[j]] + v[j] <= dp[i - 1]) {
				continue;
			}
			flag = true;
			if (dp[i - w[j]] + v[j] > dp[i]) {
				dp[i] = dp[i - w[j]] + v[j];
				use = j;
				tmp = i - w[j];
			}
		}
		if (!flag) {
			tmp = i - 1;
			dp[i] = dp[i - 1];
		}

		for (int k = 1; k <= n; ++k) {
			used[i][k] = used[tmp][k];
		}
		if (use != 0) {
			++used[i][use];
		}
	}

	printf("%d\n", dp[m]);
	return 0;
}