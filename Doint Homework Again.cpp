#include<cstdio>
#include<iostream>
using namespace std;

int ans[10000];
int num;

int ddl[1001];
int penalty[1001];

int heap[1001];
int length;

void percolate_down(int i) {
	int idx = i;
	int m = heap[idx];
	int child;
	for (; idx * 2 <= length; idx = child) {
		child = idx * 2;
		if (child + 1 <= length && heap[child] < heap[child + 1]) {
			++child;
		}
		if (heap[child] > m) {
			heap[idx] = heap[child];
		}
		else break;
	}
	heap[idx] = m;
}

void enqueue(int x) {
	++length;
	int idx = length;
	for (; idx > 1 && x > heap[idx / 2]; idx /= 2) {
		heap[idx] = heap[idx / 2];
	}
	heap[idx] = x;
}

int dequeue() {
	int tmp = heap[1];
	heap[1] = heap[length--];
	percolate_down(1);
	return tmp;
}

int getboundary(int start, int end) {
	int m = ddl[start];
	int n = penalty[start];
	while (start < end) {
		while (start < end && ddl[end] < m) {
			--end;
		}
		ddl[start] = ddl[end];
		penalty[start] = penalty[end];
		while (start < end && ddl[start] >= m) {
			++start;
		}
		ddl[end] = ddl[start];
		penalty[end] = penalty[start];
	}
	ddl[start] = m;
	penalty[start] = n;
	return start;
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
	int t;
	int n;
	int i;
	int j;
	int k;
	int done;
	int total;
	scanf("%d", &t);
	for (i = 1; i <= t; ++i) {
		length = 0;
		scanf("%d", &n);
		total = done = 0;
		for (j = 1; j <= n; ++j) {
			scanf("%d", &ddl[j]);
		}
		for (j = 1; j <= n; ++j) {
			scanf("%d", &penalty[j]);
			total += penalty[j];
		}
		qsort(1, n);
		for (j = ddl[1], k = 1; j >= 1; --j) {
			if (j == ddl[k]) {
				for (; k + 1 <= n && ddl[k + 1] == ddl[k]; ++k) {
					enqueue(penalty[k]);
				}
				enqueue(penalty[k]);
				done += dequeue();
				++k;
			}
			else {
				if (length) {
					done += dequeue();
				}
			}
		}
		ans[num++] = total - done;
	}
	for (i = 0; i < num; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

//int main() {
//	for (int i = 1; i <= 10; ++i) {
//		ddl[i] = i * 2;
//	}
//	qsort(1, 10);
//	for (int i = 1; i <= 10; ++i) {
//		cout << ddl[i] << ' ';
//	}
//	cout << endl;
//}