#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int index;
	int data;
	node(int a = 0, int b = 0) : index(a), data(b) {}
};

void fast_sort1(int[], int[], int, int);
int get_boundary1(int[], int[], int, int);
void fast_sort2(node[], int[], int, int);
int get_boundary2(node[], int[], int, int);

class Binary_heap {
private:
	int max_size;
	int current_size;
	int *data;
	void percolate_down(int idx);
	void double_space();
	void build_heap();
public:
	Binary_heap(int init_size = 10) : max_size(init_size + 10), current_size(0), data(new int[max_size]) { data[1] = 1; }
	Binary_heap(int a[], int left, int right);
	~Binary_heap() { delete[] data; }
	void enqueue(int x);
	int dequeue();
	int front() { return data[1]; }
	void print() {
		for (int i = 1; i <= current_size; ++i) {
			printf("%d ", data[i]);
		}
		printf("\n");
	}
};

int Binary_heap::dequeue() {
	int tmp = data[1];
	data[1] = data[current_size--];
	percolate_down(1);
	return tmp;
}

Binary_heap::Binary_heap(int a[], int left, int right) {
	max_size = right - left + 11;
	current_size = right - left + 1;
	data = new int[max_size];
	int i;
	for (i = 1; i <= right - left + 1; ++i) {
		data[i] = a[left + i - 1];
	}
	build_heap();
}

void Binary_heap::build_heap() {
	int i = current_size / 2;
	for (; i >= 1; --i) {
		percolate_down(i);
	}
}

void Binary_heap::percolate_down(int idx) {
	int tmp = data[idx];
	int child;
	for (; idx * 2 <= current_size; idx = child) {
		child = idx * 2;
		if (child != current_size && data[child] < data[child + 1]) {
			++child;
		}
		if (data[child] > tmp) {
			data[idx] = data[child];
		}
		else { break; }
	}
	data[idx] = tmp;
}

void Binary_heap::double_space() {
	max_size *= 2;
	int *p = data;
	data = new int[max_size];
	for (int i = 1; i <= current_size; ++i) {
		data[i] = p[i];
	}
	delete[] p;
}

void Binary_heap::enqueue(int x) {
	if (current_size == max_size - 1) {
		double_space();
	}

	int hole = ++current_size;
	for (; hole > 1 && x > data[hole / 2]; hole /= 2) {
		data[hole] = data[hole / 2];
	}
	data[hole] = x;
}

int grades[200001];
int scho[200001];
node tmp[200001];
int index[200001];
int save[200001];                      //保存某一边的奖学金之和

int main() {
	int N, C, F;
	scanf("%d %d %d", &N, &C, &F);
	int m = N / 2;                                  //m个人为一边
	int i;
	for (i = 1; i <= C; ++i) {
		scanf("%d %d", &grades[i], &scho[i]);
	}
	if (N == 0) {
		printf("%d", -1);
		return 0;
	}

	fast_sort1(grades, scho, 1, C);

	Binary_heap A(scho, C - m + 1, C);
	int sum1 = 0, sum2 = 0;
	for (i = C; i >= C - m + 1; --i) {
		sum2 += scho[i];
	}
	save[C - m] = sum2;
	int tmp;
	for (i = C - m - 1; i >= m + 1; --i) {
//		A.print();
		if (A.front() > scho[i + 1]) {
			tmp = A.dequeue();
			A.enqueue(scho[i + 1]);
			sum2 += scho[i + 1] - tmp;
		}
//		A.print();
		save[i] = sum2;
	}

	/*for (i = m + 1; i <= C - m; ++i) {
		printf("%d ", save[i]);
	}
	printf("\n");*/

	Binary_heap B(scho, 1, m);
	for (i = 1; i <= m; ++i) {
		sum1 += scho[i];
	}
	if (sum1 + scho[m + 1] + save[m + 1] <= F) {
//		B.print();
		printf("%d\n", grades[m + 1]);
		return 0;
	}
	for (i = m + 2; i <= C - m; ++i) {
	/*	B.print();*/
		if (B.front() > scho[i - 1]) {
			tmp = B.dequeue();
			B.enqueue(scho[i - 1]);
			sum1 += scho[i - 1] - tmp;
		}
//		B.print();
		if (sum1 + scho[i] + save[i] <= F) {
			printf("%d\n", grades[i]);
			return 0;
		}
	}
	printf("%d\n", -1);
	return 0;
}


/*
int main() {
	int N, C, F;
	scanf("%d %d %d", &N, &C, &F);
	int m = N / 2;
	int i, j;
	for (i = 1; i <= C; ++i) {
		scanf("%d %d", &grades[i], &scho[i]);
	}
	fast_sort1(grades, scho, 1, C);

//	Binary_heap A;
	Binary_heap A(scho, 1, m);

	int sum1 = 0, sum2 = 0;
	for (int j = 1; j <= m; ++j) {
//		A.enqueue(scho[j]);
		sum1 += scho[j];
	}
	for (j = m + 2; j <= C; ++j) {
		tmp[j] = node(j, scho[j]);
		index[j] = j;
	}
	fast_sort2(tmp, index, m + 2, C);
	for (j = m + 2; j <= N; ++j) {
		sum2 += tmp[j].data;
	}

	i = m + 1;
	if (sum1 + sum2 + scho[i] <= F) {
		printf("%d\n", grades[i]);
		return 0;
	}

	int max1, max2;
	int mid;
	int count = 1;
	int flag = false;
	max2 = tmp[N].data;
	max1 = A.front();
	for (i = m + 2; i <= C - m; ++i) {
		int last = i - 1;
		tmp[index[i]].data = 0;
		if (scho[last] < max1) {
			A.dequeue();
			A.enqueue(scho[last]);
			sum1 += scho[last] - max1;
			max1 = A.front();
		}
		if (scho_ship[i] <= max2) {
			while (tmp[N + count].data == 0) {
				++count;
			}
			max2 = tmp[N + count].data;
			++count;
			sum2 += -scho_ship[i] + max2;
		}
		if (sum1 + sum2 + scho[i] <= F) {
			mid = grades[i];
			flag = true;
			break;
		}
	}
	if (!flag) {
		printf("%d\n", -1);
	}
	else {
		printf("%d\n", mid);
	}
	return 0;
}
*/

void fast_sort1(int a[], int b[], int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary1(a, b, start, end);
	fast_sort1(a, b, start, boundary - 1);
	fast_sort1(a, b, boundary + 1, end);
}

int get_boundary1(int a[], int b[], int start, int end) {
	int left = start;
	int right = end;
	int m = a[left];
	int n = b[left];
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

void fast_sort2(node a[], int b[], int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary2(a, b, start, end);
	fast_sort2(a, b, start, boundary - 1);
	fast_sort2(a, b, boundary + 1, end);
}

int get_boundary2(node a[], int b[], int start, int end) {
	int left = start;
	int right = end;
	node m = a[left];
	int n = left;
	while (left < right) {
		while (left < right && a[right].data > m.data) {
			--right;
		}
		a[left] = a[right];
		b[a[left].index] = left;
		while (left < right && a[left].data <= m.data) {
			++left;
		}
		if (left == right) {
			break;
		}
		a[right] = a[left];
		b[a[right].index] = right;
	}
	a[left] = m;
	b[m.index] = left;
	return left;
}

