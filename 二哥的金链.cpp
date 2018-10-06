#include<cstdio>

const int INF = 0x7fffffff;

int nodes[400001];
int queue[400001];

int min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	int i;
	int nums = 0;                    //队列元素个数
	int *top = queue;
	int right = 1;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &nodes[i]);
		nodes[i + N] = nodes[i];
	}

	int min_value = INF;
	while (right <= N + N - 1) {
		while (nums != 0 && nodes[right] > nodes[top[nums - 1]]) --nums;
		top[nums++] = right;
		if (right - top[0] >= K) {
			++top;
			--nums;
		}
		if (right > K) min_value = min(min_value, nodes[top[0]]);
		++right;
	}
	printf("%d\n", min_value);
	return 0;
}