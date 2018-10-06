#include<cstdio>

int st[200001][20];
int m;

int query(int, int);
int max(int, int);
int log2(int);

int query(int left, int right) {
	return max(st[left][m], st[right - (1 << m) + 1][m]);
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int log2(int x) {
	int ans = 0;
	while (x > 1) {
		x >>= 1;
		++ans;
	}
	return ans;
}

int main() {
	int n, k;
	scanf("%d\n%d", &k, &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &st[i][0]);
	}

	int j;
	for (j = 1; (1 << j) <= n; ++j) {
		for (i = 1; i + (1 << j) - 1 <= n; ++i) {
			st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
		}
	}

	int Max = 0;
	m = log2(k);
	for (i = 1; i <= n - k + 1; ++i) {
		printf("%d ", query(i, i + k - 1));
	}
	return 0;
}