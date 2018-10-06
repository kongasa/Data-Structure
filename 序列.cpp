#include<cstdio>
#include<iostream>
using namespace std;

const int N = 100001;
int seq[N];
int l[N * 2];    //left[N + i] = j��ʾ��ߺ�Ϊi�ĸ��� 
int r[N * 2];    //right[N + i] = j��ʾ�ұߺ�Ϊi�ĸ���

int main() {
	int n, b;
	scanf("%d%d", &n, &b);
	int i;
	int bpos;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &seq[i]);
		if (seq[i] > b) {
			seq[i] = 1;
		}
		else if (seq[i] < b) {
			seq[i] = -1;
		}
		else {
			seq[i] = 0;
			bpos = i;
		}
	}
	int sum = 0;
	for (i = bpos; i >= 1; --i) {
		sum += seq[i];
		++l[n + sum];
	}
	sum = 0;
	for (i = bpos; i <= n; ++i) {
		sum += seq[i];
		++r[n + sum];
	}
	int ans = 0;
	for (i = -n; i <= n; ++i) {
		ans += l[n + i] * r[n - i];
	}
	printf("%d\n", ans);
	return 0;
}