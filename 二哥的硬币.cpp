#include<cstdio>
#include<iostream>
using namespace std;


int dp[100001];
int A[101];
int C[101];
int used[100001];
int ans[1000];
int cnt;

void init(int m) {
	for (int i = 0; i <= m; ++i) {
		used[i] = 0;
	}
}

int main() {
	int n, m;
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) {
			break;
		}

		++cnt;
		int i;
		for (i = 1; i <= n; ++i) {
			scanf("%d", A + i);
		}
		for (i = 1; i <= n; ++i) {
			scanf("%d", C + i);
		}
		for (i = 1; i <= m; ++i) dp[i] = 0;
		dp[0] = 1;
		for (i = 1; i <= n; ++i) {
			init(m);
			for (int j = A[i]; j <= m; ++j) {
				if (dp[j - A[i]] == 1 && used[j - A[i]] < C[i] && dp[j] == 0) {
					dp[j] = 1;
					++ans[cnt];
					used[j] = used[j - A[i]] + 1;
				}
			}
		}
	}
	for (int i = 1; i <= cnt; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}