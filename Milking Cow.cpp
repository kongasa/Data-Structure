#include<cstdio>

const int MAX = 20001;
int in[MAX];
int out[MAX];
int get_boundary(int[], int[], int, int);
void q_sort(int[], int[], int, int);
int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	int N;
	scanf("%d", &N);
	int i;
	for (i = 1; i <= N; ++i) {
		scanf("%d %d", &in[i], &out[i]);
	}

	int max1 = 0, max2 = 0;        //max1有人时间, max2无人时间
	q_sort(in, out, 1, N);
	int in_time = in[1], out_time = out[1];
	
	for (i = 2; i <= N; ++i) {
		if (in[i] <= out_time) {
			if (out[i] > out_time) {
				out_time = out[i];
			}
		}
		else {
			max1 = max(max1, out_time - in_time);
			max2 = max(max2, in[i] - out_time);
			in_time = in[i];
			out_time = out[i];
		}
	}
	max1 = max(out_time - in_time, max1);
	printf("%d %d\n", max1, max2);
	return 0;
}

void q_sort(int a[], int b[], int start, int end) {
	if (start >= end) {
		return;
	}
	int boundary = get_boundary(a, b, start, end);
	q_sort(a, b, start, boundary - 1);
	q_sort(a, b, boundary + 1, end);
}

int get_boundary(int a[], int b[], int start, int end) {
	int left = start;
	int right = end;
	int m = a[start];
	int n = b[start];
	while (left < right) {
		while (left < right && a[right] > m) {
			--right;
		}
		a[left] = a[right];
		b[left] = b[right];
		while (left < right && a[left] <= m) {
			++left;
		}
		a[right] = a[left];
		b[right] = b[left];
	}
	a[left] = m;
	b[left] = n;
	return left;
}