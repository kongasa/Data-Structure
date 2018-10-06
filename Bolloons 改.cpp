#include<cstdio>
#include<iostream>
using namespace std;

long long heap[300000];                   //记录初始名次比我高的人升天所需气球数
int length = 0;
long long ac[300000];                     //记录初始名次比我低的人的ac
long long w[300000];                      //记录初始名次比我低的人的w
int lower = 0;                            //成绩小于等于我的人的个数

void enqueue(long long);
long long dequeue();
void percolate_down(int);
int get_boundary1(long long[], long long[], int, int);
void qsort1(long long[], long long[], int, int);            //降序排列

int get_boundary1(long long a[], long long b[], int start, int end) {
	int left = start;
	int right = end;
	long long m = a[start];
	long long n = b[start];
	while (left < right) {
		while (left < right && a[right] < m) {
			--right;
		}
		a[left] = a[right];
		b[left] = b[right];
		while (left < right && a[left] >= m) {
			++left;
		}
		a[right] = a[left];
		b[right] = b[left];
	}
	a[left] = m;
	b[left] = n;
	return left;
}

void qsort1(long long a[], long long b[], int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary1(a, b, start, end);
	qsort1(a, b, start, boundary - 1);
	qsort1(a, b, boundary + 1, end);
}

void enqueue(long long x) {
	heap[++length] = x;
	int idx = length;
	for (; idx > 1 && heap[idx / 2] > x; idx /= 2) {
		heap[idx] = heap[idx / 2];
	}
	heap[idx] = x;
}

long long dequeue() {
	long long ans = heap[1];
	heap[1] = heap[length--];
	percolate_down(1);
	return ans;
}

int Min(int a, int b) {
	return (a < b) ? a : b;
}

void percolate_down(int idx) {
	long long int m = heap[idx];
	int child;
	for (; idx * 2 <= length; idx = child) {
		child = idx * 2;
		if (child + 1 <= length && heap[child] > heap[child + 1]) {
			child++;
		}
		if (heap[child] < m) {
			heap[idx] = heap[child];
		}
		else break;
	}
	heap[idx] = m;
}

int main() {
	int N;
	scanf("%d", &N);
	int i;
	cin >> ac[0] >> w[0];
	long long score, weight;
	for (i = 1; i < N; ++i) {
		cin >> score >> weight;
		if (score > ac[0]) {
			enqueue(weight - score + 1LL);
		}
		else {
			ac[++lower] = score;
			w[lower] = weight;
		}
	}

	qsort1(ac, w, 1, lower);

	long long *my_ac = ac, *my_w = w;
	int highest_rank = length + 1;
	while (length > 0 && my_ac[0] >= heap[1]) {
		my_ac[0] -= dequeue();
		while (lower > 0 && my_ac[1] > my_ac[0]) {
			enqueue(my_w[1] - my_ac[1] + 1LL);
			my_ac[1] = my_ac[0];
			my_w[1] = my_w[0];
			++my_ac;
			++my_w;
			--lower;
		}
		highest_rank = Min(highest_rank, length + 1);
	}
	cout << highest_rank << endl;
	return 0;
}