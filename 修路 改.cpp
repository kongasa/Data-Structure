#include<cstdio>
#include<iostream>
using namespace std;


int a[2001];
int b[2001];
int c[2001];

/*
void quick_sort1(int[], int, int);
int get_boundary1(int[], int, int);
void quick_sort2(int[], int, int);
int get_boundary2(int[], int, int);
int abs(int x) {
	return (x > 0) ? x : (-x);
}

int main() {
	int N;
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		c[i] = a[i];
	}
	quick_sort1(b, 1, N);
	quick_sort2(c, 1, N);

	long long int sum1 = 0, sum2 = 0;
	for (i = 1; i <= N; ++i) {
		sum1 += abs(a[i] - b[i]);
		sum2 += abs(a[i] - c[i]);
	}
	sum1 >>= 1;
	sum2 >>= 1;
	cout << ((sum1 < sum2) ? sum1 : sum2) << endl;
	return 0;
}

void quick_sort1(int m[], int left, int right) {
	if (left >= right) {
		return;
	}
	int boundary = get_boundary1(m, left, right);
	quick_sort1(m, left, boundary - 1);
	quick_sort1(m, boundary + 1, right);
}

int get_boundary1(int m[], int start, int end) {
	int left = start;
	int right = end;
	int p = m[start];
	while (left < right) {
		while (left < right && m[right] > p) {
			--right;
		}
		m[left] = m[right];
		while (left < right && m[left] <= p) {
			++left;
		}
		m[right] = m[left];
	}
	m[left] = p;
	return left;
}

void quick_sort2(int m[], int left, int right) {
	if (left >= right) {
		return;
	}
	int boundary = get_boundary2(m, left, right);
	quick_sort2(m, left, boundary - 1);
	quick_sort2(m, boundary + 1, right);
}

int get_boundary2(int m[], int start, int end) {
	int left = start;
	int right = end;
	int p = m[start];
	while (left < right) {
		while (left < right && m[right] < p) {
			--right;
		}
		m[left] = m[right];
		while (left < right && m[left] >= p) {
			++left;
		}
		m[right] = m[left];
	}
	m[left] = p;
	return left;
}
*/

int abs(int x) {
	return (x > 0) ? x : (-x);
}

void solve(int b[], int c[], int left, int right) {   //b·Ç½µ£¬c·ÇÉı
	if (left >= right) {
		return;
	}
	int mid = (left + right) >> 1;
	solve(b, c, left, mid);
	solve(b, c, mid + 1, right);
	int sum1 = 0, sum2 = 0;
	int i;
	if (b[mid] > b[mid + 1]) {
		for (i = mid; i >= left; --i) {
			if (b[i] <= b[mid + 1]) { break; }
			sum1 += abs(b[i] - b[mid + 1]);
		}
		for (i = mid + 1; i <= right; ++i) {
			if (b[i] >= b[mid]) { break; }
			sum2 += abs(b[mid] - b[i]);
		}
		if (sum1 <= sum2) {
			for (i = mid; i >= left; --i) {
				if (b[i] <= b[mid + 1]) { break; }
				b[i] = b[mid + 1];
			}
		}
		else {
			for (i = mid + 1; i <= right; ++i) {
				if (b[i] >= b[mid]) { break; }
				b[i] = b[mid];
			}
		}
	}
	sum1 = sum2 = 0;
	if (c[mid] < c[mid + 1]) {
		for (i = mid; i >= left; --i) {
			if (c[i] >= c[mid + 1]) { break; }
			sum1 += abs(c[i] - c[mid + 1]);
		}
		for (i = mid + 1; i <= right; ++i) {
			if (c[i] <= c[mid]) { break; }
			sum2 += abs(c[mid] - c[i]);
		}
		if (sum1 <= sum2) {
			for (i = mid; i >= left; --i) {
				if (c[i] >= c[mid + 1]) { break; }
				c[i] = c[mid + 1];
			}
		}
		else {
			for (i = mid + 1; i <= right; ++i) {
				if (c[i] <= c[mid]) { break; }
				c[i] = c[mid];
			}
		}
//		printf("sum1 :%d test  sum2:%d\n", sum1, sum2);
	}
}

int main() {
	int N;
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		scanf("%d", &a[i]);
		b[i] = a[i];
		c[i] = a[i];
	}

	solve(b, c, 1, N);
	int sum1 = 0, sum2 = 0;
	for (int i = 1; i <= N; ++i) {
		printf("%d ", b[i]);
	}
	printf("\n");
	for (i = 1; i <= N; ++i) {
		printf("%d ", c[i]);
	}
	printf("\n");
	for (i = 1; i <= N; ++i) {
		sum1 += abs(b[i] - a[i]);
		sum2 += abs(c[i] - a[i]);
	}
	printf("%d\n", ((sum1 > sum2) ? sum2 : sum1));
	return 0;
}