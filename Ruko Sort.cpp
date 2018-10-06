#include<cstdio>

const int N = 1000001;
int a[N];
int asize;
int ans[N];

int get_boundary(int left, int right) {
	int m = a[left];
	int start = left;
	int end = right;
	while (start < end) {
		while (start < end && a[end] > m) {
			--end;
		}
		a[start] = a[end];
		while (start < end && a[start] <= m) {
			++start;
		}
		a[end] = a[start];
	}
	a[start] = m;
	return start;
}

void qsort(int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary(start, end);
	qsort(start, boundary - 1);
	qsort(boundary + 1, end);
}

int main() {
	scanf("%d", &asize);
	int i;
	for (i = 1; i <= asize; ++i) {
		scanf("%d", &a[i]);
	}
	qsort(1, asize);
	int cnt = 1;
	ans[1] = a[1];
	for (i = 2; i <= asize; ++i) {
		if (a[i] != a[i - 1]) {
			ans[++cnt] = a[i];
		}
	}
	printf("%d\n", cnt);
	for (i = 1; i <= cnt; ++i) {
		printf("%d ", ans[i]);
	}
	return 0;
}