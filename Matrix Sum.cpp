#include<cstdio>
#include<iostream>
using namespace std;
#define ll long long
ll sum[401][401][2];          //0为奇阵， 1为偶阵
ll s[401];                    //前缀和
ll a[401][401][2];                 //0为奇阵，1为偶阵

int main() {
	int n;
	scanf("%d", &n);
	int i, j;
	int k;
	int tmp;
	for (i = 1; i <= n; ++i) {
		for (k = 1; k <= n; ++k) {
			s[k] = 0;
		}
		for (j = 1; j <= n; ++j) {
			scanf("%d", &tmp);
			tmp = tmp & 1;
			s[j] = s[j - 1] + tmp;
			for (k = 0; k < j; ++k) {
				tmp = s[j] - s[k];
				ll ji = a[j][k + 1][0];
				ll ou = a[j][k + 1][1];
				tmp = tmp & 1;
				if (tmp == 0) {
					a[j][k + 1][0] = ji;
					a[j][k + 1][1] = ou + 1;
				}
				else {
					a[j][k + 1][1] = ji;
					a[j][k + 1][0] = ou + 1;
				}
			}
			for (k = 1; k <= n; ++k) {
				sum[i][j][0] += a[j][k][0];
				sum[i][j][1] += a[j][k][1];
			}
		}
	}
	ll ans1 = 0LL, ans2 = 0LL;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= n; ++j) {
			ans1 += sum[i][j][0];
			ans2 += sum[i][j][1];
		}
	}
	cout << ans1 << ' ' << ans2 << endl;
	return 0;
}