#include<cstdio>
#include<iostream>
using namespace std;

int nums[10000];
int re[101];
int ans;

int main() {
	int n;
	scanf("%d", &n);
	int i;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &nums[i]);
		re[nums[i]] = 1;
	}
	int j;
	int oldpos = n + 1;
	int newpos = n;
	int tmp;
	for (i = 1; i <= n; ++i) {
		for (j = i + 1; j <= n; ++j) {
			tmp = (nums[i] > nums[j]) ? nums[i] / nums[j] : nums[j] / nums[i];
			if (re[tmp] == 0) {
				nums[++newpos] = tmp;
				re[tmp] = 1;
			}
		}
	}
	while (oldpos <= newpos) {
		for (i = 1; i < oldpos; ++i) {
			tmp = (nums[i] > nums[oldpos]) ? nums[i] / nums[oldpos] : nums[oldpos] / nums[i];
			if (re[tmp] == 0) {
				nums[++newpos] = tmp;
				re[tmp] = 1;
			}
		}
		++oldpos;
	}
	printf("%d\n", newpos);
	return 0;
}