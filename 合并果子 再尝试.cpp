#include<cstdio>

int heap[10001];
int current_size = 0;
void percolate_down(int);
void enqueue(int);
int dequeue();

int main() {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &heap[i]);
	}
	current_size = n;
	for (i = current_size / 2; i >= 1; --i) {
		percolate_down(i);
	}

	int a, b;
	int sum = 0;
	while (current_size > 1) {
		a = dequeue();
		b = dequeue();
		sum += a + b;
		enqueue(a + b);
	}
	printf("%d\n", sum);
	return 0;
}

void percolate_down(int idx) {
	int child;
	int m = heap[idx];

	for (; idx * 2 <= current_size; idx = child) {
		child = idx * 2;
		if (child + 1 <= current_size && heap[child] > heap[child + 1]) {
			++child;
		}
		if (heap[child] < m) {
			heap[idx] = heap[child];
		}
		else break;
	}
	heap[idx] = m;
}

int dequeue() {
	int ans = heap[1];
	heap[1] = heap[current_size--];
	percolate_down(1);
	return ans;
}

void enqueue(int x) {
	heap[++current_size] = x;
	int idx = current_size;
	for (; idx > 1 && heap[idx / 2] > x; idx /= 2) {
		heap[idx] = heap[idx / 2];
	}
	heap[idx] = x;
}