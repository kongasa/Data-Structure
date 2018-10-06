//ÉÆÓÃÇ°×ººÍ
#include<cstdio>

//int nums[1000001];
int sum[1000001];

int Max(int a, int b) {
	return (a > b) ? a : b;
}

int Min(int a, int b) {
	return (a < b) ? a : b;
}

int main() {
	int n;
	scanf("%d", &n);
	int i;
	int tmp;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &tmp);
		sum[i] = sum[i - 1] + tmp;
	}

	int j;
	int max_sum = 0;
	int min_qianzhuihe = 0;
	for (j = 2; j <= n; ++j) {
		if (sum[j - 2] < sum[min_qianzhuihe]) min_qianzhuihe = j - 2;
		max_sum = Max(max_sum, sum[j] - sum[min_qianzhuihe]);
	}
	//	int current_sum = nums[1];
	//	int max_sum = 0;
	//	int left = 1;
	//	for (i = 2; i <= n; ++i) {
	//		current_sum += nums[i];
	//		printf("current_sum %d\n", current_sum);
	//		if (current_sum < 0 && i != n - 1) {
	//			if (nums[i + 1] < 0) {
	//				while
	//			}
	//			/*if (current_sum + nums[i + 1] < 0) {
	//				current_sum = nums[++i];
	//				continue;
	//			}*/
	//		}
	//		max_sum = Max(max_sum, current_sum);
	//	}
	if (max_sum <= 0) {
		printf("Game Over\n");
	}
	else printf("%d\n", max_sum);
	return 0;
}