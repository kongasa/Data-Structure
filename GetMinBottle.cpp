#include<cstdio>

int a[10000];

int lowbit(int x) {
	return (x & (-x));
}

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	if (n < k) {
		printf("%d\n", k - n);
		return 0;
	}
	int count = 0;
	int tmp;
	while (n > 0) {
		a[++count] = lowbit(n);
		n -= a[count];
	}
	int i = 1;
	int ans = 0;

	while (count > k) {
		ans += a[i + 1] - a[i];
		a[i + 1] *= 2;
		++i;
		--count;
	}
	printf("%d\n", ans);
	return 0;
}