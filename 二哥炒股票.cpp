#include<cstdio>
#include<iostream>
using namespace std;

double profit;
int t1[51];                         //二哥的交易动作
int a[51];                          //二哥的交易动作
int d[51];                           //二哥的交易动作 买入卖出
int t2[10001];                       //股票变动
int v[10001];                       //股票变动为v元每股

int main() {
	int m, n;
	scanf("%d", &m);
	int i;
	for (i = 1; i <= m; ++i) {
		scanf("%d%d%d", &t1[i], &a[i], &d[i]);
	}
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) {
		scanf("%d%d", &t2[i], &v[i]);
	}

	int j = 1;
	double tmp;
	for (i = 1; i <= m; ++i) {
		while (t1[i] >= t2[j] && j <= n) {
			++j;
		}
		switch (d[i]) {
		case 1:
			profit -= (tmp = 100 * a[i] * v[j - 1]) + static_cast<double>(a[i]) / 10 + 1;
			tmp *= 0.002;
			if (tmp < 5) profit -= 5;
			else profit -= tmp;
			break;
		case 2:
			profit += (tmp = 100 * a[i] * v[j - 1]) - static_cast<double>(a[i]) / 10 - 1 - tmp * 0.001;
			tmp *= 0.002;
			if (tmp < 5) profit -= 5;
			else profit -= tmp;
		}
	}
	printf("%.2f\n", profit);
	return 0;
}