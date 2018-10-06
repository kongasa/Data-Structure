#include<cstdio>

int main() {
	int erge, dengzi, n;
	int count = 0;
	scanf("%d%d%d", &erge, &dengzi, &n);
	int i;
	int height;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &height);
		if (height <= erge + dengzi) {
			++count;
		}
	}
	printf("%d\n", count);
	return 0;
}