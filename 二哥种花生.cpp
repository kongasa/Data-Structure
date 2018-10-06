#include<cstdio>

int sum[1001][1001];        //sum[i][j]:1~i�� 1~j������Ԫ�صĺ�
int sum1[1001];             //��¼��i��ǰsum��Ԫ�غ͵ĸ�������

int Max(int a, int b) {
	return (a > b) ? a : b;
}

int main() {
	int L, W;
	int i, j;
	int tmp;
	scanf("%d%d", &L, &W);
	for (i = 1; i <= L; ++i) {
		for (j = 1; j <= W; ++j) {
			scanf("%d", &tmp);
			sum1[j] = sum1[j - 1] + tmp;
			sum[i][j] = sum[i - 1][j] + sum1[j];
		}
	}

	int a, b;
	scanf("%d%d", &a, &b);
	int m = 0;
	for (i = a; i <= L; ++i) {
		for (j = b; j <= W; ++j) {
			m = Max(m, sum[i][j] - sum[i - a][j] - sum[i][j - b] + sum[i - a][j - b]);
		}
	}
	printf("%d\n", m);
	return 0;
}