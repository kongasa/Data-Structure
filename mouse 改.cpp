//±©¡¶≤Â»Î≈≈–Ú
#include<cstdio>
#include<iostream>
using namespace std;

const int N = 100001;
const int INF = 0x7fffffff;
int points[N * 2];
int strength[N * 2];
int idx[N * 2];

int getboundary(int start, int end) {
	int left = start;
	int right = end;
	int m = points[start];
	int n = strength[start];
	int k = idx[start];
	while (left < right) {
		while (left < right && points[right] <= m) {
			if (points[right] == m && idx[right] < k) break;
			--right;
		}
		points[left] = points[right];
		strength[left] = strength[right];
		idx[left] = idx[right];
		while (left < right && points[left] >= m) {
			if (points[left] == m && idx[left] > k) break;
			++left;
		}
		points[right] = points[left];
		strength[right] = strength[left];
		idx[right] = idx[left];
	}
	points[left] = m;
	strength[left] = n;
	idx[left] = k;
	return left;
}

void qsort(int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = getboundary(start, end);
	qsort(start, boundary - 1);
	qsort(boundary + 1, end);
}

void nsort(int Size) {
	int m, n, k;
	int j;
	for (int i = 2; i <= Size; ++i) {
		m = points[i];
		n = strength[i];
		k = idx[i];
		for (j = i - 1; j >= 1 && (points[j] < m || (points[j] == m && idx[j] > k)); --j) {
			points[j + 1] = points[j];
			strength[j + 1] = strength[j];
			idx[j + 1] = idx[j];
		}
		points[j + 1] = m;
		strength[j + 1] = n;
		idx[j + 1] = k;
	}
}

int main() {
	int n, r;
	int i;
	scanf("%d%d", &n, &r);
	for (i = 1; i <= n * 2; ++i) {
		scanf("%d", &points[i]);
		idx[i] = i;
	}
	for (i = 1; i <= n * 2; ++i) {
		scanf("%d", &strength[i]);
	}
	points[0] = INF;
	qsort(1, 2 * n);
	int j;
	for (i = 1; i <= r; ++i) {
		for (j = 1; j <= 2 * n; j += 2) {
			if (strength[j] > strength[j + 1]) {
				points[j] += 2;
			}
			else if (strength[j] < strength[j + 1]) {
				points[j + 1] += 2;
			}
			else {
				++points[j];
				++points[j + 1];
			}
		}
		nsort(2 * n);
	}
	for (i = 1; i <= 2 * n; ++i) {
		printf("%d ", idx[i]);
	}
	printf("\n");
	return 0;
}