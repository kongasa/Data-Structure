#include<cstdio>

int main() {
	int n, x, y, i, j, count = 0;
	scanf("%d %d %d", &n, &x, &y);
	int **map = new int*[n];
	for (i = 0; i < n; ++i) map[i] = new int[n];

	int round;
	for (round = 1; round <= (n + 1) / 2; ++round) {
		i = j = round - 1;
		if (i != 0) ++count;
		for (; j < n - round + 1; ++j) {
			if (x - 1 == i && y - 1 == j) { printf("%d\n", count); return 0; }
			++count;
		}
		--count;
		for (--j; i < n - round + 1; ++i) {
			if (x - 1 == i && y - 1 == j) { printf("%d\n", count); return 0; }
			++count;
		}
		--count;
		for (--i; j >= round - 1; --j) {
			if (x - 1 == i && y - 1 == j) { printf("%d\n", count); return 0; }
			++count;
		}
		--count;
		for (++j; i > round - 1; --i) {
			if (x - 1 == i && y - 1 == j) { printf("%d\n", count); return 0; }
			++count;
		}
		--count;
	}
}