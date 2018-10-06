#include<cstdio>

int start[25001];
int endc[25001];
int shifts[1000001];

int Max(int a, int b) {
	return a > b ? a : b;
}

int getboundary(int left, int right){
	int m = start[left];
	int n = endc[left];
	while (left < right) {
		while (left < right && start[right] > m) {
			--right;
		}
		start[left] = start[right];
		endc[left] = endc[right];
		while (left < right && start[left] <= m) {
			++left;
		}
		start[right] = start[left];
		endc[right] = endc[left];
	}
	start[left] = m;
	endc[left] = n;
	return left;
}

void qsort(int left, int right) {
	if (left >= right) {
		return;
	}
	int boundary = getboundary(left, right);
	qsort(left, boundary - 1);
	qsort(boundary + 1, right);
}

int main() {
	int n, t;
	scanf("%d%d", &n, &t);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &start[i], &endc[i]);
	}
	qsort(1, n);
	int ans = 0;
	int nowtime = 0;
	i = 1;
	int tmp = 0;
	while (nowtime < t) {
		if (i > n) break;
		if (start[i] > nowtime + 1) {
			ans = -1;
			break;
		}
		for (; i <= n && start[i] <= nowtime + 1; ++i) {
			tmp = Max(tmp, endc[i]);
		}
		nowtime = tmp;
		++ans;
	}
	if (nowtime < t) ans = -1;
	printf("%d\n", ans);
	return 0;
}