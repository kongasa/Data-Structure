#include<cstdio>

const int MAX = 200001;
int heap[MAX];
int tmp[MAX];
int money[MAX];
int grades[MAX];
int save[MAX];
int current_length;

void q_sort(int[], int[], int, int);
int get_boundary(int[], int[], int, int);
int dequeue();
void enqueue(int);
void percolate_down(int);

int main() {
	int N, C, F;
	scanf("%d %d %d", &N, &C, &F);
	int i, j;
	for (i = 1; i <= C; ++i) {
		scanf("%d %d", &grades[i], &money[i]);
	}

	q_sort(grades, money, 1, C);
	int m = N / 2;
	int sum1 = 0, sum2 = 0;
	for (i = C; i >= C - m + 1; --i) {
		sum2 += money[i];
		heap[C - i + 1] = money[i];
	}
	current_length = m;
	for (i = current_length / 2; i > 0; --i) {
		percolate_down(i);
	}
	save[C - m] = sum2;
	int tmp;
	for (i = C - m - 1; i >= m + 1; --i) {
		if (money[i + 1] < heap[1]) {
			tmp = dequeue();
			enqueue(money[i + 1]);
			sum2 += money[i + 1] - tmp;
		}
		save[i] = sum2;
	}
	current_length = m;
	for (i = 1; i <= m; ++i) {
		sum1 += money[i];
		heap[i] = money[i];
	}
	for (i = current_length / 2; i > 0; --i) {
		percolate_down(i);
	}
	if (sum1 + save[m + 1] + money[m + 1] <= F) {
		printf("%d\n", grades[m + 1]);
		return 0;
	}
	for (i = m + 2; i <= C - m; ++i) {
		if (money[i - 1] < heap[1]) {
			tmp = dequeue();
			enqueue(money[i - 1]);
			sum1 += money[i - 1] - tmp;
		}
		if (sum1 + save[i] + money[i] <= F) {
			printf("%d\n", grades[i]);
			return 0;
		}
	}
	printf("%d\n", -1);
	return 0;
}

int dequeue() {
	int tmp = heap[1];
	heap[1] = heap[current_length--];
	percolate_down(1);
	return tmp;
}

void percolate_down(int x) {
	int idx = x;
	int child;
	int tmp = heap[x];
	for (; idx * 2 <= current_length; idx = child) {
		child = idx * 2;
		if (child + 1 <= current_length && heap[child] < heap[child + 1]) {
			++child;
		}
		if (heap[child] > tmp) {
			heap[idx] = heap[child];
		}
		else break;
	}
	heap[idx] = tmp;
}

void enqueue(int x) {
	++current_length;
	int idx = current_length;
	for (; idx > 1; idx /= 2) {
		if (heap[idx / 2] < x) {
			heap[idx] = heap[idx / 2];
		}
		else break;
	}
	heap[idx] = x;
}

void q_sort(int grades[], int money[], int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary(grades, money, start, end);
	q_sort(grades, money, start, boundary - 1);
	q_sort(grades, money, boundary + 1, end);
}

int get_boundary(int grades[], int money[], int start, int end) {
	int left = start;
	int p = grades[left];
	int q = money[left];
	int right = end;
	while (left < right) {
		while (left < right && grades[right] < p) --right;
		grades[left] = grades[right];
		money[left] = money[right];
		while (left < right && grades[left] >= p) ++left;
		money[right] = money[left];
		grades[right] = grades[left];
	}
	money[left] = q;
	grades[left] = p;
	return left;
}
