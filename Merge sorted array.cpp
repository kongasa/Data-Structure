#include<cstdio>

int a[1000000];
int b[1000000];
int c[1000000];

int main() {
	int m, n;
	scanf("%d%d", &m, &n);
	int i, j;
	for (i = 0; i < m; ++i) {
		scanf("%d", &a[i]);
	}
	for (i = 0; i < n; ++i) {
		scanf("%d", &b[i]);
	}
	i = j = 0;
	int k = 0;
	for (; i < m && j < n; ++k) {
		if (a[i] < b[j]) {
			c[k] = a[i++];
		}
		else {
			c[k] = b[j++];
		}
	}
	for (; i < m; ++i) {
		c[k++] = a[i];
	}
	for (; j < n; ++j) {
		c[k++] = b[j];
	}
	for (i = 0; i < k; ++i) {
		printf("%d ", c[i]);
	}
	return 0;
}