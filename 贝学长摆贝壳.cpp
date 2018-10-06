#include<cstdio>
#include<iostream>
using namespace std;

int a[100001];
int b[100001];
int c[100001];                               //c[i] = j代表a中i的索引是j
int d[100001];         
int up[100001];                              //求d的最长单调上升子序列
int max_length = 0;
int length = 0;

int get_pos(int start, int end, int x) {
	int left = start;
	int right = end;
	int mid;
	while (left < right) {
		mid = (left + right) >> 1;
		if (up[mid] < x) left = mid + 1;
		else right = mid;
	}
	return left;
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		c[a[i]] = i;
	}
	for (i = 1; i <= n; ++i) {
		scanf("%d", &b[i]);
		d[c[b[i]]] = i;
	}

	for (i = 1; i <= n; ++i) {
		if (d[i] > up[length]) {
			up[++length] = d[i];
		}
		else {
			int idx = get_pos(1, length, d[i]);
			up[idx] = d[i];
		}
	}

	printf("%d\n", length);

	return 0;
}