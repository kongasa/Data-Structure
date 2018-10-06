//把a[]中的元素升序排序（快排），同时a[]中相同的元素按照对应的b[]中元素升序顺序排序
#include<cstdio>
#include<cstdlib>
#include<ctime>

int get_boundary(int a[], int b[], int start, int end) {
	int left = start;
	int right = end;
	int ahead = a[start];
	int bhead = b[start];
	while (left < right) {
		while (left < right && a[right] >= ahead) {
			if (a[right] == ahead && b[right] < bhead) break;
			--right;
		}
		a[left] = a[right];
		b[left] = b[right];
		while (left < right && a[left] <= ahead) {
			if (a[left] == ahead && b[left] > bhead) break;
			++left;
		}
		a[right] = a[left];
		b[right] = b[left];
	}
	a[left] = ahead;
	b[left] = bhead;
	return left;
}

void qsort(int a[], int b[], int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary(a, b, start, end);
	qsort(a, b, start, boundary - 1);
	qsort(a, b, boundary + 1, end);
}

int main() {
	srand(time(NULL));
	int a[50], b[50];
	int i;
	for (i = 0; i < 50; ++i) {
		a[i] = rand() % 10;
		b[i] = rand() % 10;
	}
	for (i = 0; i < 50; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
	for (i = 0; i < 50; ++i) {
		printf("%d ", b[i]);
	}
	printf("\n");

	qsort(a, b, 0, 49);

	for (i = 0; i < 50; ++i) {
		printf("%d ", a[i]);
	}
	printf("\n");
	for (i = 0; i < 50; ++i) {
		printf("%d ", b[i]);
	}
	printf("\n");
	return 0;
}