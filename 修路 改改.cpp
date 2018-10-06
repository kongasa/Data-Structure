#include<cstdio>
#include<iostream>
using namespace std;

int a[2001];
const int INF = 1100000001;

struct Block {
	int left, right;
	int value;
	int lower, higher;          //left到right内比value小的和比value大的值
};

Block blocks[2001];

int abs(int x) {
	return (x > 0) ? x : -x;
}

int main() {
	int N;
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; ++i) {
		scanf("%d", &a[i]);
	}

	long long int sum1 = 0, sum2 = 0;
	int count = 0;
	blocks[0].value = -INF;
	int k;
	for (i = 1; i <= N; ++i) {
		if (a[i] > blocks[count].value) {
			blocks[++count].left = i;
			blocks[count].right = i;
			blocks[count].value = a[i];
			blocks[count].lower = 0;
			blocks[count].higher = 1;
		}
		else if (a[i] == blocks[count].value) {
			++blocks[count].higher;
			blocks[count].right = i;
		}
		else {
			++blocks[count].lower;
			++blocks[count].right;
			if (blocks[count].higher == blocks[count].lower) {
				int max_in_lower = -INF;
				for (int j = blocks[count].left; j <= blocks[count].right; ++j) {
					if (a[j] < blocks[count].value) {
						if (a[j] > max_in_lower) {
							k = 1;
							max_in_lower = a[j];
						}
						else if (a[j] == max_in_lower) {
							++k;
						}
					}
				}
				if (max_in_lower < blocks[count - 1].value) {
					blocks[count - 1].right = blocks[count].right;
					blocks[count - 1].higher += blocks[count].higher;
					blocks[count - 1].lower += blocks[count].lower;
					--count;
				}
				else if (max_in_lower == blocks[count - 1].value) {
					blocks[count - 1].right = blocks[count].right;
					blocks[count - 1].higher += blocks[count].higher + k;
					blocks[count - 1].lower += blocks[count].lower - k;
					--count;
				}
				else {
					blocks[count].value = max_in_lower;
					blocks[count].higher += k;
					blocks[count].lower -= k;
				}
			}
		}
	}
	for (i = 1; i <= count; ++i) {
		for (int j = blocks[i].left; j <= blocks[i].right; ++j) {
			sum1 += abs(a[j] - blocks[i].value);
		}
//		printf("blocks[%d].value:%d\n",i,  blocks[i].value);
	}

	blocks[0].value = INF;
	count = 0;
	for (i = 1; i <= N; ++i) {
		if (a[i] < blocks[count].value) {
			blocks[++count].left = i;
			blocks[count].right = i;
			blocks[count].value = a[i];
			blocks[count].lower = 1;
			blocks[count].higher = 0;
		}
		else if (a[i] == blocks[count].value) {
			++blocks[count].lower;
			blocks[count].right = i;
		}
		else {
			++blocks[count].higher;
			++blocks[count].right;
			if (blocks[count].higher == blocks[count].lower) {
				int min_in_higher = INF;
				for (int j = blocks[count].left; j <= blocks[count].right; ++j) {
					if (a[j] > blocks[count].value) {
						if (a[j] < min_in_higher) {
							min_in_higher = a[j];
							k = 1;
						}
						else if (a[j] == min_in_higher) {
							++k;
						}
					}
				}
				if (min_in_higher > blocks[count - 1].value) {
					blocks[count - 1].right = blocks[count].right;
					blocks[count - 1].higher += blocks[count].higher;
					blocks[count - 1].lower += blocks[count].lower;
					--count;
				}
				if (min_in_higher == blocks[count - 1].value) {
					blocks[count - 1].right = blocks[count].right;
					blocks[count - 1].higher += blocks[count].higher - k;
					blocks[count - 1].lower += blocks[count].lower + k;
					--count;
				}
				else {
					blocks[count].value = min_in_higher;
					blocks[count].lower += k;
					blocks[count].higher -= k;
				}
			}
		}
	}
	for (i = 1; i <= count; ++i) {
		for (int j = blocks[i].left; j <= blocks[i].right; ++j) {
			sum2 += abs(a[j] - blocks[i].value);
		}
	}
//	printf("sum1:%d  sum2:%d\n", sum1, sum2);
//	cout << sum1 << " " << sum2 << endl;
	if (sum1 < sum2) { printf("%lld\n", sum1); }
	else { printf("%lld\n", sum2); }
	return 0;
}