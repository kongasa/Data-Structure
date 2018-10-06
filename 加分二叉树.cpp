#include<cstdio>
#include<iostream>
using namespace std;

int di[30];
int dp[30][30];
int idx[30][30];


void preorder(int idx[][30], int start, int end) {
	int i = idx[start][end];
	printf("%d ", idx[start][end]);
	if (idx[start][idx[start][end] - 1] != 0) preorder(idx, start, idx[start][end] - 1);
	if (idx[idx[start][end] + 1][end] != 0) preorder(idx, idx[start][end] + 1, end);
}

int main() {
	int N;
	scanf("%d", &N);
	int i;
	int tmp;
	for (i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			if (i == j) scanf("%d", &dp[i][j]);
			else if (i > j) dp[i][j] = 1;
		}
	for (i = 0; i <= N; ++i) {
		dp[0][i] = 1;
		dp[i][0] = 1;
	}

	for (int len = 1; len <= N; ++len) {
		for (i = 1; i <= N - len + 1; ++i) {
			int j = i + len - 1;
			if (i == j) {
				idx[i][j] = i;
				continue;
			}
			for (int k = i; k <= j; ++k)
				if ((tmp = dp[i][k - 1] * dp[k + 1][j] + dp[k][k]) > dp[i][j]) {
					dp[i][j] = tmp;
					idx[i][j] = k;
				}
		}
	}
	printf("%d\n", dp[1][N]);
	preorder(idx, 1, N);
}
