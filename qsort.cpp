#include<cstdio>
#include<iostream>
using namespace std;

const int N = 1000001;
int a[N];
int b[N];
int asize;

int Max(int a, int b) {
	return (a > b) ? a : b;
}

int Min(int a, int b) {
	return (a < b) ? a : b;
}

int mid(int a, int b, int c) {
	if (a >= b && a >= c) {
		return Max(b, c);
	}
	else if (a <= b && a <= c) {
		return Min(b, c);
	}
	else return a;
}

int get_boundary(int left, int right) {
	int m = mid(a[left], a[right], a[(left + right) >> 1]);
	int l = left, r = right;
	int i = left;
	for (; i <= right; ++i) {
		if (a[i] < m) {
			b[l++] = a[i];
		}
		else if (a[i] > m){
			b[r--] = a[i];
		}
		if (l == r) break;
	}
	for (i = l; i <= r; ++i) {
		b[i] = m;
	}
	for (i = left; i <= right; ++i) {
		a[i] = b[i];
	}
	return l;
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
	for (i = 1; i <= asize; ++i) {
		printf("%d ", a[i]);
	}
	return 0;
}