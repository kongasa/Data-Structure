#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int idx;
	int data;
	node(int d = 0, int x = 0) : idx(d), data(x) {}
};

int nums[100001];
int n;
int ans1[100001];
int ans2[100001];
int t1;
int t2;
node queue3[100001];
node queue4[100001];
int length1;
int length2;


int main() {
	int k;
	scanf("%d%d", &n, &k);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &nums[i]);
	}


	node *queue1 = queue3, *queue2 = queue4;
	for (i = 1; i <= n; ++i) {
		if (length1 > 0 && i - queue1[1].idx >= k) {
			++queue1;
		}
		if (length2 > 0 && i - queue2[1].idx >= k) {
			++queue2;
		}

		if (length1 == 0) queue1[++length1] = node(i, nums[i]);
		else {
			while (length1 > 0 && queue1[length1].data < nums[i]) {
				--length1;
			}
			queue1[++length1] = node(i, nums[i]);
		}

		if (length2 == 0) queue2[++length2] = node(i, nums[i]);
		else {
			while (length2 > 0 && queue2[length2].data > nums[i]) {
				--length2;
			}
			queue2[++length2] = node(i, nums[i]);
		}
		if (i >= k) {
			ans1[++t1] = queue1[1].data;
			ans2[++t2] = queue2[1].data;
		}
	}
	for (i = 1; i <= t2; ++i) {
		printf("%d ", ans2[i]);
	}
	printf("\n");
	for (i = 1; i <= t1; ++i) {
		printf("%d ", ans1[i]);
	}
	printf("\n");
	return 0;
}