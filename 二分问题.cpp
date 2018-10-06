#include<cstdio>
#include<iostream>
using namespace std;

int nums[100001];

int main() {
	freopen("data10.in", "r", stdin);
	freopen("data.out", "w", stdout);
	int n, m;
	int i;
	scanf("%d%d", &n, &m);
	for (i = 1; i <= n; ++i) {
		scanf("%d", &nums[i]);
	}
	int x;
	int left;
	int right;
	int mid;
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &x);
		left = 1;
		right = n;
		while (left < right) {
			mid = (left + right) >> 1;
			if (nums[mid] >= x) right = mid;
			else left = mid + 1;
		}
		if (nums[left] != x) printf("-1 ");
		else printf("%d ", left);
		left = 1; right = n;
		while (left < right) {
			mid = ((left + right) >> 1) + 1;
			if (nums[mid] > x) right = mid - 1;
			else left = mid;
		}
		if (nums[left] != x) printf("-1\n");
		else printf("%d\n", left);
	}

	return 0;
}