#include<cstdio>
#include<iostream>
using namespace std;

const int MAX = 50002;
int point[MAX];
int l, m, n;

bool check(int ans) {
	int lastpoint = 0;
	int i = 1;
	int cnt = 0;
	for (; i <= n; ++i) {
		if (point[i] - point[lastpoint] < ans) {
			++cnt;
		}
		else {
			lastpoint = i;
		}
	}
	if (l - point[lastpoint] < ans) {
		++cnt;
	}
	if (cnt <= m) return true;
	else return false;
}

int main() {
	scanf("%d%d%d", &l, &n, &m);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &point[i]);
	}
	int left = 1;
	int right = l;
	int mid;
	while (left < right) {
		mid = (left + right) / 2 + 1;
		if (check(mid)) left = mid;
		else right = mid - 1;
	}
	printf("%d\n", left);
	return 0;
}