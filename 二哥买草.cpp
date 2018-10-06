
#include <iostream>
#include <cstdio>

using namespace std;

int get_boundary(int a[], int start, int end) {
	int left = start;
	int right = end;
	int b = a[start];
	while (left < right) {
		while ( left < right && a[right] < b) --right;
		a[left] = a[right];
		while (left < right && a[left] >= b) ++left;
		a[right] = a[left];
	}
	a[left] = b;
	return left;

}

void qsort(int a[], int start, int end) {
	if (start >= end) {
		return;
	}

	int boundary = get_boundary(a, start, end);
	qsort(a, start, boundary - 1);
	qsort(a, boundary + 1, end);
}

int a[10005];
int b[10005];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
	}

	qsort(a, 1, n);
	qsort(b, 1, m);
	int j = 1;
	int ans = n;
	for (i = 1; i <= n; ++i) {
		for (; j <= m && b[j] >= a[i]; ++j);
		if (j <= m) {
			++ans;
			++j;
		}
	}
	printf("%d\n", ans);
	return 0;
}