#include<cstdio>

const int INF = 0x7fffffff;
int a[1000001];
int b[1000001];
int c[1000001];

int get_pos1(int x, int left, int right) {
	int mid;
	while (left < right) {
		mid = (left + right) >> 1;
		if (x < b[mid]) left = mid + 1;
		else if (x > b[mid]) right = mid;
		else return mid;
	}
	return left;
}

int get_pos2(int x, int left, int right) {
	int mid;
	while(left < right) {
		mid = (left + right) >> 1;
		if (x < c[mid]) right = mid;
		else left = mid + 1;
	}
	return left;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	b[0] = INF;
	int N;
	scanf("%d", &N);
	int i;
	int max_length = 0;
	int current_pos = 0;

	int current_length = 0;        //c
	int idx;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &a[i]);
		if (a[i] < b[max_length]) {
			b[++max_length] = a[i];
//			max_length = max(max_length, current_pos);
		}
		else {
			current_pos = get_pos1(a[i], 1, max_length);
			b[current_pos] = a[i];
		}

		if (a[i] >= c[current_length]) {
			c[++current_length] = a[i];
		}
		else {
			idx = get_pos2(a[i], 1, current_length);
			c[idx] = a[i];
		}
	}
	printf("%d\n%d\n", max_length, current_length);
	return 0;
}
