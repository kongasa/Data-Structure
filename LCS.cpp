#include<cstdio>

char x[1002];
char y[1002];
int dp[1001][1001];

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	scanf("%s\n%s", x, y);

	int i, j;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j){
			if (x[i - 1] == y[j - 1]) {
				dp[i][j] = dp[i - 1][j - 1] + 1;
			}
			else {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
	}
	printf("%d\n", dp[n][m]);
	return 0;
}