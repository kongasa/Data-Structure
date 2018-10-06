#include<cstdio>

int c[1001];
int w[1001];
int dp[10001];

int max(int a, int b) {
	return ((a > b) ? a : b);
}

int main() {
	int V, N;
	scanf("%d %d", &V, &N);
	int i;
	for (i = 1; i <= N; ++i) {
		scanf("%d %d", &c[i], &w[i]);
	}

	for (i = 1; i <= V; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (i < c[j]) continue;
			dp[i] = max(dp[i], dp[i - c[j]] + w[j]);
		}
	}
	printf("%d\n", dp[V]);
}