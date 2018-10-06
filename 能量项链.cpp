#include<cstdio>
#include<iostream>
using namespace std;

int head[201];
int rear[201];
int dp[201][201];

int main() {
	int N;
	scanf("%d", &N);
	int i;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &head[i]);
		rear[i - 1] = head[i];
	}
	for (; i <= 2 * N; ++i) {
		head[i] = head[i - N];
		rear[i - 1] = head[i];
	}
	rear[i - 1] = head[1];
//	for (i = 1; i <= 2 * N; ++i) {
//		cout << head[i] << " " << rear[i] << endl;
//	}

	int tmp;
	
	for (int len = 0; len < N; ++len) {
		for (i = 1; i <= 2 * N - 1 - len; ++i) {
			int j = i + len;
			if (i == j) {
				dp[i][j] = 0;
				continue;
			}
			for (int k = i; k < j; ++k) {
				if ((tmp = dp[i][k] + dp[k + 1][j] + head[i] * rear[j] * rear[k]) > dp[i][j]) {
					dp[i][j] = tmp;
				}
			}
		}
	}
	int Max = 0;
	for (i = 1; i <= N; ++i) {
		if (dp[i][i + N - 1] > Max) {
			Max = dp[i][i + N - 1];
		}
	}
	printf("%d\n", Max);


}