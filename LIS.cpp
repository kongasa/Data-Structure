#include<cstdio>

int nums[1000001];
int ans[1000001];

int get_pos(int x, int left, int right) {
	if (left >= right) {
		return left;
	}
	int mid = (left + right) / 2;
	if (ans[mid] == x) { return mid; }
	if (ans[mid] > x) {
		return get_pos(x, left, mid);
	}
	else return get_pos(x, mid + 1, right);
}

int main() {
	int N;
	scanf("%d", &N);
	int i;
	for (i = 1; i <= N; ++i) {
		scanf("%d", &nums[i]);
	}

	int len = 0;
	ans[1] = 0;
	for (i = 1; i <= N; ++i) {
		if (nums[i] > ans[len]) {
			ans[++len] = nums[i];
		}
		else {
			int idx = get_pos(nums[i], 1, len);
			ans[idx] = nums[i];
		}
	}
	printf("%d\n", len);
	return 0;
}